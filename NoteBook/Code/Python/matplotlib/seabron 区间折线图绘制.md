```python
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
# 设置中文字体（在macOS上可用的字体）
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']  # 使用macOS系统的中文字体
plt.rcParams['axes.unicode_minus'] = False  # 解决负号显示问题
def show_cpu_info(data1):
    if 'Time' not in data1.columns:
        raise ValueError("没有 'Time' 序列")
    data1['Time'] = pd.to_datetime(data1['Time'], format='%H:%M:%S.%f')
    data1.set_index('Time', inplace=True)
    # 使用正则表达式匹配列名中包含 'Core X 频率' 的列
    # 假设列名格式为 "Core X 频率 [MHz]"
    core_columns = data1.filter(regex=r'Core \d+ 频率 \[MHz\]').columns
    # 核心使用率
    core_usage = data1.filter(regex=r'Core \d+ T\d 使用率 \[%\]').columns
    # 核心温度 Core 0 [℃]
    core_temp = data1.filter(regex=r'Core \d+ \[℃\]').columns
    # 提取匹配的列
    core_data = data1[core_columns]
    df = pd.DataFrame(core_data)
    # 计算每一行的均值、最大值和最小值
    df['mean'] = df.mean(axis=1)
    df['max'] = df.max(axis=1)
    df['min'] = df.min(axis=1)
    # usage_data 的每一行的平均值,最大值和最小值
    usage_data=data1[core_usage]
    df_usage=pd.DataFrame(usage_data)
    df_usage['mean']=df_usage.mean(axis=1)
    df_usage['max']=df_usage.max(axis=1)
    df_usage['min']=df_usage.min(axis=1)
    # temp_data 的每一行的平均值,最大值和最小值
    temp_data=data1[core_temp]
    df_temp=pd.DataFrame(temp_data)
    df_temp['mean']=df_temp.mean(axis=1)
    df_temp['max']=df_temp.max(axis=1)
    df_temp['min']=df_temp.min(axis=1)
    
    # 创建一个新的 DataFrame，用于绘图（x轴为时间或索引，y轴为频率）
    df_plot = pd.DataFrame({
        'index': df.index,
        'mean': df['mean'],
        'max': df['max'],
        'min': df['min']
    })

    # 绘制带有误差带的折线图
    fig,ax1=plt.subplots(figsize=(50, 6))
    sns.lineplot(x=df.index, y=df['mean'], data=df_plot, label='CPU频率',color='blue')
    plt.fill_between(df_plot['index'], df_plot['min'], df_plot['max'],color='blue', alpha=0.3, label='最大频率和最小频率')
    ax1.set_xlabel('时间')
    ax1.set_ylabel('CPU 频率 [MHz]',color='blue')
    # 绘制使用率折线图
    ax2=ax1.twinx()
    ax2.set_ylabel('CPU 使用率&温度', color='orange')
    ax2.tick_params(axis='y', labelcolor='orange')  
    sns.lineplot(x=df.index, y=df_usage['mean'], data=df_usage, label='CPU使用率',color='orange',ax=ax2)
    plt.fill_between(df.index, df_usage['min'], df_usage['max'],color='orange', alpha=0.3, label='最大使用率和最小使用率')
    # 使用红色绘制温度折线图
    sns.lineplot(x=df.index, y=df_temp['mean'], data=df_temp, label='CPU温度',color='red',ax=ax2)
    plt.fill_between(df.index, df_temp['min'], df_temp['max'],color='red', alpha=0.3, label='最大温度和最小温度',)
    plt.title('CPU性能释放图')
    
    plt.legend()
    plt.show()

data1 = pd.read_csv('/Users/coirelen/code/python/hwinfo数据可视化/123.csv', sep=',')
show_cpu_info(data1)
```
显示图形
![[img/cpu性能释放图.png]]

