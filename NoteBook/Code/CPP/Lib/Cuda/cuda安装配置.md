#cuda #并行
### 安装CUDA
1. 去官网下载 CUDA 对应系统的 sh 文件
2. 运行安装，取消勾选驱动程序

### 配置 OPENCL 环境
将以下代码添加到/etc/profile
```
#
#cuda
#
    export PATH=/usr/local/cuda/bin/${PATH:+:${PATH}}
    export C_INCLUDE_PATH=/usr/local/cuda/include${C_INCLUDE_PATH:+:${C_INCLUDE_PATH}}
    export CPLUS_INCLUDE_PATH=/usr/local/cuda/include${CPLUS_INCLUDE_PATH:+:${CPLUS_INCLUDE_PATH}}
    export LD_LIBRARY_PATH=/usr/local/cuda/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
    export LIBRARY_PATH=/usr/local/cuda/lib64${LIBRARY_PATH:+:${LIBRARY_PATH}}
```
这下就可以使用gcc 来编译了

