```cmake
find_package(Boost REQUIRED COMPONENTS locale)
target_link_libraries(main Boost::locale)
```
如果手动指定lib 和dll 会导致 内存memcpy失败 因为没有使用几种转换方式的任何一个
```cpp
#include <boost/locale.hpp>
int main(int, char**) {
	char* u8str=u8"(123abc你是不是大师?贾大师_ !)    ";
	//在使用msvc时出现字符串包含换行 需要将代码重新保存为UTF-8 With BOM
	auto gbkstr=boost::locale::conv::from_utf<char>(u8str,"GBK");
	printf("boost GBK %s\n",gbkstr.c_str());
}
```