## 添加 第三个y轴支持
```python
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
# 设置中文字体（在macOS上可用的字体）
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']  # 使用macOS系统的中文字体
plt.rcParams['axes.unicode_minus'] = False  # 解决负号显示问题
def show_cpu_info(data1):
    if 'Time' not in data1.columns:
        raise ValueError("没有 'Time' 序列")
    data1['Time'] = pd.to_datetime(data1['Time'], format='%H:%M:%S.%f')
    data1.set_index('Time', inplace=True)
    # 使用正则表达式匹配列名中包含 'Core X 频率' 的列
    # 假设列名格式为 "Core X 频率 [MHz]"
    core_columns = data1.filter(regex=r'Core \d+ 频率 \[MHz\]').columns
    # 核心使用率
    core_usage = data1.filter(regex=r'Core \d+ T\d 使用率 \[%\]').columns
    # 核心温度 Core 0 [℃]
    core_temp = data1.filter(regex=r'Core \d+ \[℃\]').columns
    # 提取匹配的列
    core_data = data1[core_columns]
    df = pd.DataFrame(core_data)
    # 计算每一行的均值、最大值和最小值
    df['mean'] = df.mean(axis=1)
    df['max'] = df.max(axis=1)
    df['min'] = df.min(axis=1)
    # usage_data 的每一行的平均值,最大值和最小值
    usage_data=data1[core_usage]
    df_usage=pd.DataFrame(usage_data)
    df_usage['mean']=df_usage.mean(axis=1)
    df_usage['max']=df_usage.max(axis=1)
    df_usage['min']=df_usage.min(axis=1)
    # temp_data 的每一行的平均值,最大值和最小值
    temp_data=data1[core_temp]
    df_temp=pd.DataFrame(temp_data)
    df_temp['mean']=df_temp.mean(axis=1)
    df_temp['max']=df_temp.max(axis=1)
    df_temp['min']=df_temp.min(axis=1)
    
    # 创建一个新的 DataFrame，用于绘图（x轴为时间或索引，y轴为频率）
    df_plot = pd.DataFrame({
        'index': df.index,
        'mean': df['mean'],
        'max': df['max'],
        'min': df['min']
    })

    # 绘制带有误差带的折线图
    fig,ax1=plt.subplots(figsize=(50, 6))
    sns.lineplot(x=df.index, y=df['mean'], data=df_plot, label='CPU频率',color='blue')
    plt.fill_between(df_plot['index'], df_plot['min'], df_plot['max'],color='blue', alpha=0.3, label='最大频率和最小频率')
    ax1.set_xlabel('时间')
    ax1.set_ylabel('CPU 频率 [MHz]',color='blue')
    # 绘制使用率折线图
    ax2=ax1.twinx()
    ax2.set_ylabel('CPU 使用率&温度', color='orange')
    ax2.tick_params(axis='y', labelcolor='orange')  
    sns.lineplot(x=df.index, y=df_usage['mean'], data=df_usage, label='CPU使用率',color='orange',ax=ax2)
    plt.fill_between(df.index, df_usage['min'], df_usage['max'],color='orange', alpha=0.3, label='最大使用率和最小使用率')
    # 使用红色绘制温度折线图
    fig.subplots_adjust(right=0.8)
    ax3 = ax1.twinx()
# 调整ax3位置，为了不与ax2重叠
    ax3.spines['right'].set_position(('outward', 60))
    ax3.set_ylabel("CPU 温度 [℃]",color='red')
    ax3.tick_params(axis='y', labelcolor='red')
    sns.lineplot(x=df.index, y=df_temp['mean'], data=df_temp, label='CPU温度',color='red',ax=ax3)
    plt.fill_between(df.index, df_temp['min'], df_temp['max'],color='red', alpha=0.3, label='最大温度和最小温度',)
    plt.title('CPU性能释放图')
    
    plt.legend()
    plt.show()

data1 = pd.read_csv('/Users/coirelen/code/python/hwinfo数据可视化/123.csv', sep=',')
show_cpu_info(data1)
```
修改后的图形
![[img/cpu性能释放图-y3.png]]