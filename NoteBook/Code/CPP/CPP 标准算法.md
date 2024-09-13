## 查找 find find_if
```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

int test_find(){
    using namespace std;
    vector<int> arr = {1,2,4,6,10};
    auto p=std::find(arr.begin(),arr.end() , 5);
    std::cout << p-arr.begin() << std::endl;
    // 没能找到数据时,返回 end()
    return *p;
}
std::vector<int> test_find_if(std::vector<int> in){
    auto out= std::find_if(in.begin(),in.end(),[](int x){return x>5;});
    return std::vector<int>(out,in.end());
    //返回 所有大于5的元素
}
int main(){
    auto out= test_find_if(std::vector<int>{1,2,3,4,5,6,7,8,9});
    std::for_each(out.begin(),out.end(),[](int x){std::cout << x << std::endl;});
}
```

## 合计 accumulate
```cpp
//accumulate 算法
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
	std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
	int sum = std::accumulate(v.begin(), v.end(), 0);
    //从0开始累加,v的开头到v的结尾
	std::cout << sum << std::endl;

	return 0;
}
```
### 乘积计算
```cpp
//accumulate 算法
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
	std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
	int sum = std::accumulate(v.begin(), v.end(), 1,[](int x,int y){return x*y;});
    //从1开始相乘,v的开头到v的结尾
	std::cout << sum << std::endl;

	return 0;
}
```

## 查找 find find_if
```cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// std::find 数 在一个数组里

int test_find()
{
	std::vector<int> v{1,2,3,4,5,6,7,8,9};
	auto it = std::find(v.begin(), v.end(), 5);
	if(it != v.end())
	{
		std::cout << "find 5 at " << it-v.begin()<< std::endl;
	}
	return 0;
}
int test_find_if(){
	std::vector<int> v{1,2,3,4,5,6,7,8,9};
	auto it = std::find_if(v.begin(), v.end(), [](int x){return x%2==0;});
	if(it != v.end())
	{
		std::cout << "find mod 2 == 0  at " << it-v.begin()<< std::endl;
	}
	return 0;
}
int main(){
	test_find();
	test_find_if();
}
```
## 查找 search
```cpp
//search str in str
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

int main()
{
    string str = "hello world";
	string str2 = "world";
	auto it= std::search(str.begin(), str.end(),std::boyer_moore_searcher(str2.begin(), str2.end()));
    std::puts(it.base());
}
```
## 比较 equal mismatch lexicographic_compare lexicographical_compare_three_way

## 计数 all_of any_of none_of count_if count

## 生成 generate generate_n

## 转换 transform

## 拷贝 copy copy_n copy_if copy_backward

## 移动 move move_backward

## 替换 replace replace_if replace_copy replace_copy_if

## 擦除 erase erase_if

## 删除 remove remove_if remove_copy remove_copy_if

## 唯一化 unique unique_copy

## 乱序 shuffle

## 抽样 sample

## 反转 reverse reverse_copy