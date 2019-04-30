//
// Created by firesWu on 2019-04-29.
//
#include <default_plugin/default_plugin.hpp>

namespace plugin{
    using namespace std;
    using namespace appbase;

    abstract_plugin& _default_plugin = app().register_plugin<default_plugin>();

    default_plugin::default_plugin() {}

    default_plugin::~default_plugin() {}

    void default_plugin::plugin_initialize() {
        cout<<"default_plugin init"<<endl;
    }

    void default_plugin::plugin_startup() {
        cout<<"default_plugin startup"<<endl;
    }

    void default_plugin::plugin_shutdown() {
        cout<<"default_plugin shutdown"<<endl;
    }

}
