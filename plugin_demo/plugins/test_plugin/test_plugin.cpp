//
// Created by firesWu on 2019-04-29.
//
#include <test_plugin/test_plugin.hpp>

namespace plugin{
    using namespace std;
    using namespace appbase;

    const static abstract_plugin& _test_plugin = app().register_plugin<test_plugin>();

    test_plugin::test_plugin() {}

    test_plugin::~test_plugin() {}

    void test_plugin::plugin_initialize() {
        cout<<"test_plugin init"<<endl;
    }

    void test_plugin::plugin_startup() {
        cout<<"test_plugin startup"<<endl;
    }

    void test_plugin::plugin_shutdown() {
        cout<<"test_plugin shutdown"<<endl;
    }

}
