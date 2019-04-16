#include <iostream>
#include <vector>
#include <ctime>
#include <type_traits>

using namespace std;

class demo {
    public:
        string value;
        demo():value(""){}
        demo( string b ):value(b){
            cout<<" call constructor " <<endl;
        }

        demo( const demo& b ):value(b.value){
            cout<<" call copy constructed"<<endl;
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

int main() {

//    test1();
//    test2();
//    test3();
    test4();
    return 0;
}