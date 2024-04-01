#多线程 #线程池 #并行
首先在$Cargo.toml$ 添加以下代码
```toml
threadpool = "1.8.1"
random = "0.14.0"
```

$main.rs$ 部分的内容
```rust
use random::Source;
use threadpool;
use std::thread;
use std::time;
use random;
fn main() {
		let pool=threadpool::ThreadPool::new(8);
		for i in 1..10{
		let o=i;
		pool.execute(move||{
			let mut rd=random::default(2000);
			thread::sleep(time::Duration::from_nanos(rd.read_u64()%2000));
			thread::sleep(time::Duration::from_secs(2));
			println!("Thread {}",o);
		});
	}
	pool.join();
}
```
输出：
```shell
    Finished dev [unoptimized + debuginfo] target(s) in 0.17s
     Running `target/debug/pthread-t`
Thread 7
Thread 2
Thread 3
Thread 1
Thread 4
Thread 8
Thread 5
Thread 6
Thread 9
```