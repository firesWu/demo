## 异步框架

### 引入
上次实现了 EOS 的插件机制， 这次我们在这个基础上再加点东西上去。
目前 EOS 的主流程是单线程的，也有同学看过以前的一些技术文章，里面会提到用 cycle, shard 的方式来实现多线程来 push_trx， 但这部分已经被移除了。 这种方式来实现多线程的前提是能在执行前分离出完全无关的 trx, 但是以现在智能合约的灵活性( recipient 、inline action 和 defer trx 机制使得 trx 的 一个 action 能含有多个智能合约的内容 ) 在执行前很难判断 2 个 trx 时候存在关系， 使得这种实现多线程的方式也无法实现。

既然是单线程，又要处理多个生产端的任务( 例如 http，p2p 请求)，并且保证一定的性能，那就要肯定需要实现一个异步框架。

### 异步框架的实现
EOS 异步框架是通过实现一个任务队列， 然后往队列中 post 任务来实现， 而消费者不停地从中提取 task 并且执行。当然 EOS 用了现成的异步框架 boost::asio 。

#### asio
它是基于操作系统提供的异步机制( 底层封装了 select/ epoll/ kqueue/ overlapped, 使用各种操作系统 )，采用前摄器设计模式来实现可移植的异步操作。 想具体了解的同学可以查阅 https://www.boost.org/doc/libs/1_70_0/doc/html/boost_asio/overview/core/async.html

### 源码介绍
异步框架的添加比较简单， 因为 asio 已经封装得比较完善了。

#### 添加 boost 依赖
首先在 CMakeLists.txt 添加对 boost::asio 的支持
```
// CMakeLists.txt
target_link_libraries( eos_demo
        // ...
        boost_system
        )
```

#### 创建异步框架对象
```
// libraries/include/application.hpp
// 创建 io_service， 它是 asio 中的核心类，实现了任务队列，通过 post 添加任务， run 执行任务。
std::shared_ptr<boost::asio::io_service> io_serv;

// libraries/application.cpp
// EOS 的对象基本通过 shared_ptr 来管理，不用手动的释放对象资源。
application::application(){
    io_serv = make_shared<boost::asio::io_service>();
}
```


#### 启动异步框架
```
// libraries/application.cpp
// 在 exec() 时启动 io_service
void application::exec() {
    std::cout<< " exec " <<std::endl;
    get_io_service().run();
    shutdown();
}
```

#### 捕捉信号，退出进程 gracefully
```
// libraries/application.cpp
// io_service::run 是一个阻塞方法，里面其实是个无限循环，没有任务时会阻塞，获取到任务时执行，之后进入下一次阻塞。
// 所以需要需要利用 io_service 去捕捉信号。
// 通过 ios 拦截信号并作出相应的处理
void application::setup_signal_handling_on_ios(boost::asio::io_service& ios) {
    std::shared_ptr<boost::asio::signal_set> ss = std::make_shared<boost::asio::signal_set>(ios, SIGINT, SIGTERM, SIGPIPE);
    wait_for_signal(ss);
}

void application::wait_for_signal(std::shared_ptr<boost::asio::signal_set> ss) {
    ss->async_wait([this, ss](const boost::system::error_code& ec, int) {
        if(ec)
            return;
        std::cout<<" shutdown for signal "<<std::endl;
        quit();
        // 为什么捕捉完信号还要再捕捉一次呢？  防止用户多次触发，无法退出 gracefully
        wait_for_signal(ss);
    });
}

void application::quit() {
   my->_is_quiting = true;
   // 退出 io_service::run()
   io_serv->stop();
}
```

#### 向 io_service 提交请求
EOS 中向 io_service post 任务的主要有 http_plugin 和 net_plugin， 这里直接在 main.cpp 模拟这样的 post, 就不具体实现了。

```
// main.cpp
void http_request( int i ){
    std::cout<< " http request " << i <<endl;
}

void p2p_request( int i ){
    std::cout<< " p2p request " << i <<endl;
}

int main() {
    // 这里插件的配置就直接通过 plugins 数组来配置， 就不使用配置文件了
    vector<string> plugins = {"plugin::test_plugin"};
    // 初始化插件
    app().initialize<default_plugin>(plugins);
    // 启动容器
    app().startup();
    // 模拟 http , p2p 向 io_service post 任务。
    app().get_io_service().post( boost::bind(http_request, 1) );
    app().get_io_service().post( boost::bind(p2p_request, 1) );
    app().get_io_service().post( boost::bind(http_request, 2) );
    app().get_io_service().post( boost::bind(p2p_request, 2) );
    app().get_io_service().post( boost::bind(http_request, 3) );
    app().get_io_service().post( boost::bind(p2p_request, 3) );
    app().get_io_service().post( boost::bind(http_request, 4) );
    app().get_io_service().post( boost::bind(p2p_request, 4) );
    // 执行
    app().exec();
    return 0;
}
```
执行结果：
```shell
default_plugin init
dependencies_plugin init
test_plugin init
default_plugin startup
dependencies_plugin startup
test_plugin startup
 exec 
 http request 1
 p2p request 1
 http request 2
 p2p request 2
 http request 3
 p2p request 3
 http request 4
 p2p request 4
^C shutdown for signal 
 exit 
test_plugin shutdown
dependencies_plugin shutdown
default_plugin shutdown
```
从结果中可以看出向  io_service post 任务成功，并且成功捕捉到 ctrl + c 触发的信号。


### 总结
其实读过 EOS 源码的同学都知道本文的 demo 跟 EOS 源码差不多， 主要通过这种逐渐搭建的方式来让同学们熟悉 EOS 的主要框架和具体的实现思想。

具体代码: https://github.com/firesWu/demo/tree/master/plugin_demo ( 不要忘记 follow 哟)
