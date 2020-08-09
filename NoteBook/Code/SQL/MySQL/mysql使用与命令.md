# MySQL 使用

### 操作关键词
#### DDL数据定义
```sql
create
drop
alter
```
#### DML数据操作
```sql
insert
delete
update
select
```
#### DCL数据控制
```sql
grant
revoke
```
#### 使用命令显示已有数据库
```sql
show databases;
```
```
+--------------------+
| Database           |
+--------------------+
| information_schema |
| test               |
+--------------------+
2 rows in set (0.001 sec)
```

#### 使用命令显示数据库中的表
```sql
show tables;
```
#### 删除
```sql
drop database 数据库名字;
drop table 表名;
```
#### 显示内容
```sql
desc 表名;
```
#### 创建
```sql
# 新建一个表
create table '表名' ( [数据结构] )
# 新建一个库
create database 库名
```
#### 修改一个表
```sql
# 修改已有类
alter table 表名 modify 类型名 类型;
# 添加一个类
alter table 表名 add column 类型名 类型;
# 删除一个类
alter table 表名 drop 类型名;
# 修改一个类
alter table 表名 change 类型名 类型名 类型;
# 以上简称为命令，下面是修改位置
# 将修改类的放到第一个
命令 first;
# 将修改的类放到某个类的后面
命令 after 类型名;
# 修改一个表的名称
alter table 表名 rename 新表名;
```
#### 插入记录
``` sql
# 插入数据
insert into 表名 (类名1，类名2) values (值1，值2);
# 不指定顺序则与类排列顺序一致
insert into 表名 values (值1，值2);
# 插入多条数据
insert into 表名 values (值1，值2),(值1，值2),(值1，值2);
```
#### 修改值
```sql
update 表名 set 表名.值 = 另外的值 ;
update 表名 set 表名.值 = 另外的值 where 表名.值= 对比的值;
```
#### 删除值
```sql
delete from 表名 where 公式;
```
#### 查询
```sql
# 查询全部
select * from 表名;
# 查询某个类的全部资料
select 类名 from 表名;
# 去掉重复的
select distinct 类名 from 表名;
# 排序
select * from 表名 order by 类名;       # 默认升序
select * from 表名 order by 类名 asc;   # 升序 
select * from 表名 order by 类名 desc;  # 降序
# 范围
limit 开始的下标 , 数量;
limit 数量 ;            
# 函数
select sum(类名) from 表名;     #求和
select count(类名) from 表名;   #计数
# 函数分组 
select 函数(类名) from 表名 group by 类名;
# 连接
select 类1, 类2 from 表1 left join 表2 on 表1.类n = 表2.类n;
# 左连接 会显示 左表有但是右表没有的 数据
select 类1, 类2 from 表1 right join 表2 on 表1.类n = 表2.类n;
# 右连接 参考上面 把左右互换

# 子查询
# // 关键词 in 、not in 、=、 != 、 exists 、 not exists 等
select * from 表1 where 类1 in (select 类2 from 表2);

# 交集
# union all 包含重复
# union  不包含重复
```
## 权限
```sql
# 给予 并 建立用户
grant select,insert on 表1.* to '用户'@'localhost' identified by '密码';
# 收回
revoke insert on 表1.* from '用户'@'localhost';
