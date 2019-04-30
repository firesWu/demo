//
// Created by firesWu on 2019-04-29.
//

#ifndef PLUGIN_DEMO_APPLICATION_HPP
#define PLUGIN_DEMO_APPLICATION_HPP

#include <plugin.hpp>
#include <map>
#include <vector>

namespace appbase {

    using namespace std;

    class application {
        public:

            template<typename... Plugin>
            bool initialize(vector<string> plugins_name){
                std::vector<abstract_plugin*> default_start_plugin = {find_plugin<Plugin>()...};

                try{
                    // 初始化默认插件
                    for(auto plugin : default_start_plugin){
                        plugin->initialize();
                    }

                    // 初始化动态配置的插件
                    for(auto plugin_name : plugins_name){
                        get_plugin(plugin_name).initialize();
                    }
                } catch(...) {
                    cout<<"init failed"<<endl;
                    return false;
                }
                return true;
            }

            void startup();
            void shutdown();

            void exec();
            void quit();
            bool is_quiting() const;

            //单例模式
            static application& instance();

            abstract_plugin* find_plugin(const std::string& name)const;
            abstract_plugin& get_plugin(const std::string& name)const;

            // 注册插件，实例化，以便通过名字便能找到该实例。
            template<typename Plugin>
            auto& register_plugin(){
                // 判断插件是否实例化过， 若有直接返回对象引用
                auto existing = find_plugin<Plugin>();
                if ( existing ){
                    return *existing;
                }

                auto plug = new Plugin();
                plugins[plug->name()].reset(plug);
                plug->register_dependencies();
                return *plug;

            }

            // 通过类去查找对象实例指针
            template<typename Plugin>
            Plugin* find_plugin()const{
                std::string name = boost::core::demangle(typeid(Plugin).name());
                return dynamic_cast<Plugin*>(find_plugin(name));
            }

            // 通过类获取对象实例引用
            template<typename Plugin>
            Plugin& get_plugin()const {
                auto ptr = find_plugin<Plugin>();
                return *ptr;
            }

        protected:
            void plugin_initialized(abstract_plugin& plug){ initialized_plugins.push_back(&plug); }
            void plugin_started(abstract_plugin& plug){ running_plugins.push_back(&plug); }

        private:
            bool _is_quiting = false; // 是否退出
            std::vector<abstract_plugin*> initialized_plugins; // 经过初始化的插件
            std::vector<abstract_plugin*> running_plugins; // 成功运行的插件
            std::map<std::string, std::unique_ptr<abstract_plugin>> plugins; // 类名与插件对象指针的映射

        // plugin 需要操作私有变量
        template<typename Impl>
        friend class plugin;

    };

    // 获取 application 对象引用
    application& app();

    template <typename Impl>
    class plugin : public abstract_plugin {

        public:
            plugin():_name(boost::core::demangle((typeid(Impl).name()))){}
            virtual ~plugin(){}

            // 获取插件的状态
            virtual state get_state()const override{ return _state; }

            // 获取插件名称
            virtual const std::string& name()const override { return _name; }

            // 先注册插件所依赖的插件
            virtual void register_dependencies(){
                static_cast<Impl*>(this)->plugin_requires([&](auto& plug){});
            }

            // 初始化插件
            virtual void initialize() override {
                if (_state == registered ) {
                    _state = initialized;
                    // 先初始化依赖插件
                    static_cast<Impl*>(this)->plugin_requires([&](auto& plug){ plug.initialize(); });
                    static_cast<Impl*>(this)->plugin_initialize();
                    app().plugin_initialized(*this);
                }

                assert(_state == initialized);// 初始化失败抛异常。
            }

            // 启动插件
            virtual void startup() override {
                if ( _state == initialized ) {
                    _state = started;
                    // 先启动依赖插件
                    static_cast<Impl*>(this)->plugin_requires([&](auto& plug){ plug.startup(); });
                    static_cast<Impl*>(this)->plugin_startup();
                    app().plugin_started(*this);
                }
                assert(_state == started);// 启动失败抛异常。
            }

            // 关闭插件，插件关闭时应跟初始化相反的顺序。
            virtual void shutdown() override {
                if (_state == started) {
                    _state = stopped;
                    static_cast<Impl*>(this)->plugin_shutdown();
                }
            }

        protected:
            plugin(const std::string& name ):_name(name){}

        private:
            state _state = abstract_plugin::registered;
            std::string _name;

        };

}


#endif //PLUGIN_DEMO_APPLICATION_HPP
