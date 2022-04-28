#include "server.h"

Server::Server(const SqlConnPool::Config& sqlconfig, const string& redisconn): 
    epoll(new Epoll(FD_NUM)), threadpool(new ThreadPool()),
    dbapi(sqlconfig), redisapi(redisconn) {

    closed = false;

    assert(socket_init());

    assert(epoll->addFd(listenfd, EPOLLIN));
}


void Server::start() {
    while (!closed) {
        int num = epoll->wait(-1);

        for (int i = 0; i < num; i++) {
            int fd = epoll->getEventFd(i);

            uint32_t events = epoll->getEvents(i);

            if(fd == listenfd) {
                doConnect();

            }else if (events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                closeConn(fd);

            }else if (events & EPOLLIN) {
                processRead(fd);
            }
        }
        
    }
}


bool Server::socket_init() {
    this->listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->listenfd < -1) {
        perror("socket create:");
        return false;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 1;

    // IO reuse
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind:");
        return false;
    }

    printf("server started.\n");
    printf("listening at port: %d...\n", ntohs(serv_addr.sin_port));

    // listen
    if(listen(listenfd, LISTEN_NUM) == -1) {
        perror("listen:");
        return false;
    }

    return true;
}


void Server::doConnect() {
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);

    int cfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);

    // invalid fd
    if (cfd < 0) { return; }

    // add connection to the fd->conn map
    ClientConn *conn = new ClientConn(cfd, cliaddr);
    conns[cfd] = conn;

    // set file fd to non block
    setFdNonBlock(cfd);

    // add to epoll
    epoll->addFd(cfd, EPOLLIN | EPOLLET);

    printf("socket [%s:%d] connected.\n", conn->getIP(), conn->getPort());
}


void Server::closeConn(int fd) {
    // delete from fd->conn map, which must exist
    ClientConn *conn = conns[fd];
    printf("client [%s:%d] disconnected.\n", conn->getIP(), conn->getPort());
    conns.erase(fd);
    delete conn;

    // delete from fd -> user_id map, which maybe not exists
    if (fd_to_userId.count(fd)) {
        // if exists in fd->user_id map, its of a user logged in
        // user_id also needs to be erased
        // delete from user_id -> conn
        int userId = fd_to_userId[fd];
        // double delete
        userId_to_fd.erase(userId);
        fd_to_userId.erase(fd); 
    }

    // remove from epoll
    epoll->removeFd(fd);

    close(fd);
}


int Server::setFdNonBlock(int fd) {
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
}


void Server::processRead(int fd) {
    // put task to the task queue
    threadpool->addTask(std::bind(&Server::read, this, fd));
}


void Server::read(int fd) {
    string request;
    ClientConn *conn = conns[fd];

    // read request
    if (!conn->read(request)) {
        printf("error while reading.\n");
        printf("disconnecting client [%s:%d]...\n", conn->getIP(), conn->getPort());

        closeConn(fd);
        return;
    }

    printf("received request from client [%s:%d].\n", 
        conn->getIP(), 
        conn->getPort());
    
    handleRequest(request, conn);
}


void Server::write(ClientConn *client, string response) {
    if (!client->write(response))  {
        closeConn(client->getFd());
        return;
    }
}


void Server::handleRequest(const string& request, ClientConn *client) {
    RequestBase requestBase;

    if (!requestBase.load(request)) {
        printf("failed to deserialized request.\n");
        denied(request, client);
        return;
    }
    

    if (requestBase.type == "signup") {
        signUp(request, client);
        return;
    }

    if (requestBase.type == "signin") {
        signIn(request, client);
        return;
    }

    // if client is not validated, send denied message
    if (!fd_to_userId.count(client->getFd())) {
        denied(request, client);
        return;
    }

    // *********************** broadcast **********************
    if (requestBase.type == "broadcast") {
        broadcast(request, client);
        return;
    }

    // *********************** fetchlist **********************
    if (requestBase.type == "fetchlist") {
        fetchlist(request, client);
        return;
    }
        
    // *********************** private ************************
    if (requestBase.type == "private") {
        privateMsg(request, client);
        return;
    }

    // *********************** private ************************
    if (requestBase.type == "privateload") {
        loadPrivate(request, client);
        return;
    }
        
    // *********************** private ************************
    if (requestBase.type == "broadcastload") {
        loadBroadcast(request, client);
        return;
    }
    
    denied(request, client);
}


void Server::denied(const string& request, ClientConn *client) {
    printf("request type: unknown, permission denied\n");
    DeniedRes res;
    threadpool->addTask(std::bind(&Server::write, this, client, res.dump()));
}


