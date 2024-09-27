## 字符串

## 基本操作
```cpp
    vector<int> ti{1,2,3,4,5};// 建立数据可用省略=号
    for_each(ti.begin(),ti.end(),[](auto x){cout<<x<<endl;});
```
### switch 语句
```cpp
    switch (x)
    {
    case 1:
        [[fallthrough]] //使用[[fallthrough]]来指定是有意不写break
    case 2:
        //do something
        break;
    }
```
### 指针
#### 智能指针
```cpp
    //cpp17
    auto intx=make_unique<int>(2);
    cout<<*intx<<endl;
    auto inty=make_shared<int>(10);
    cout <<*inty<<endl;
```
在新版的c++中因该使用智能指针来代替传统指针；
#### 引用
使用引用,而尽量不使用指针
```cpp
/**
 * 输出字符串并修改其值
 * 
 * 此函数接收一个引用字符串参数，在其末尾添加" outed"，然后输出修改后的字符串
 * 它展示了如何在函数内部修改传入的字符串，并保持外部的引用字符串同步更新
 * 
 * @param a 一个引用字符串参数，将在函数内部被修改并输出
 */
void print(std::string &a){
    std::cout<<a<<std::endl;
    a+=" outed";
}

/**
 * 主函数
 * 
 * 初始化一个字符串，然后两次调用print函数，观察字符串值的变化并输出
 * 这个例子说明了通过引用传递字符串参数，可以在函数之间共享和修改数据
 * 
 * @return 返回0，表示程序成功执行
 */
int main()
{
    std::string a{"123"};
    print(a); // 第一次调用print，输出并修改字符串a
    print(a); // 第二次调用print，再次输出并修改字符串a
}
```

