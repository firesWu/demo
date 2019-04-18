#include <iostream>
#include <vector>
#include <ctime>
#include <type_traits>
#include <bitset>

using namespace std;

class demo {
    public:
        string value;
        demo():value(""){}
        demo( string b ):value(b){
            cout<<" call constructor " <<endl;
        }


        demo( demo& b ):value(b.value){
            cout<<" call copy constructed"<<endl;
        }

        demo( const demo& b ):value(b.value){
            cout<<" call copy const constructed"<<endl;
        }

        demo( demo&& b ){
            value = move(b.value);
            cout<<" call move constructed"<<endl;
        }

        ~demo(){
            cout<<" destroy demo"<<endl;
        }


};


void test1(){
    cout<< "===== test 01 =====" <<endl;

    clock_t start, end;
    int count = 1;

    cout<<"push_back"<<endl;
    vector<demo> list2;
    start = clock();
    for( int i = 0; i < count ; i++ ){
        demo d2("abcdefasdfasdfadsfs");
        list2.push_back(d2);
    }
    end = clock();
    cout<< (end - start) << endl;

    cout<<"emplace_back"<<endl;
    vector<demo> list;
    start = clock();
    for( int i = 0; i < count ; i++ ){
//        demo d("abcdefasdfasdfadsfs");
        list.emplace_back("abcdefasdfasdfadsfs");
    }
    end = clock();
    cout<< (end - start) << endl;

    return ;
}

void test2(){
    cout<< "===== test 02 =====" <<endl;

    // move 会将 str 的内容转移到 str2. 此时 str 就成了空字符串
    string str = "abcd";
    cout<<(str)<<endl;
    string str2 = move(str);
    cout<<(str)<<endl;
    cout<<(str2)<<endl;

    int ia = 10;
//    int&& ib = move(ia);
    int&& ib = int(10);
    cout<<&ib<<endl;

    demo b("ab");
    cout<<(&b.value)<<endl;
    auto s = std::move(b);
    cout<<(&s.value)<<endl;
    cout<<"test2 end"<<endl;

    return ;
}

class HasPtrMem {
public:
    HasPtrMem():d(new int(0)){
        cout<<"construct"<<endl;
    }

    // 增加深拷贝函数， 避免 d 指针成为悬挂指针
    HasPtrMem(HasPtrMem& a):d(new int(*a.d)){
        cout<<"construct"<<endl;
    }

    ~HasPtrMem(){
        delete d;
        cout<<"destrcut"<<endl;
    }
    int * d;
};

// 浅拷贝 深拷贝分析。
void test3(){
    cout<< "===== test 03 =====" <<endl;

    HasPtrMem a;
    HasPtrMem b(a);
    cout<< a.d <<endl;

    // 浅拷贝会导致释放 2 次同样的指针
    cout<< b.d <<endl;

}

template< typename T>
void iamforward(T&& t){
    iruncode(forward<T>(t));
}

template< typename T>
void iruncode(T&& t){
    cout<< "rvalue ref" <<endl;
}

template< typename T>
void iruncode(T& t){
    cout<< "lvalue ref" <<endl;
}

template< typename T>
void iruncode(const T& t){
    cout<< "const lvalue ref" <<endl;
}

template< typename T>
void iruncode(const T&& t){
    cout<< "const rvalue ref" <<endl;
}

void iruncode2( demo& d){
    d.value="test";
}

void test4(){
    cout<< "===== test 04 =====" <<endl;
    demo b("hi");
    const demo bb("bi");

    iamforward(b);
    iamforward(move(b));
    iamforward(bb);
    iamforward(move(bb));

    demo && b3 = move(b);
    iruncode2(b3);
    cout<<b3.value<<endl;
}


