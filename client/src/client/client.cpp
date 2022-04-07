#include "client.h"

void Client::start() {
    assert(socket_init());


}

bool Client::socket_init() {
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == -1) {
        perror("error creating socket.");
        return false;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr.s_addr);

    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("error connecting.");
        return false;
    }
}

void Client::prompt() {
    int opt;
    while (true) {
        printf("what next:\n");
        printf("1. register name.\n");
        printf("2. fetch user list.\n");
        printf("3. send message to someone");
        printf("4. broadcast a message\n");
        printf("5. show messages\n");
        
        std::cin >> opt;
        
        if (opt == 1) {
            registerName();
        }else if (opt == 2) {
            fetchUserList();
        }else if (opt == 3) {
            privateMsg();
        }else if (opt == 4) {
            broadcast();
        }else if (opt == 5) {
            showMessages();
        }else {
            printf("invalid option, try again.\n");
        }
    }
}

void Client::listen() {
    while(true) {
        memset(read_buffer, 0, BUFF_SIZE);
        int len = read(sock, read_buffer, BUFF_SIZE);

        if(len > 0) {
            printf("server: %s\n", read_buffer);
        } else if(len == 0) {
            printf("server disconnected.\n");
            break;
        } else {
            perror("read");
            exit(-1);
        }
    }
}

void Client::registerName() {
    std::string name;
    printf("enter username: ");
    std::cin >> name;

    RegistrationReq req(name);

    write_(req.dump());
}

void Client::fetchUserList() {
    FetchListReq req;

    write_(req.dump());
}

void Client::privateMsg() {
    std::string target, msg;
    printf("enter target username: ");
    getline(std::cin, target);
    printf("enter the message: ");
    getline(std::cin, msg);

    PrivateReq req(target, msg);

    write_(req.dump());
}

void Client::broadcast() {
    std::string msg;
    printf("enter the message: ");
    getline(std::cin, msg);

    BroadcastReq req(msg);

    write_(req.dump());
}

void Client::showMessages() {
    
}

void Client::write_(const std::string& response) {
    std::lock_guard<std::mutex> guard(mtx);

    write(sock, response.c_str(), response.size());
}