### auto
```cpp
    auto a={1,2,3,4}; 
    //auto b={1,2.0,3,4};
    //auto a{1,2,3};
    auto a{1};
```
## Class 类
```cpp
export class SomeClass{
	void fn();//默认是私有
	public:
		//公有的
	private:
		//私有的
}
export struct somestruct{
	//默认公有
	private:
	//私有
}
```
#### 显式设置构造函数
```cpp
class MyClass{
	double m_value,
	double m_foo,
	MyClass(const MyClass& src)=default; //设置为默认拷贝函数
	MyClass(const MyClass& src)=delete; //设置不允许拷贝该类
}
MyClass::MyClass(double val):m_value{val},m_foo{val}
{
	
}
```
#### 初始化列表构造函数
```cpp
class Mclass{
	public:
	Mclass(initializer_list<T> args){
	for (const auto & val:args){
		//do_something
		}
	}
}
Mclass a{1,2,3,4,5,6,7,8}
```
使用initializer_list<>
#### 委托构造
```cpp
class Mclass{
	Mclass(t):OtherClass{t}{}
}
```
#### explicit 禁用隐式转换
```cpp
class MClass{
	explicit Mclass(String_View a){};
}
//MClass{"asd"sv};
//将无法通过编译
```
#### 赋值函数
```cpp
class Mclass{
	public:
		Mclass& operator=(const Mclass& rhs){
		//do Something;
		}
}
```
关于[[现代c++编程要点#显式设置构造函数]]

### 友元
```cpp
class Mclass{
	friend class OtherClass;//类
	friend void OtherClass::fn();//类函数
	friend void fn(); //函数
}
```
定义友元后 private 的数据将会被暴露给指定的类/函数
#### noexcept 永不抛出异常
```cpp
class Mclass{
	public:
	void swap(Mclass& first,Mclass& second) noexcept; //如果该函数出现异常将终止程序
}
```
#### 右值引用
右值一般为临时值
```cpp
int a{1},b{2};
int&& c{a+b};
void fn(int && val){};
fn(std::move(a));
fn(a+b);
//直接调用fn(a)因为其是左值所以会失败
```
使用右值引用时，会将拷贝数据的操作优化为移动数据，将提升性能

### 继承
```cpp
class Baseclass{
//something..
}
class otherclass:public Baseclass{
//something..
}
```
#### 禁用继承
```cpp
class myclass final{
//使用final禁用继承
}
```
#### virtual
```cpp
class Baseclass{
	virtual void someMethod(){};
}
class otherclass:public Baseclass{
	void someMethod() override;
}
```
派生类使用时需要删除virtual并在最后写上override；如果需要在下一层派生中使用则任然需要添加virtual。
使用时如果不添加override将会建立一个一样的方法函数，当基类进行改变的时候该方法将会被调用，而导致行为出错。
如果忘记使用virtual建立方法函数时，将会导致派生类重写函数时隐藏基类方法函数。
#### 禁用重写
```cpp
class Baseclass{
	void someMethod() override final;
}
```
如此这般，在派生类中重写函数将会报错；
#### 纯虚方法和抽象基类
```cpp
// 定义一个基类，用于被其他类继承
class BaseClass{
  public:
    // 虚拟析构函数，确保派生类的资源能够正确释放
    virtual ~BaseClass() =default;
    
    // 纯虚函数，强制派生类实现设置数值的功能
    virtual void set(int num) =0;
    
    // 纯虚函数，强制派生类实现获取字符串的功能
    virtual std::string getString() const=0;
    // 使用=0来定义纯虚方法，表示BaseClass是一个抽象类，不能被实例化
};

// OtherClass类继承自BaseClass，实现set和getString方法
class OtherClass:public BaseClass{
  private:
    int val=0; // 用于存储设置的数值，默认值为0
  
  public:
    // 默认析构函数，不需要额外实现
    ~OtherClass()=default;
    
    // 实现set方法，重写基类的虚函数
    void set(int num) override{val=num;};
    
    // 实现getString方法，重写基类的虚函数
    std::string getString() const override{return std::to_string(val);};
};

// 主函数
int main()
{
  // 使用智能指针指向OtherClass对象，通过基类指针操作派生类对象
  std::unique_ptr<BaseClass> c {new OtherClass{}};
  
  // 调用set方法设置val的值
  c->set(10);
  
  // 调用getString方法获取并打印val的值
  cout<<c->getString()<<endl;
}
```
#### 多重继承
```cpp
//多重继承
#include <iostream>

// 定义类 class1
class class1 {
public:
    void method() {
        std::cout << "Method from class1" << std::endl;
    }
};

// 定义类 class2
class class2 {
public:
    void method() {
        std::cout << "Method from class2" << std::endl;
    }
};

// 定义多重继承的类 myclass
class myclass : public class1, public class2 {
public:
    // 重定义同名方法
    void method() {
        // 明确指定从哪个基类调用方法
        class1::method();
        class2::method();
    }
};

int main() {
    myclass obj;

    // 调用重定义的方法
    obj.method();

    // 使用作用域解析运算符调用特定基类的方法
    obj.class1::method();  // 调用 class1 的方法
    obj.class2::method();  // 调用 class2 的方法

    return 0;
}
```
## 测试
### 断言
```cpp
#include <cassert>
#include <string>
#include <vector>
// 单元测试函数
void run_assert_tests() {
    // 示例 1: 检查整数相等
    int a = 5;
    int b = 5;
    assert(a == b);  // 断言 a 和 b 相等

    // 示例 2: 检查字符串相等
    std::string s1 = "hello";
    std::string s2 = "hello";
    assert(s1 == s2);  // 断言 s1 和 s2 相等

    // 示例 3: 检查数组相等
    int arr1[] = {1, 2, 3};
    int arr2[] = {1, 2, 3};
    assert(arr1[0] == arr2[0] && arr1[1] == arr2[1] && arr1[2] == arr2[2]);  // 断言数组元素相等

    // 示例 4: 检查指针不为空
    int* ptr = new int(10);
    assert(ptr != nullptr);  // 断言指针不为空
    delete ptr;  // 释放内存

    // 示例 5: 检查布尔值
    bool flag = true;
    assert(flag);  // 断言 flag 为 true

    // 示例 6: 检查浮点数相等
    double x = 3.14;
    double y = 3.14;
    assert(x == y);  // 断言 x 和 y 相等

    // 示例 7: 检查字符相等
    char c1 = 'a';
    char c2 = 'a';
    assert(c1 == c2);  // 断言 c1 和 c2 相等

    // 示例 8: 检查字符串长度
    std::string str = "hello";
    assert(str.length() == 5);  // 断言字符串长度为 5

    // 示例 9: 检查容器大小
    std::vector<int> vec = {1, 2, 3};
    assert(vec.size() == 3);  // 断言向量大小为 3

    // 示例 10: 检查枚举值
    enum Color { Red, Green, Blue };
    Color color = Green;
    assert(color == Green);  // 断言 color 为 Green
}

int main() {
    // 调用单元测试函数
    run_assert_tests();

    return 0;
}
```

### Boost.Test

```cpp
#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>

// 定义测试用例
BOOST_AUTO_TEST_SUITE(AssertTests)

// 示例 1: 检查整数相等
BOOST_AUTO_TEST_CASE(test_int_equality) {
    int a = 5;
    int b = 5;
    BOOST_CHECK_EQUAL(a, b);  // 断言 a 和 b 相等
}

// 示例 2: 检查字符串相等
BOOST_AUTO_TEST_CASE(test_string_equality) {
    std::string s1 = "hello";
    std::string s2 = "hello";
    BOOST_CHECK_EQUAL(s1, s2);  // 断言 s1 和 s2 相等
}

// 示例 3: 检查数组相等
BOOST_AUTO_TEST_CASE(test_array_equality) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {1, 2, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(arr1, arr1 + 3, arr2, arr2 + 3);  // 断言数组元素相等
}

// 示例 4: 检查指针不为空
BOOST_AUTO_TEST_CASE(test_pointer_non_null) {
    int* ptr = new int(10);
    BOOST_CHECK_NE(ptr, nullptr);  // 断言指针不为空
    delete ptr;  // 释放内存
}

// 示例 5: 检查布尔值
BOOST_AUTO_TEST_CASE(test_boolean_value) {
    bool flag = true;
    BOOST_CHECK(flag);  // 断言 flag 为 true
}

// 示例 6: 检查浮点数相等
BOOST_AUTO_TEST_CASE(test_float_equality) {
    double x = 3.14;
    double y = 3.14;
    BOOST_CHECK_CLOSE(x, y, 0.001);  // 断言 x 和 y 相等（允许小误差）
}

// 示例 7: 检查字符相等
BOOST_AUTO_TEST_CASE(test_char_equality) {
    char c1 = 'a';
    char c2 = 'a';
    BOOST_CHECK_EQUAL(c1, c2);  // 断言 c1 和 c2 相等
}

// 示例 8: 检查字符串长度
BOOST_AUTO_TEST_CASE(test_string_length) {
    std::string str = "hello";
    BOOST_CHECK_EQUAL(str.length(), 5);  // 断言字符串长度为 5
}

// 示例 9: 检查容器大小
BOOST_AUTO_TEST_CASE(test_vector_size) {
    std::vector<int> vec = {1, 2, 3};
    BOOST_CHECK_EQUAL(vec.size(), 3);  // 断言向量大小为 3
}

// 示例 10: 检查枚举值
BOOST_AUTO_TEST_CASE(test_enum_value) {
    enum Color { Red, Green, Blue };
    Color color = Green;
    BOOST_CHECK_EQUAL(color, Green);  // 断言 color 为 Green
}

BOOST_AUTO_TEST_SUITE_END()

int main(int argc, char* argv[]) {
    ::boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
    return 0;
}
```