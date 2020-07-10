## 基础知识
### 编译一个单文件源码的程序
```cmake
#指定需要camke最小版本
cmake_minimum_required(VERSION 3.10)
#建立一个项目
project(Tutorial)
#将需要编译的文件添加到项目
add_executable(Tutorial tutorial.cxx)
```
### 编译一个多文件源码程序
```cmake
#指定需要camke最小版本
cmake_minimum_required(VERSION 3.10)
#建立一个项目
project(Tutorial)
#将需要编译的文件添加到项目
add_executable(Tutorial tutorial.cxx)
#添加一个下游目录Dir_name是文件夹名称
add_subdirectory(Dir_name)
#编译链接
target_link_libraries(Tutorial Dir_name)
```
> 在Dir_name路径下也需要一个CMakeLists.txt
```cmake
#指定需要camke最小版本
cmake_minimum_required(VERSION 3.10)
#建立一个项目
project(Dir_name)
#将需要编译的文件添加到项目
add_executable(Dir_name 你的文件.cc)
```
### 链接lib
```cmake
link_libraries(lib_name)
link_libraries("/path/libname.so")
```