# 使用zypper安装
```sh
sudo zypper in cargo rustup
```
# 使用官方链接安装
## 打开https://rustup.rs/

## 设置代理
参考网页:https://rsproxy.cn/

设置环境变量,或添加到 ~/.zshrc or ~/.bashrc 配置文件

```sh
export RUSTUP_DIST_SERVER="https://rsproxy.cn"
export RUSTUP_UPDATE_ROOT="https://rsproxy.cn/rustup"
```

获取最新的安装命令

> curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

## 设置 PATH

1. 系统路径
   /etc/profile
2. 用户路径
   $HOME/.bashrc

### 在文件末尾添加

```sh
    #
    #Rust
    # 
    PATH = $PATH:$HOME/.cargo/bin
    export PATH
```
要立即生效只需要source一下.bashrc 文件,之后无需再source 
```sh
source .bashrc
```


# 安装 nightly

> rustup update nightly

# 安装 RLS

```sh
rustup component add rls --toolchain nightly
rustup component add rust-analysis --toolchain nightly
rustup component add rust-src --toolchain nightly
```

# 编译动态链接库程序

```rust
-C prefer-dynamic
```

# 设置使用 Crates源
[[cargo源]]
打开 ~/.cargo/config 添加以下内容
### 清华源

```sh
[source.crates-io]
replace-with = 'tuna'

[source.tuna]
registry = "https://mirrors.tuna.tsinghua.edu.cn/git/crates.io-index.git"
```
### 字节源

```sh
[source.crates-io]
replace-with = 'rsproxy-sparse'
[source.rsproxy]
registry = "https://rsproxy.cn/crates.io-index"
[source.rsproxy-sparse]
registry = "sparse+https://rsproxy.cn/index/"
[registries.rsproxy]
index = "https://rsproxy.cn/crates.io-index"
[net]
git-fetch-with-cli = true
```