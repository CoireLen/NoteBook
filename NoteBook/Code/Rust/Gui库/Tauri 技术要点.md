#GUI #WEB 
### 跳过 src-tauri 中的文件变更自动重新编译
在该目录下建立.taurigonre
```
*
filename.txt
```
使用\*来表示所有文件 单独文件则使用文件名来表示

### 共享数据

```rust
struct AppState{
    connect:Mutex<sqlite::Connection>
}
impl AppState {
    fn new()->AppState{
        AppState { connect:Mutex::new(sqlite::open("data.db").unwrap()) }
    }
}
fn main() {
    let state=AppState::new();
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![])
        .manage(state)
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
```

### 异步运行
```rust
#[tauri::command]
async fn get_prints_data(state:State<'_,AppState>)->Result<(),()>{
	Ok()
}
```
注意 ，此时使用传参需要生命周期，其次 返回函数结果必须为Result结构包裹