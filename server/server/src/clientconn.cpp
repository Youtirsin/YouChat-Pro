#include "clientconn.h"


ClientConn::ClientConn(int fd_, const sockaddr_in& cliaddr_) {
    fd = fd_;

    cliaddr = cliaddr_;

    user_id = "";

    inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, sizeof(ip));

    port = ntohs(cliaddr.sin_port);
}


bool ClientConn::read(std::string& request) {
    std::lock_guard<std::mutex> guard(mtx);
    request = "";

    memset(readBuffer, 0, sizeof(readBuffer));

    // 循环读数据
    while(1) {

        int len = recv(fd, readBuffer, sizeof(readBuffer), 0);

        if(len == 0) {
            // 非阻塞模式下和阻塞模式是一样的 => 判断对方是否断开连接
            return false;

        }else if(len > 0) {

            std::copy(readBuffer, readBuffer + len, std::back_inserter(request));

        } else {

            if(errno == EAGAIN) {

                // done reading
                return true;

            } else {

                // reading fault
                return false;
            }
        }
    }
}

bool ClientConn::write(std::string& response) {
    std::lock_guard<std::mutex> guard(mtx);

    std::string send_;

    for (int i = 0; i < response.size(); i += BUFFER_SIZE) {

        int n = BUFFER_SIZE;

        n = std::min(n, int(response.size() - i));

        send_ = response.substr(i, n);

        std::copy(send_.begin(), send_.end(), writeBuffer);
        
        send(fd, writeBuffer, n, 0);
    }
    return true;
}