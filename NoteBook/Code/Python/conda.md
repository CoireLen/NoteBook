## 创建环境

Conda 允许您创建单独的环境，每个环境都包含自己的文件、包和包依赖项。每个环境的内容不会相互影响。

创建新环境最基本的方法是使用以下命令

> conda create -n <env-name>

要在创建环境时添加包，请在环境名称后指定它们

```sh
	conda create -n myenvironment python numpy pandas
```

## 更换 conda 源

修改 `${HOME}/.condarc` 文件
```
channels:
  - defaults
show_channel_urls: true
default_channels:
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/r
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/msys2
custom_channels:
  conda-forge: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  pytorch: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  ```

## 支持Jupyter C++
```sh
conda install xeus-cling -c conda-forge
```
