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

> - config your database connection in config.json like following, and put the json file to the directory where the excutable is in

```json
{
    "redis" : "tcp://127.0.0.1:6379",

    "mysql" : {
        "host" : "127.0.0.1",
        "user" : "root",
        "pwd" : "123456",
        "dbname" : "youchatpro",
        "connsize" : 10
    }
}
```

## Compile and run

```shell
mkdir build
cd build && cmake ..
./server
```

## Installation and deployment

## To-do

1. build a client desktop application with electron instead of pyqt

2. server test

3. installation and deployment of server
