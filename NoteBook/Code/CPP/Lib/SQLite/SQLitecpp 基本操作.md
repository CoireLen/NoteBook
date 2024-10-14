#数据库
```cmake
  find_package(SQLiteCpp CONFIG REQUIRED)
    target_link_libraries(main PRIVATE SQLiteCpp)

```
```cpp
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
int main(int, char**) {
    SQLite::Database db("test.db",SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    try
    {
        db.exec("Create TABLE datas (name TEXT,data TEXT)");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    auto query="SELECT count(*) FROM datas WHERE name='Bernie'";
    auto a=db.execAndGet(query);
    std::cout <<a<<std::endl;
    if (a.getInt()==0){
        //添加数据到数据库
        try
        {
            db.exec("INSERT INTO datas VALUES ('Bernie','Blank')");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else{
        //修改数据
        try
        {
            db.exec("UPDATE datas SET data = 'Texas' WHERE name = 'Bernie';");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    //查询并输出
    SQLite::Statement q(db,"SELECT * FROM datas where name='Bernie'");
    while(q.executeStep()){

        const char * name=q.getColumn(0);
        const char * val=q.getColumn(1);
        std::cout<<name<<":"<<val<<std::endl;
    }
}
```