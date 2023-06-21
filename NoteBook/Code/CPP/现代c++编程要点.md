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
class BaseClass{
    public:
        virtual ~BaseClass() =default;
        virtual void set(int num) =0;
        virtual std::string getString() const=0;
        //使用=0来定义纯虚方法
};
class OtherClass:public BaseClass{
    private:
        int val=0;
    public:
        ~OtherClass()=default;
        void set(int num) override{val=num;};
        std::string getString() const override{return std::to_string(val);};
};
int main()
{
    std::unique_ptr<BaseClass> c {new OtherClass{}};
    c->set(10);
    cout<<c->getString()<<endl;
}
```
#### 多态

#### 多重继承


## 单元测试
