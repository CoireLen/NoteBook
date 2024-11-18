## 修改镜像存储路径

```sh
/etc/containers/storage.conf
```
>graphroot = "/var/lib/containers/storage" 为容器存储路径

移动目录 需要关闭以下服务
- podman
- podman-restart
- podman-auto-update
- containerd
## 修改为国内镜像源

```sh
/etc/containers/registries.conf
```
修改此文件
```sh
# 取消从默认地址搜索的仓库域名
unqualified-search-registries = ["docker.io"]

# 自定义搜索器
[[registry]]
# 仓库前缀（镜像前缀）
prefix = "docker.io"
# 加速器地址，此处配置的 docker 中国区源
location = "dockerproxy.cn"
# 允许通过 http 协议获取镜像
insecure = true
```
