//
// Created by firesWu on 2019-04-29.
//

#ifndef PLUGIN_DEMO_PLUGIN_HPP
#define PLUGIN_DEMO_PLUGIN_HPP
#include <iostream>
#include <string>
#include <boost/core/demangle.hpp>

namespace appbase {

    class application;

    class abstract_plugin {
        public:
            enum state {
                registered,
                initialized,
                started,
                stopped
            };

            virtual  ~abstract_plugin(){}
            virtual state get_state()const = 0;
            virtual const std::string& name()const = 0;
            virtual void initialize() = 0;
            virtual void startup() = 0;
            virtual void shutdown() = 0;
    };

}


#endif //PLUGIN_DEMO_PLUGIN_HPP
