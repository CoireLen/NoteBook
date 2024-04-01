#多线程 #数据通信



```rust
use random::Source;
use threadpool;
use std::thread;
use std::time;
use random;
use std::sync::mpsc;
fn main() {
	let pool=threadpool::ThreadPool::new(8);
	let (tx,rx)=mpsc::channel();
	for i in 1..10{
	let o=i;
	let tx1=tx.clone();
		pool.execute(move||{
		let mut rd=random::default(2000);
			let t=rd.read_u64()%2000;
				thread::sleep(time::Duration::from_nanos(t));
				thread::sleep(time::Duration::from_secs(1));
				tx1.send(t).unwrap();
				println!("Thread {}",o);
			});
		}
	for received in rx {//此操作会导致线程阻塞
		println!("Got: {}", received);
	}
}
```