#include <iostream>
#include <application.hpp>
#include <default_plugin/default_plugin.hpp>

using namespace plugin;
using namespace appbase;
using namespace std;

int main() {

    vector<string> plugins = {"plugin::test_plugin"};
    app().initialize<default_plugin>(plugins);
    app().startup();
    app().shutdown();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}