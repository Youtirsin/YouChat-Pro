#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == -1) {
        perror("error creating socket.");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10086);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("error connecting.");
        exit(0);
    }

    int number = 0;
    char buf[BUF_SIZE];
    
    std::string msg;

    while(true) {
        getline(std::cin, msg);
        write(sock, msg.c_str(), msg.size());

        memset(buf, 0, sizeof(buf));
        int len = read(sock, buf, sizeof(buf));

        if(len > 0) {
            printf("server: %s\n", buf);
        } else if(len == 0) {
            printf("server disconnected.\n");
            break;
        } else {
            perror("read");
            break;
        }
    }

    close(sock);

    return 0;
}