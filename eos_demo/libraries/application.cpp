//
// Created by firesWu on 2019-04-29.
//

#include <application.hpp>

namespace appbase {

application::application(){
    io_serv = make_shared<boost::asio::io_service>();
}

application::~application(){}

void application::exec() {
    std::cout<< " exec " <<std::endl;
    while( get_io_service().run_one() ){}
    std::cout<<" exit " <<std::endl;
    shutdown();
}

void application::quit() {
    _is_quiting = true;
    io_serv->stop();
}

bool application::is_quiting() const {
    return _is_quiting;
}

application& application::instance() {
    static application _app;
    return _app;
}

void application::wait_for_signal(std::shared_ptr<boost::asio::signal_set> ss) {
    ss->async_wait([this, ss](const boost::system::error_code& ec, int) {
        if(ec)
            return;
        std::cout<<" shutdown for signal "<<std::endl;
        quit();
        wait_for_signal(ss);
    });
}

// 通过 ios 拦截信号并作出相应的处理
void application::setup_signal_handling_on_ios(boost::asio::io_service& ios) {
    std::shared_ptr<boost::asio::signal_set> ss = std::make_shared<boost::asio::signal_set>(ios, SIGINT, SIGTERM, SIGPIPE);
    wait_for_signal(ss);
}

void application::startup() {

    // 在初始化 plugin 时， 启动一个 io_service 线程来拦截信号
    boost::asio::io_service startup_thread_ios;
    setup_signal_handling_on_ios( startup_thread_ios );
    std::thread startup_thread( [&startup_thread_ios]() {
        startup_thread_ios.run();
    });

    auto clean_up_signal_thread = [&startup_thread_ios, & startup_thread] {
        startup_thread_ios.stop();
        startup_thread.join();
    };


    try {
        // 启动插件
        for( auto plugin : initialized_plugins ) {
            if( is_quiting() ) return;
            plugin->startup();
        }
    } catch( ... ){
        clean_up_signal_thread();
        shutdown();
        throw ;
    }

    clean_up_signal_thread();
    setup_signal_handling_on_ios( get_io_service() );
}

void application::shutdown() {

    // 最晚开启的插件应该最先关闭
    for(auto ritr = running_plugins.rbegin();
        ritr != running_plugins.rend(); ++ritr) {
        (*ritr)->shutdown();
        plugins.erase((*ritr)->name());
    }

    running_plugins.clear();
    initialized_plugins.clear();
    plugins.clear();
    io_serv->reset();
}

abstract_plugin* application::find_plugin(const std::string& name) const{
    auto itr = plugins.find(name);
    if (itr == plugins.end()) {
       return nullptr;
    }
    return itr->second.get();
}

abstract_plugin& application::get_plugin(const std::string& name) const {
    auto ptr = find_plugin(name);
    if(!ptr){
        std::cout<<" unable find plugin " + name <<std::endl;
        throw new std::exception();
    }
    return *ptr;
}

application& app() { return application::instance(); }

}