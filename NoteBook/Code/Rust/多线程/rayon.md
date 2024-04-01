#并行 #计算

```rust
fn main(){
	let v=vec![1,2,3,4,5,6,7,8,9];
	let rv=rayon_def(&v);
	println!("{:?}",rv);
}
fn rayon_def(a:&Vec<i32>)->Vec<i32>{
	a.par_iter().map(|i|{i*i}).collect()
}
```