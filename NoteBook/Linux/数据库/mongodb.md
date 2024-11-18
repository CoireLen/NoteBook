### 下载工具包
https://fastdl.mongodb.org/tools/db/mongodb-database-tools-suse15-x86_64-100.10.0.rpm

### 备份数据库
mongodump -h 192.168.5.200:27017 -o ./mongodbbackup/
### 还原数据库
mongorestore -h 10.0.0.11:27017 --dir ./mongodbbackup/

