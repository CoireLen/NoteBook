## bin 可执行程序
```toml
[[bin]]
name = "first-program"
path = "src/main.rs"
[[bin]]
name = "second-program"
path = "src/main02.rs"
```

```sh
cargo run --bin second-program
```
在Cargo.toml 文件中可以添加多个bin
使用 cargo run --bin name 来进行区分生成运行不同的可执行程序

## lib 库
和可执行程序相同 只不过建立时使用以下命令
```sh
cargo new --lib mylib
```
## example 示例代码


## bench 性能测试

### dependencies 依赖项目

#### dev-dependencies  示例 测试 性能测试的依赖项目

#### build-dependencies 构建脚本的依赖项目

## 编译命令
### build
#### dev
```sh
cargo build
```
使用build 编译项目 默认使用dev 优化编译时间
#### release
```sh
cargo build -r
cargo build --release
```
对runtime速度进行优化
#### test
```sh
cargo test
```
运行测试
#### bench
```sh
cargo bench
```
运行基准测试
## 编译脚本 交叉编译
### 使用cpp

## RustDoc 生成项目文档