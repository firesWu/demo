//
// Created by firesWu on 2019-04-29.
//

#ifndef PLUGIN_DEMO_TEST_PLUGIN_HPP
#define PLUGIN_DEMO_TEST_PLUGIN_HPP

#include <application.hpp>
#include <dependencies_plugin/dependencies_plugin.hpp>

namespace plugin {
    using namespace appbase;
    using namespace std;

    class test_plugin : public plugin<test_plugin> {
        public:
        template <typename Lambda>
        void plugin_requires( Lambda&& l ) {
            auto& dp = app().register_plugin<dependencies_plugin>();
            l(dp);
       }

        test_plugin();
        virtual ~test_plugin();

        void plugin_initialize();
        void plugin_startup();
        void plugin_shutdown();

    };

}

#endif //PLUGIN_DEMO_TEST_PLUGIN_HPP
