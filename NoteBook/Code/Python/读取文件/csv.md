## 读取CSV文件
### 打开CSV文件
使用open 打开文件
```python
file=open('文件路径','打开方式')
```
### 使用csv库
> import csv
> data=csv.reader(file)
### 处理数据
```python
for 行 in data
    for 元素 in 行
```
来处理数据