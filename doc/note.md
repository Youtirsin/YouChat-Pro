# Notes

## References

* [#Web服务器-原始版本 (qq.com)](https://mp.weixin.qq.com/mp/appmsgalbum?__biz=MzAxNzU2MzcwMw==&action=getalbum&album_id=1339230165934882817&scene=173&from_msgid=2649274278&from_itemidx=4&count=3&nolastread=1#wechat_redirect)

* [(22条消息) reactor和proactor模式_蚂蚁的专栏-CSDN博客_reactor模式和proactor](https://blog.csdn.net/caiwenfeng_for_23/article/details/8458299)

* [Reactor模式，或者叫反应器模式 - daimojingdeyu - ITeye博客](https://www.iteye.com/blog/daimojingdeyu-828696)

* 

## 摘要

半同步/半异步模式工作流程

> - 同步线程用于处理客户逻辑
> 
> - 异步线程用于处理I/O事件
> 
> - 异步线程监听到客户请求后，就将其封装成请求对象并插入请求队列中
> 
> - 请求队列将通知某个工作在**同步模式的工作线程**来读取并处理该请求对象

半同步/半反应堆工作流程（以Proactor模式为例）

> - 主线程充当异步线程，负责监听所有socket上的事件
> 
> - 若有新请求到来，主线程接收之以得到新的连接socket，然后往epoll内核事件表中注册该socket上的读写事件
> 
> - 如果连接socket上有读写事件发生，主线程从socket上接收数据，并将数据封装成请求对象插入到请求队列中
> 
> - 所有工作线程睡眠在请求队列上，当有任务到来时，通过竞争（如互斥锁）获得任务的接管权

Reactor和Proactor模式的主要区别就是真正的读取和写入操作是有谁来完成的，Reactor中需要应用程序自己读取或者写入数据，而Proactor模式中，应用程序不需要进行实际的读写过程，它只需要从缓存区读取或者写入即可，操作系统会读取缓存区或者写入缓存区到真正的IO设备.

## Epoll

    epoll 在边沿模式下，必须要将套接字设置为**非阻塞模式**，但是，这样就会引发另外的一个 bug，在非阻塞模式下，循环地将读缓冲区数据读到本地内存中，当缓冲区数据被读完了，调用的 read()/recv() 函数还会继续从缓冲区中读数据，此时函数调用就失败了，返回 - 1，对应的全局变量 errno 值为 EAGAIN 或者 EWOULDBLOCK 如果打印错误信息会得到如下的信息：Resource temporarily unavailable

### 线程池设计

# 问题

> * 模板定义和声明不能分开文件

## Jsoncpp

> - [jsoncpp的常见用法 - 简书 (jianshu.com)](https://www.jianshu.com/p/8bb28b570647/)

## MySQL C++

> - [(22条消息) c++连接mysql编程(mysq-connector/c++)_jlaij的博客-CSDN博客](https://blog.csdn.net/chinabhlt/article/details/47726421)