void Server::signUp(const string& request, ClientConn *client) {
    SignUpReq req;

    printf("request type: sign up, client [%s, %d] is signing up.\n", client->getIP(), client->getPort());
    if (!req.load(request)) { return; }

    if (dbapi.saveUser(req.username, req.password)) {
        SignUpRes res(1);
        threadpool->addTask(std::bind(&Server::write, this, client, res.dump()));
    }else {
        SignUpRes res(0);
        threadpool->addTask(std::bind(&Server::write, this, client, res.dump()));
    }
}


void Server::signIn(const string& request, ClientConn *client) {
    SignInReq req;

    printf("request type: sign in, client [%s, %d] is signing in.\n", client->getIP(), client->getPort());
    if (!req.load(request)) { return; }
    
    auto user = redisapi.getUserWithName(req.username);
    if (!user) {
        user = dbapi.getUserWithName(req.username);
        if (!user) {
            SignInRes res(0);
            threadpool->addTask(std::bind(&Server::write, this, client, res.dump()));
            return;
        }
        redisapi.saveUser(*user);
    }

    string realPsd = user->password;

    if (realPsd == req.password) {
        fd_to_userId[client->getFd()] = user->id;
        userId_to_fd[user->id] = client->getFd();

        SignInRes res(1);
        threadpool->addTask(std::bind(&Server::write, this, client, res.dump()));
    }else {
        SignInRes res(0);
        threadpool->addTask(std::bind(&Server::write, this, client, res.dump()));
    }
}


void Server::broadcast(const string& request, ClientConn *client) {
    BroadcastReq req;
    if (!req.load(request)) { return; }

    int id = fd_to_userId[client->getFd()];

    BroadcastRes res(id, req.msg, timestampnow());
    string response = res.dump();
    printf("request type: broadcast, sending message to everyone.\n");

    dbapi.saveBroadcastMsg(id, req.msg);

    // save unread noti for the offline
    std::unordered_set<int> allid = redisapi.getAllUserIds();

    for (auto &&fd : fd_to_userId) {
        allid.erase(fd.second); // remove the online
        ClientConn * conn = conns[fd.first];
        threadpool->addTask(std::bind(&Server::write, this, conn, response));
    }
    
    for (auto &&e : allid) {
        redisapi.increUnreadBy(e, 0, 1); // add an unread of the broadcast
    }
    
    printf("done broadcasting.\n");
}


void Server::fetchlist(const string& request, ClientConn *client) {
    printf("request type: fetchlist, returning the user list.\n");
    FetchListRes res;

    for (auto &&c : userId_to_fd) {
        auto user = redisapi.getUserWithId(c.first);
        if (!user) {
            user = dbapi.getUserWithId(c.first);
            if (!user) { continue; }
            redisapi.saveUser(*user);
        }
        res.addName(user->username, c.first);
    }
    
    threadpool->addTask(std::bind(&Server::write, this, client, res.dump()));
}


void Server::privateMsg(const string& request, ClientConn *client) {
    PrivateReq req;
    if (!req.load(request)) return;
    printf("request type: private, sending to %d.\n", req.to_id);

    bool target_online = true;
    // sender id
    int from_id = fd_to_userId[client->getFd()];

    // target not online or not exists
    if (!userId_to_fd.count(req.to_id)) {
        // not exists
        if (!redisapi.getUserWithId(req.to_id) && !dbapi.getUserWithId(req.to_id)) {
            return;
        }
        target_online = false;

        redisapi.increUnreadBy(from_id, req.to_id, 1);
    }

    // load target connection
    int to_fd = userId_to_fd[req.to_id];
    ClientConn * toClient = conns[to_fd];

    // save msg
    dbapi.savePrivateMsg(from_id, req.to_id, req.msg);

    // send msg
    if (target_online) {
        PrivateRes res(from_id, req.to_id, req.msg, timestampnow());
        threadpool->addTask(std::bind(&Server::write, this, toClient, res.dump()));
    }
}


void Server::loadPrivate(const string& request, ClientConn *client) {
    PrivateLoadReq req;
    if (!req.load(request)) return;
    printf("request type: private, sending to %d.\n", req.to_id);

    // from id
    int from_id = fd_to_userId[client->getFd()];
    
    redisapi.clearUnread(from_id, req.to_id); // clear unread notifications

    string res = dbapi.loadPrivateMsg(from_id, req.to_id, req.page, req.size);
    threadpool->addTask(std::bind(&Server::write, this, client, res));
}


void Server::loadBroadcast(const string& request, ClientConn *client) {
    BroadcastLoadReq req;
    if (!req.load(request)) return;

    // from id
    int from_id = fd_to_userId[client->getFd()];

    redisapi.clearUnread(from_id, 0); // clear unread notifications
    
    string res = dbapi.loadBroadcastMsg(req.page, req.size);
    threadpool->addTask(std::bind(&Server::write, this, client, res));
}