// test section3 bitset
void test5(){
    cout<< "===== test 05 =====" <<endl;
    // 内部存储使用 size_t 类型
    bitset<100> bs(4);
    bitset<300> bs2("100");
    cout<< bs <<endl;
    cout<< bs2.size() <<endl;

    cout<< numeric_limits<size_t>::max()<<endl;
    cout<< numeric_limits<unsigned long>::max()<<endl;
    cout<< numeric_limits<unsigned long long>::max()<<endl;

    cout<< sizeof(size_t) <<endl;
    cout<< sizeof(unsigned long)<<endl;
    cout<< sizeof(unsigned long long) <<endl;

    int i =1;
    i = (i = 3*i, i*5);
    cout<<i<<endl;

}

// test section5 cast

class base {
public:
    virtual void test(){
        cout<< "i'm father" <<endl;
    }
};

class son : public base {
public:
//    virtual void test(){
//        cout<< " i'm son"<<endl;
//    }

    void test2(){
        cout<< "hi" <<endl;
    }
};

void test6(){
    cout<< "===== test 06 =====" <<endl;
    // dynamic_cast
    cout<<"dynamic_cast"<<endl;
    {
        cout<<"上行转换"<<endl;
        son * s = new son();
        s->test();
        s->test2();

        auto b = dynamic_cast<base*>(s);
        b->test();
        auto b2 = s;
        b2->test();
    }
    {
        cout<<"下行转换"<<endl;
        base * b = new son();
        b->test();

        auto s = dynamic_cast<son*>(b);
        s->test();
        s->test2();
    }
    cout<<"reinterpret_cast"<<endl;
    {
        int * ptr = new int(97);
        char * cptr = reinterpret_cast<char*>(ptr);
        cout<<*cptr<<endl;
    }

}


//demo& getTemp(){
//    demo temp("10aa");
//    return temp;
//}

shared_ptr<demo> getTempPtr(){
    shared_ptr<demo> s_ptr = make_shared<demo>("100aa");
    return s_ptr;
}

void test7(){
    cout<< "===== test 07 =====" <<endl;
//    {
//        auto& i = getTemp();
//        cout<<i.value<<endl;
//    }

    {
        auto ptr = getTempPtr();
        cout<<ptr->value<<endl;
    }

}

// 智能指针测试

class B;
class A {
public:
    B* b;
    shared_ptr<B> b2;
    weak_ptr<B> b3;

    A(){}
    A(B* _b):b(_b){}

    void setB(B* _b){
        b = _b;
    }

    void setB2(shared_ptr<B>& _b){
        b2 = _b;
    }

    void setB3(const weak_ptr<B>& _b){
        b3 = _b;
    }

    ~A(){
        cout<<"A destory"<<endl;
    }
};

class B {
public:
    A* a;
    shared_ptr<A> a2;
    weak_ptr<A> a3;

    B(){}
    B(A* _a):a(_a){}

    void setA(A* _a){
        a = _a;
    }

    void setA2(shared_ptr<A>& _a){
        a2 = _a;
    }

    void setA3(const weak_ptr<A>& _a){
        a3 = _a;
    }

    ~B(){
        cout<<"B destory"<<endl;
    }
};

void test8(){
    cout<< "===== test 08 =====" <<endl;
    // 直接销毁，不会管对象之间是否还有引用
    {
        cout<< "正常写法" <<endl;
        A a = A();
        B b =B();
        a.setB(&b);
        b.setA(&a);
    }

    // 无法销毁，对象之间存在循环引用
    {
        cout << "循环引用写法" << endl;
        shared_ptr<A> a2 = make_shared<A>();
        shared_ptr<B> b2 = make_shared<B>();
        a2->setB2(b2);
        b2->setA2(a2);
        cout<<a2.use_count()<<endl;
        cout<<b2.use_count()<<endl;
    }

    // 正常销毁对象
    {
        cout << "弱指针写法" << endl;
        shared_ptr<A> a2 = make_shared<A>();
        shared_ptr<B> b2 = make_shared<B>();
        a2->setB3(b2);
        b2->setA3(a2);
        cout<<a2.use_count()<<endl;
        cout<<b2.use_count()<<endl;
    }

}

int main() {

//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
//    test7();
    test8();
    return 0;
}