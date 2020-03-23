### 设置储存路径
> /usr/lib/systemd/system/docker.service

在里面的EXECStart的后面增加后如下:

> ExecStart=/usr/bin/dockerd - -graph /home/docker

重启

### 添加用户权限
> sudo usermod -aG docker USER_NAME

重新登陆
### Login 和Pull
> docker login
> username:<输入用户名>
> password:<输入密码>

登陆后方可使用Pull获取镜像
### Images
>docker images

获取现有镜像信息
### commit 
> docker commit -m "消息" -a "作者" id username/imgname:ver

### 映射文件夹
> docker run -it --mount type=bind,source=D:/Code, destination=/code/ gcc bash

### 启动 连接 一个镜像
> start  attach

### 加速镜像获取
使用阿里云镜像加速服务
>   sudo vim /etc/docker/daemon.json

将"registry-mirrors": ["https://......com"] （对应自己的加速地址）复制到文件中