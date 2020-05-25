# 打开https://rustup.rs/
获取最新的安装命令
>curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# 设置 PATH

1.  系统路径
    /etc/profile
2. 用户路径
    $HOME/.bashrc
## 在文件末尾添加
```sh
    #
    #Rust
    # 
    PATH = $PATH:$HOME/.cargo/bin
    export PATH
    ###RUST源
    export RUSTUP_DIST_SERVER=https://mirrors.tuna.tsinghua.edu.cn/rustup

使用代理
```sh
    export HTTP_PROXY=127.0.0.1:8888
    export HTTPS_PROXY=127.0.0.1:8888
```
# 安装 nightly
>    rustup update nightly

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