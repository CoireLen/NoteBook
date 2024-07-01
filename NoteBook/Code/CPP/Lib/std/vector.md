### 创建vector
```cpp
#include <vector>
#include <string>
using std::vector;
using std::string;

vector<int> vi(10,100); //建立vector 其中包含10个100;
vector<string> vs(10,"hallo"); //建立vector 其中包含10个"hallo"

vector<int> vi2{1,2,3,4,5};// 包含1,2,3,4,5 这几个数字

std::for_each(vi.begin(),vi.end(),[](int x){printf("%d ",x);});//输出
std::for_each(vs.begin(),vs.end(),[](string x){printf("%s ",x.c_str());});//输出
```
### assgin() 重新设置内容
```cpp
vi.assign(5,123); //重新设置vi为5个123
std::for_each(vi.begin(),vi.end(),[](int x){printf("%d ",x);});//输出
```

### swap()内容交换

```cpp
printf("\nvi:%x vi2:%x",vi.data(),vi2.data());

vi.swap(vi2);//交换数据

printf("\nvi:%x vi2:%x",vi.data(),vi2.data());
//实际上只是交换了指针以及size的数据
```
### 比较
```cpp
vi.assign(10,10);
vi2.assign(10,10);

printf("\n%d",vi==vi2?1:0); //在长度相等时比较其中的数据

vi[9]=1;

printf("\n%d",vi>vi2?1:0);

vi[9]=11;

printf("\n%d",vi>vi2?1:0);

vi.assign(10,10);
vi.push_back(-1);

printf("\n%d",vi==vi2?1:0);//在长度不等时是如何进行比较的?
```
## 获取数据
### 通过迭代器
```cpp
vector<int> vi2{1,2,3,4,5};// 包含1,2,3,4,5 这几个数字

auto iter=std::begin(vi2);//int *//输出1
auto riter=std::rbegin(vi2);//int * //输出5
auto citer=std::cbegin(vi2)+3;//const int * //输出4 (随机迭代器可以通过+ - 实现类似指针的效果)

printf("%d %d %d\n",*iter,*citer,*riter);// 1 4 5

*iter +=10;

//*citer +=10;//表达式必须是可修改的左值

printf("%d %d\n",*iter,*citer); //11 4

auto eiter =std::end(vi2)-1;//若 不减去1 则之指向的是数组尾部之后无效的数据.
	printf("%d\n",*eiter);//输出5
```
### 通过\[]与at
```cpp
vector<int> vi2{1,2,3,4,5};// 包含1,2,3,4,5 这几个数字
for(int i=0;i<10;++i){
	printf("%d\n",vi2[i]);
}
//这个代码会输出超出数组内容的数据;
for(int i=0;i<10;++i){
	printf("%d\n",vi2.at(i));
}
//这个代码无法输出超出数组的内容并会报错;
//terminating due to uncaught exception of type std::out_of_range: vector
```

## 插入
```cpp
   //vector 插入演示
   vector<string> v;
   v.push_back("hello");
   //左值插入
   string s = "world";
   v.push_back(std::move(s));
   //s 为空 ,s移动到v 中
   printf("s data:%s\n", s.c_str());

   v.insert(v.begin(), v[0]);
   //拷贝插入
    v.insert(v.begin(), std::move(v[1]));
    //移动插入
    std::for_each(v.begin(), v.end(), [](const string& s){
        printf("%s", s.c_str());
    });
    putchar('\n');
```
## 删除

```cpp
    // 删除
    v.erase(v.begin());
    std::for_each(v.begin(), v.end(), [](const string& s){
        printf("%s", s.c_str());
    });
    putchar('\n');
    // clear删除全部
    v.clear();
    std::for_each(v.begin(), v.end(), [](const string& s){
        printf("%s", s.c_str());
    });
    putchar('\n');
    //erase_if
    v.push_back("hello");
    v.push_back("world");
    std::erase_if(v, [](const string& s){
        return s == "hello";
    });
    std::for_each(v.begin(), v.end(), [](const string& s){
        printf("%s", s.c_str());
    });
    putchar('\n');```
