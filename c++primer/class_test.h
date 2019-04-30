//
// Created by 吴远 on 2019-04-28.
//

#ifndef SECTION3_CLASS_TEST_H
#define SECTION3_CLASS_TEST_H

class abstract_plugin {
public:
    virtual void startup() = 0;
    virtual void get_name() = 0;
};


template <typename Impl>
class plugin : public abstract_plugin {
public:
    virtual void startup(){
        static_cast<Impl*>(this)->plugin_start();
    }

};

class test_plugin : public plugin<test_plugin> {
public:
    void plugin_start(){
        cout<<"test_plugin"<<endl;
    }

};

#endif //SECTION3_CLASS_TEST_H
