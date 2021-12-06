# 忘记密码

### 停用服务

```bash
systemctl  stop mysql
```

### 修改配置文件

> /etc/my.cnf

```bash
[mysqld]
skip-grant-tables
```

### 启动mysql

```shell
systemctl start mysqld 
```

```bash
mysql
```

### 使用命令修改密码

```sql
ALTER USER 'root'@'localhost' IDENTIFIED BY '123456';
```
