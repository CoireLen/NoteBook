```cmake
find_package(Boost REQUIRED COMPONENTS locale)
target_link_libraries(main Boost::locale)
```

```cpp
#include <boost/locale.hpp>
int main(int, char**) {
	char* u8str=u8"(123abc你是不是大师?贾大师_ !)    ";
	auto gbkstr=boost::locale::conv::from_utf<char>(u8str,"GBK");
	printf("boost GBK %s\n",gbkstr.c_str());
}
```