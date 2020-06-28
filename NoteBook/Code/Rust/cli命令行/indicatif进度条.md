# 使用indicatif库
> 在Cargo.toml 添加
```
indicatif = "0.15.0"
```
示例
```rust
use indicatif::ProgressBar;
use std::{thread,time};
fn main() {
    let bar=ProgressBar::new(100);
    let t1=time::Duration::from_millis(10);
    for _ in 0..100{
        bar.inc(1);
        thread::sleep(t1);
    }
    bar.finish();
}
```
ProgressBar 是一个单独的进度条
导入 ProgressIterator 来更加简便的使用进度条
```rust
use indicatif::ProgressIterator;
use std::{thread,time};
fn main() {
    let t1=time::Duration::from_millis(10);
    for _ in (0..100).progress(){
        thread::sleep(t1);
    }
}
```
MultiProgress
//需要多线程知识 搁置