## python源设置
在 Python 中，你可以使用国内的源来加快安装依赖库的速度。以下是一些常用的中国镜像源，可以用来替代默认的 PyPI 源：

1. **阿里云**：
   ```
   https://mirrors.aliyun.com/pypi/simple/
   ```

2. **清华大学**：
   ```
   https://pypi.tuna.tsinghua.edu.cn/simple/
   ```

3. **中国科学技术大学**：
   ```
   https://pypi.mirrors.ustc.edu.cn/simple/
   ```

4. **豆瓣**：
   ```
   https://pypi.douban.com/simple/
   ```

### 临时使用镜像源安装：
例如，通过 pip 安装一个包时临时指定源：
```bash
pip install 包名 -i https://pypi.tuna.tsinghua.edu.cn/simple
```

### 永久配置镜像源：
如果你想永久地使用国内源，可以修改或创建 `pip` 配置文件。

#### 1. 在 macOS 或 Linux 上：
编辑或创建 `~/.pip/pip.conf` 文件，内容如下：
```ini
[global]
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
```

#### 2. 在 Windows 上：
编辑或创建 `%HOMEPATH%\pip\pip.ini` 文件，内容如下：
```ini
[global]
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
```

这样，你以后安装包时就会默认使用配置的国内源。