cargo.toml
```
sqlite = "0.30.5"
```
main.rs
```rust
use std::string;
use sqlite;
fn main() {
    //打开数据库
    let connect=sqlite::open("data.db").unwrap();
    //建立数据表
    let _a=connect.execute("Create TABLE datas (name TEXT,data TEXT)");
    if let Ok(_) =_a  {
        println!("Create table succeed");
    }
    else{
        println!("Create table faild");
    }
    let query="SELECT count(*) FROM datas WHERE name='Bernie'";
    let mut countx=0;
    let _a=connect.iterate(query, |pairs|{
        for &(name, value) in pairs.iter() {
            let tmp=value.unwrap();
            println!("{} = {}", name,tmp);
            //将tmp从&str转换为i32
            countx=String::from(tmp).parse::<i32>().unwrap();
        }
        true
    }).unwrap();
    
    if countx==0{
        //添加数据到数据库
        let _a=connect.execute("INSERT INTO datas VALUES ('Bernie','Blank')");
        if let Ok(_) =_a  {
            println!("Insert succeed");
        }
        else{
            println!("Insert failed");
        }
    }
    else{
        //更新数据
        let _a=connect.execute("UPDATE datas SET data = 'Texas' WHERE name = 'Bernie';");
        if let Ok(_) =_a  {
            println!("Update succeed");
        }
        else{
            println!("Update failed");
        }
    }
    
    //查询数据
    let query="SELECT * FROM datas where name='Bernie'" ;
    connect
    .iterate(query, |pairs| {
        for &(name, value) in pairs.iter() {
            if name=="data"{
                println!("{} = {}", name, value.unwrap());
            }
        }
        true
    })
    .unwrap();
}   
```
