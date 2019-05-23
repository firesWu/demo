//
// Created by firesWu on 2019-04-29.
//

#ifndef PLUGIN_DEMO_DEFAULT_PLUGIN_HPP
#define PLUGIN_DEMO_DEFAULT_PLUGIN_HPP

#include <application.hpp>

namespace plugin {
    using namespace appbase;
    using namespace std;

    class default_plugin : public plugin<default_plugin> {
    public:
        template <typename Lambda>
        void plugin_requires( Lambda&& l ) {
//          app().register_plugin<PLUGIN>()
        }

        default_plugin();
        virtual ~default_plugin();

        void plugin_initialize();
        void plugin_startup();
        void plugin_shutdown();

    };

}

#endif //PLUGIN_DEMO_DEFAULT_PLUGIN_HPP
