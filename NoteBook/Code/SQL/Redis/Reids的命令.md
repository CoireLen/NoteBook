## 全局命令
```sql
# 查看所有键
keys *

#键总数
dbsize

#检查键是否存在 存在1 不存在0
exists

#删除键
del 键
del 键1 键2 ...

#键过期
expire 键 时间（秒）
ttl 键  #查看剩余时间 0或大于0 是剩余时间 -1未设置过期时间 -2键不存在

#键的数据结构类型
type 键 #不存在返回none
```

### 数据操作
```sql
# 设置值 新建值 修改值
set 键 值
setnx 键 值 #若不存在则成功 否则返回0
setex 键 值 #若键存在则成功 否则返回0

#获取值
get 键 #若不成功返回（nil）

#批量操作
mset 键1 值1 键2 值2 ...
mget 键1 键2 ...

# 计数
incr 键             #自增 值不是整数（error） 是整数 返回 值+1  不存在则新建并从0开始计算
decr 键             #自减
incrby 键 值        #自增 指定的数
decrby 键 值        #自减 指定的数
incrbufloat 键 值   #自增指定浮点数

# 字符串操作
append 键 值         #在字符串后追加数据
strlen 键           #获取字符串长度
setrange 键 位置 值  #将指定位置的char改成 值
getrange 键 开始 结束 #获取从开始到结束的字符串切片

#设置一个新值并获取旧值
getset 键 值


```