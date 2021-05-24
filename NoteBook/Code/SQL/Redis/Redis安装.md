# 安装

省略

# 客户端

hiredis

# 服务
## 启动后台模式
将\etc\redis\default.conf.example
复制一份到./redis.conf
修改
```sh
#daemonize no
daemonize yes
```
记住 pidfile /run/redis/default.pid 的路径
## service
```sh
[Unit]
Description=Redis Server Manager
After=network.target

[Service]
Type=forking
PIDFile=/var/run/default.pid
#这儿是pidfile 上面写着记住的地方
ExecStart=/usr/sbin/redis-server /etc/redis/redis.conf
#启动的程序 用whereis 查询      后面是配置文件
ExecReload=/bin/kill -USR2 $MAINPID
ExecStop=/bin/kill -SIGINT $MAINPID
PrivateTmp=true

[Install]
WantedBy=multi-user.target
Also=NetworkManager-wait-online.service
```