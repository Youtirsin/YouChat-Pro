# YouChat-Pro

[中文](./ch.md)

 A IM application with Linux C++

- Adpoted Epoll multiplexing

- Constructed a task queue together with a thread pool competing for the tasks

- Used Redis for data caching

- Encapsulated the mysqlclient,  and realized a connection pool

- Built a cross-platform desktop application with the PyQT framework (Not in the project yet)

# Prerequisites

- libjsoncpp-dev
- libmysqlclient-dev
- libhiredis-dev
- redis-plus-plus

## Run

## Setup the database

### 1. create database and data tables

> - see /sql/create.sql

### 2. configurate the connection

> - temporarily in server.h

## Compile and run

```shell
mkdir build
cd build && cmake ..
./server
```

## Installation and deployment
