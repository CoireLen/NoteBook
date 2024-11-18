启动服务:
```sh
jupyter lab --no-browser --port 8888 --ip 0.0.0.0 --allow-root

#前台运行模式（命令行窗口不能关闭）
jupyter lab
#后台运行模式
nohup jupyter lab &
```

安装中文 语言

```sh
pip install jupyterlab-language-pack-zh-CN
```

安装C++
```sh
conda install xeus-cling -c conda-forge
```

