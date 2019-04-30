//
// Created by firesWu on 2019-04-29.
//
#include <dependencies_plugin/dependencies_plugin.hpp>

namespace plugin{
    using namespace std;
    using namespace appbase;

    const static abstract_plugin& _dependencies_plugin = app().register_plugin<dependencies_plugin>();

    dependencies_plugin::dependencies_plugin() {}

    dependencies_plugin::~dependencies_plugin() {}

    void dependencies_plugin::plugin_initialize() {
        cout<<"dependencies_plugin init"<<endl;
    }

    void dependencies_plugin::plugin_startup() {
        cout<<"dependencies_plugin startup"<<endl;
    }

    void dependencies_plugin::plugin_shutdown() {
        cout<<"dependencies_plugin shutdown"<<endl;
    }

}
