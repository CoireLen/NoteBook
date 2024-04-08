# 单元测试
#测试 
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


# 重载函数 和 继承
#重载 #继承
```rust
    fn main() {
        let x=Node::new(1);
        let y=Node::new((1,2));
        print(&x);
        print(&y);
    }
    #[derive(Debug)]
    struct Node{
        x:i32,
        y:i32,
    }
    trait new<T> {
        fn new(value:T) ->Self;
    }
    impl new<i32> for Node {
        fn new(value:i32) ->Self {
            Node { x: value, y: value }
        }
    }
    impl new<(i32,i32)> for Node {
        fn new(x:(i32,i32))->Self{
            Node{x:x.0,y:x.1}
        }
    }
    trait X_Y {
        fn print(&self);
    }
    impl X_Y for Node {
        fn print(&self){
            println!("({},{})",self.x,self.y);
        }
    }   
    fn print<T:X_Y>(x:&T){
        x.print();
    }
    //或
    fn print(x:&dyn X_Y){
        x.print();
    }
```
## 重载运算符
| 运算符    | Trait        | 方法           | 说明      |
| ------ | ------------ | ------------ | ------- |
| `+`    | `Add`        | `add`        | 加法运算符   |
| `-`    | `Sub`        | `sub`        | 减法运算符   |
| `*`    | `Mul`        | `mul`        | 乘法运算符   |
| `/`    | `Div`        | `div`        | 除法运算符   |
| `%`    | `Rem`        | `rem`        | 取模运算符   |
| `+=`   | `AddAssign`  | `add_assign` | 加法赋值运算符 |
| `-=`   | `SubAssign`  | `sub_assign` | 减法赋值运算符 |
| `*=`   | `MulAssign`  | `mul_assign` | 乘法赋值运算符 |
| `/=`   | `DivAssign`  | `div_assign` | 除法赋值运算符 |
| `%=`   | `RemAssign`  | `rem_assign` | 取模赋值运算符 |
| `==`   | `PartialEq`  | `eq`         | 等于运算符   |
| `!=`   | `PartialEq`  | `ne`         | 不等于运算符  |
| `<`    | `PartialOrd` | `lt`         | 小于运算符   |
| `<=`   | `PartialOrd` | `le`         | 小于等于运算符 |
| `>`    | `PartialOrd` | `gt`         | 大于运算符   |
| `>=`   | `PartialOrd` | `ge`         | 大于等于运算符 |
| `!`    | `Not`        | `not`        | 逻辑非运算符  |
| `&`    | `BitAnd`     | `bitand`     | 位与运算符   |
| `\|`   | `BitOr`      | `bitor`      | 位或运算符   |
| `^`    | `BitXor`     | `bitxor`     | 位异或运算符  |
| `<<`   | `Shl`        | `shl`        | 位左移运算符  |
| `>>`   | `Shr`        | `shr`        | 位右移运算符  |
| `&&`   | `BitAnd`     | `bitand`     | 逻辑与运算符  |
| `\|\|` | `BitOr`      | `bitor`      | 逻辑或运算符  |
| `^`    | `BitXor`     | `bitxor`     | 逻辑异或运算符 |

| 功能函数   | Trait           | 说明                              |
|------------|-----------------|-----------------------------------|
| `Drop`     | `Drop`          | 用于在值离开作用域时执行清理操作  |
| `Deref`    | `Deref`         | 重载解引用运算符（`*`）           |
| `DerefMut` | `DerefMut`      | 重载可变解引用运算符（`*mut`）    |
| `Index`    | `Index`         | 重载索引运算符（`[]`）             |
| `IndexMut` | `IndexMut`      | 重载可变索引运算符（`[]`）         |
| `Fn`       | `Fn`            | 允许通过不可变引用调用实例        |
| `FnMut`    | `FnMut`         | 允许通过可变引用调用实例          |
| `FnOnce`   | `FnOnce`        | 允许通过所有权调用实例            |
| `Iterator` | `Iterator`      | 用于实现迭代器                    |
| `Clone`    | `Clone`         | 克隆类型                          |

### 例:add
```rust
use std::ops::Add;

#[derive(Debug)]
struct Complex {
    real: f64,
    imag: f64,
}

impl Add for Complex {
    type Output = Complex;

    fn add(self, other: Complex) -> Complex {
        Complex {
            real: self.real + other.real,
            imag: self.imag + other.imag,
        }
    }
}

fn main() {
    let num1 = Complex { real: 1.0, imag: 2.0 };
    let num2 = Complex { real: 3.0, imag: 4.0 };
    
    let sum = num1 + num2;
    
    println!("{:?}", sum); // Output: Complex { real: 4.0, imag: 6.0 }
}

```
