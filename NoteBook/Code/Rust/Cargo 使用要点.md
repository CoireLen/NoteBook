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

## test 测试文件
### 单元测试
```rust
#[test]
fn testfn(){
	//assert
}
```
使用这个测试宏时将会在源码编译添加到可执行文件。
使用测试模块与cfg宏来避免这个问题
```rust
#[cfg(test)]
mod tests{
	use std::something;
	#[test]
	fn testfn(){
		//assert
	}
}
```
### 集成测试
tests目录 下每一个.rs文件都是为一个单独的可执行程序
并且 集成测试 只适用于 lib

使用cargo test 来运行测试

### 指定运行部分测试
```sh
cargo test testfn-name
```
如果测试函数名称不是全称 如 有test1,test2 两个测试函数 使用命令 cargo test test 时将会匹配函数名称中含有test的测试函数来运行测试。

### 忽略测试ignore
```rust
#[test]
#[ignore]
fn testfn(){

}
```
这样定义后使用测试命令将会跳过该测试函数
```sh
cargo test --ignored
```
使用该命令 来单独测试 标记为跳过的函数
### 按顺序测试与并行测试
```sh
cargo test --test-thread=1
```
默认测试行为 就是 在单独的线程中并行测试，使用该命令来进行顺序测试
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