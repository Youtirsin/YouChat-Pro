#include "epoll.h"


Epoll::Epoll(int event_num_):
    events(event_num_) {
    this->epfd = epoll_create(100);
    assert(epfd != -1);
}


int Epoll::wait(int timeoutMs) {
    return epoll_wait(epfd, &events[0], static_cast<int>(events.size()), timeoutMs);
}


bool Epoll::addFd(int fd, uint32_t events) {
    assert(fd >= 0);
    
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = events;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        perror("epoll add:");
        return false;
    }
    return true;
}


bool Epoll::modFd(int fd, uint32_t events) {
    assert(fd >= 0);

    epoll_event ev;
    ev.data.fd = fd;
    ev.events = events;

    if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
        perror("epoll modify:");
        return false;
    }
    return true;
}


bool Epoll::removeFd(int fd) {
    assert(fd >= 0);
    
    epoll_event ev;
    return 0 == epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
}


int Epoll::getEventFd(size_t i) const {
    return events.at(i).data.fd;
}


uint32_t Epoll::getEvents(size_t i) const {
    return events.at(i).events;
}


Epoll::~Epoll() {
    close(epfd);
}