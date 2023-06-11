在Windows系统下使用gtk4

1.安装package-confg工具，并将bin目录加入PATH

2.使用vcpkg install gtk:x64-windows

3.rustup default stable-msvc

4.设置环境变量

> SET PKG_CONFIG_PATH %VCPKGDIR%\installed\x64-windows\lib\pkgconfig
> 
> SET GTK_LIB_DIR %VCPKGDIR%\installed\x64-windows\lib
> 
> SET PATH=%VCPKGDIR%\installed\x64-windows\bin;%PATH%