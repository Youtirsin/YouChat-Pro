#include "dbapi.h"

DBApi::DBApi(const SqlConnPool::Config& config_):
    config(config_) {
}


bool DBApi::saveUser(const string& username, const string& password) {
    SqlConnWrapper conn((SqlConnPool::Instance(config)));
    stringstream fmt;
    
    fmt << "insert into user(username, password) values('" << username << "', '" << password << "')";
    
    // insert into database
    if (!conn.getConn()->db_insert(fmt.str())) { return false; }

    return true;
}


shared_ptr<User> DBApi::getUserWithId(int id) {
    SqlConnWrapper conn((SqlConnPool::Instance(config)));
    stringstream fmt;
    
    fmt << "select * from user where id='" << id << "'";

    auto res = conn.getConn()->db_select(fmt.str());

    if (res.size() == 0) { return nullptr; }


    shared_ptr<User> user = std::make_shared<User>();

    user->id = std::stoi(res[0][0]);
    user->username = std::stoi(res[0][1]);
    user->password = std::stoi(res[0][2]);

    return user;
}


shared_ptr<User> DBApi::getUserWithName(const string& username) {
    SqlConnWrapper conn((SqlConnPool::Instance(config)));
    stringstream fmt;
    
    fmt << "select * from user where username='" << username << "'";

    auto res = conn.getConn()->db_select(fmt.str());

    if (res.size() == 0) { return nullptr; }

    shared_ptr<User> user = std::make_shared<User>();
    user->id = std::stoi(res[0][0]);
    user->username = std::stoi(res[0][1]);
    user->password = std::stoi(res[0][2]);
    
    return user;
}


// string DBApi::getPsd(const string& username) {
//     SqlConnWrapper conn((SqlConnPool::Instance(config)));
//     stringstream fmt;
    
//     fmt << "select password from user where username='" << username << "'";
    
//     auto res = conn.getConn()->db_select(fmt.str());

//     if (res.size() == 0) { return ""; }

//     return res[0][0];
// }

// int DBApi::getUserId(const string& username) {
//     SqlConnWrapper conn((SqlConnPool::Instance(config)));
//     stringstream fmt;

//     fmt << "select id from user where username='" << username << "'";
//     auto res = conn.getConn()->db_select(fmt.str());

//     if (res.size() == 0) { return -1; }
//     return stoi(res[0][0]);
// }


// string DBApi::getUsername(int id) {
//     SqlConnWrapper conn((SqlConnPool::Instance(config)));
//     stringstream fmt;

//     fmt << "select username from user where id='" << id << "'";
//     auto res = conn.getConn()->db_select(fmt.str());

//     if (res.size() == 0) { return ""; }
//     return res[0][0];
// }


bool DBApi::savePrivateMsg(int from_id, int to_id, const string& msg) {
    SqlConnWrapper conn((SqlConnPool::Instance(config)));
    stringstream fmt;

    if (from_id == -1 || to_id == -1) { return false; }

    fmt.str("");
    fmt << "insert into privatemsg(fromid, toid, msg) values('" << from_id << "','" << to_id << "','" << msg << "')";
    if (!conn.getConn()->db_insert(fmt.str())) { return false; }

    return true;
}


bool DBApi::saveBroadcastMsg(int from_id, const string& msg) {
    SqlConnWrapper conn((SqlConnPool::Instance(config)));
    stringstream fmt;

    if (from_id == -1) { return false; }

    fmt.str("");
    fmt << "insert into broadcastmsg(fromid, msg) values('" << from_id << "','" << msg << "')";
    if (!conn.getConn()->db_insert(fmt.str())) { return false; }

    return true;
}


string DBApi::loadPrivateMsg(int user_id, int friend_id, int page, int size) {
    if (page <= 0) {
        cout << "invalid parameter: page " << page << endl;
        return "";
    }
    int from = size * (page - 1);
    int to = from + size;
   
    SqlConnWrapper conn((SqlConnPool::Instance(config)));
    stringstream fmt;

    fmt << "select fromid, toid, msg, stamp from privatemsg \
where (fromid=" << user_id <<  " and toid=" << friend_id << ") \
or (fromid=" << friend_id << " and toid=" << user_id << ") \
order by stamp desc limit " << from << ", " << to;

    PrivateLoadRes res(friend_id);
    // Json::Value root;
    auto searched = conn.getConn()->db_select(fmt.str());

    if (searched.size() == 0) { return ""; }

    for (auto &&row : searched) {
        PrivateRes p(stoi(row[0]), stoi(row[1]), row[2], row[3]);
        res.addMsg(p);
        // root.append(p.dumpJson());
    }

    return res.dump();
    // return root.toStyledString();
}


string DBApi::loadBroadcastMsg(int page, int size) {

    if (page <= 0) {
        cout << "invalid parameter: page " << page << endl;
        return "";
    }
    int from = size * (page - 1);
    int to = from + size;
   
    SqlConnWrapper conn((SqlConnPool::Instance(config)));
    stringstream fmt;

    fmt << "select fromid, msg, stamp from broadcastmsg \
order by stamp desc limit " << from << ", " << to;

    // Json::Value root;
    BroadcastLoadRes res;
    auto searched = conn.getConn()->db_select(fmt.str());

    if (searched.size() == 0) { return ""; }

    for (auto &&row : searched) {
        BroadcastRes p(stoi(row[0]), row[1], row[2]);
        res.addMsg(p);
        // root.append(p.dumpJson());
    }

    // return root.toStyledString();
    return res.dump();
}