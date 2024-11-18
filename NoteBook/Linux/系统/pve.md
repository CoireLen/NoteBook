中科大 https://mirrors.ustc.edu.cn/help/proxmox.html

编辑修改 `/etc/apt/sources.list`
```
deb https://mirrors.aliyun.com/debian buster-updates main contrib non-free
deb https://mirrors.aliyun.com/debian-security buster/updates main contrib non-free
```

编辑修改 `/etc/apt/sources.list.d/pve-enterprise.list` 企业版软件包仓库位置的配置文件

```
## deb https://enterprise.proxmox.com/debian/pve buster pve-enterprise
```

编辑修改 `/etc/apt/sources.list.d/ceph.list` Ceph软件包仓库

```
http://mirrors.ustc.edu.cn/proxmox/debian/ceph-nautilus buster main
```

最后执行 `apt update` 更新源

更换CT源
```
sed -i.bak 's|http://download.proxmox.com|https://mirrors.ustc.edu.cn/proxmox|g' /usr/share/perl5/PVE/APLInfo.pm
```
