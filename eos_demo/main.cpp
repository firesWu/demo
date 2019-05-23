#include <iostream>
#include <application.hpp>
#include <boost/bind.hpp>
#include <default_plugin/default_plugin.hpp>

using namespace plugin;
using namespace appbase;
using namespace std;

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