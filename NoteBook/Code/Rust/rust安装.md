# 使用zypper安装
```sh
sudo zypper in cargo rustup
```
# 使用官方链接安装
## 打开https://rustup.rs/

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
    ###RUST源
    export RUSTUP_DIST_SERVER=https://mirrors.tuna.tsinghua.edu.cn/rustup
```
要立即生效只需要source一下.bashrc文件,之后无需再source 
```sh
source .bashrc
```

使用代理
```sh
    export HTTP_PROXY=127.0.0.1:8889
    export HTTPS_PROXY=127.0.0.1:8889
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

# 设置使用tuna Crates源
[[cargo源]]
打开 ~/.cargo/config 添加以下内容

```sh
[source.crates-io]
replace-with = 'tuna'

[source.tuna]
registry = "https://mirrors.tuna.tsinghua.edu.cn/git/crates.io-index.git"
```
