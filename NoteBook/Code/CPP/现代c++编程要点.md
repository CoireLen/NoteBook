## 基本操作
```cpp
    vector<int> ti{1,2,3,4,5};// 建立数据可用省略=号
    for_each(ti.begin(),ti.end(),[](auto x){cout<<x<<endl;});
```
## switch 语句
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
## 指针
### 智能指针
```cpp
    //cpp17
    auto intx=make_unique<int>(2);
    cout<<*intx<<endl;
    auto inty=make_shared<int>(10);
    cout <<*inty<<endl;
```
在新版的c++中因该使用智能指针来代替传统指针；

## auto
```cpp
    auto a={1,2,3,4}; 
    //auto b={1,2.0,3,4};
    //auto a{1,2,3};
    auto a{1};
```
## Class 类
### 基类继承派生
### 友元

## 单元测试
