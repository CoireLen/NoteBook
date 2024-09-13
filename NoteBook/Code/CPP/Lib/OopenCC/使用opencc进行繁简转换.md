```cpp
#include <boost/locale.hpp>
#include <opencc/opencc.h>

using namespace std;
int main()
{
    opencc_t s2ts=opencc_open("./opencc/s2t.json");
    if (s2ts==NULL){
        return -1;
    }
    system("chcp 65001");
    string szConvsert(const_cast<char []>(u8"今天天气真奇怩"));
    //在使用msvc时出现字符串包含换行 需要将代码重新保存为UTF-8 With BOM
    auto outstr=opencc_convert_utf8(s2ts,szConvsert.c_str(),szConvsert.size());
    cout<<outstr<<endl;
}
```
使用时因该将 vcpkg share\\opencc 文件夹拷贝到项目中
