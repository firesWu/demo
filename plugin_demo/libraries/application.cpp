//
// Created by firesWu on 2019-04-29.
//

#include <application.hpp>

namespace appbase {

void application::quit() {
    _is_quiting = true;
}

bool application::is_quiting() const {
    return _is_quiting;
}

application& application::instance() {
    static application _app;
    return _app;
}

void application::startup() {

    // 因为没加入其它功能，所以只有启动插件这个操作
    // 启动插件
    for( auto plugin : initialized_plugins ) {
        if( is_quiting() ) return;
        plugin->startup();
    }

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