//
// Created by firesWu on 2019-04-30.
//
#pragma once
#include <application.hpp>

namespace plugin {
    using namespace appbase;
    using namespace std;

    class dependencies_plugin : public plugin<dependencies_plugin> {
    public:
        template <typename Lambda>
        void plugin_requires( Lambda&& l ) {
//          app().register_plugin<PLUGIN>()
        }

        dependencies_plugin();
        virtual ~dependencies_plugin();

        void plugin_initialize();
        void plugin_startup();
        void plugin_shutdown();

    };

}