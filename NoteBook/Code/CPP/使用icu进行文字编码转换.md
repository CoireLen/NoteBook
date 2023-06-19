```cpp
#include <iostream>
#include <unicode/ucnv.h>
#include <string>
#include <unicode/ustdio.h>
int main(int, char**) {
    UErrorCode ecode;
    system("chcp 65001");
    auto conv_gbk=ucnv_open("GBK",&ecode);
    if (U_FAILURE(ecode)) {
    std::cout <<u8"gbk error"<<std::endl;
    }
    auto conv_utf8=ucnv_open("UTF8",&ecode);
    if (U_FAILURE(ecode)) {
    std::cout <<u8"utf8 error"<<std::endl;
    }
    char* u8str=u8"(123abc你是不是大师?贾大师_ !)    ";
    //在使用msvc时出现字符串包含换行 需要将代码重新保存为UTF-8 With BOM
    UChar str[100];
    char out[100];
    ucnv_toUChars(conv_utf8,str,100,u8str,50,&ecode);
    ucnv_fromUChars(conv_gbk,out,100,str,50,&ecode);
    if (U_FAILURE(ecode)) {
    std::cout <<"conv error"<<std::endl;
    }
    ucnv_clone(conv_gbk,&ecode);
    if (U_FAILURE(ecode)) {
    std::cout <<u8"gbk close error"<<std::endl;
    }
    ucnv_clone(conv_utf8,&ecode);
    if (U_FAILURE(ecode)) {
    std::cout <<u8"utf8 close error"<<std::endl;
    }
    std::cout<<u8str<<std::endl;
    std::cout<<out<<std::endl;
    u_printf("%S\n",str);
    printf("%S\n",str);
}
```
