#pragma once

#include <iostream>
#include <vector>

#include <cassert>
#include <sys/epoll.h>
#include <unistd.h>


class Epoll {
public:
    Epoll(int event_num);

    int wait(int timeoutMs = -1);

    bool addFd(int fd, uint32_t events);

    bool modFd(int fd, uint32_t events);

    bool removeFd(int fd);

    int getEventFd(size_t i) const;

    uint32_t getEvents(size_t i) const;

    ~Epoll();

private:
    int epfd;

    std::vector<epoll_event> events;
};