YouChat-Pro

[English](./README.md)

Linux下的C++即时通讯应用服务器。

- 使用Epoll IO多路复用

- 使用任务队列线程池竞争处理任务

- 使用Redis进行缓存

- 对mysqlclient进行简单封装，实现数据库连接池

- 使用PyQT实现跨平台的客户端桌面应用（暂未放入项目）

## 依赖

- CMake

- libjsoncpp-dev

- libmysqlclient-dev

- libhiredis-dev

- redis-plus-plus

- C++ 17

## 运行

### 数据库

#### 创建数据库和表

> - 见/sql/create.sql

#### 配置数据库连接

> - 暂时在Server.h

### 编译和运行

```shell
mkdir build
cd build && cmake ..
./server
```

## 打包与部署
