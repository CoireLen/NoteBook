
是否继续？
```rust
use dialoguer::Confirm;
fn main() {
    if Confirm::new().with_text("你想穿女装吗？").interact().unwrap()
    {
        println!("我来拍照~");
    }
    else
    {
        println!("今天你不穿也得穿!");
    }
}
```
通过vim来获取输入
```rust
use dialoguer::Editor;
fn main() {
    if let Some(rv) = Editor::new().edit("输入一些信息:").unwrap() {
        println!("你输入的信息:");
        println!("{}", rv);
    } else {
        println!("错误!");
    }
}
```
输入一点点
```rust
use dialoguer::Input;
fn main() {
    let name =Input::<String>::new().with_prompt("你的名字是?").interact().unwrap();
    println!("{},花姑娘的干活~",name);
}
```
输入密码
```rust
use dialoguer::Password;
fn main() {
    let pswd=Password::new().with_prompt("请输入密码").interact().unwrap();
    println!("{}",pswd);
}
```
挑选
```rust
use dialoguer::Select;
fn main() {
    let items=["苹果","李子","西瓜","荔枝"];
    let s=Select::new().items(&items).with_prompt("选择你喜欢的水果").interact().unwrap();
    println!("妳的选择是,{}。",items[s]);
}
```
