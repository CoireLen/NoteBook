# 使用Samba服务
## 安装Samba 服务
使用命令
>zypper in yast2-samba-server 
## 配置共享文件夹
使用命令
>yast

进入控制面板
>选择 Network Services -> Samba Server

## 使文件夹可以共享访问
进入
>/etc/samba/

打开smb.conf,在需要开启公告访问的文件夹里添加以下一行
>public = Yes
