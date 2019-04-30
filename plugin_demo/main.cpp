#include <iostream>
#include <application.hpp>
#include <default_plugin/default_plugin.hpp>

using namespace plugin;
using namespace appbase;
using namespace std;

int main() {
    // 这里插件的配置就直接通过 plugins 数组来配置， 就不使用配置文件了
    vector<string> plugins = {"plugin::test_plugin"};
    // 初始化插件
    app().initialize<default_plugin>(plugins);
    // 启动容器
    app().startup();
    // 关闭容器
    app().shutdown();
    return 0;
}