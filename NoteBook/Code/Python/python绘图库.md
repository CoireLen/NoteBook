Python 有许多用于科学和数学绘图的库，可以帮助你创建各种类型的图表和可视化。这些库广泛应用于数据分析、科学计算和机器学习。以下是一些常用的库：

### 1. **Matplotlib**
   Matplotlib 是最常用的 Python 绘图库之一，支持创建各种二维图表，如折线图、散点图、柱状图、直方图等。

   **安装**：
   ```bash
   pip install matplotlib
   ```

   **示例**：
   ```python
   import matplotlib.pyplot as plt
   import numpy as np

   x = np.linspace(0, 10, 100)
   y = np.sin(x)

   plt.plot(x, y)
   plt.xlabel('X-axis')
   plt.ylabel('Y-axis')
   plt.title('Sine Wave')
   plt.show()
   ```

### 2. **Seaborn**
   Seaborn 是基于 Matplotlib 的高级绘图库，专注于统计数据的可视化，支持热力图、回归图、分类图等。

   **安装**：
   ```bash
   pip install seaborn
   ```

   **示例**：
   ```python
   import seaborn as sns
   import matplotlib.pyplot as plt

   # 加载示例数据集
   tips = sns.load_dataset('tips')

   # 创建箱线图
   sns.boxplot(x='day', y='total_bill', data=tips)
   plt.show()
   ```

### 3. **Plotly**
   Plotly 支持交互式图表的绘制，可以用于网页和 Jupyter Notebook 中，适合创建复杂的交互式图表，如3D图、地图和热力图等。

   **安装**：
   ```bash
   pip install plotly
   ```

   **示例**：
   ```python
   import plotly.express as px

   df = px.data.iris()
   fig = px.scatter(df, x='sepal_width', y='sepal_length', color='species')
   fig.show()
   ```

### 4. **Bokeh**
   Bokeh 也是用于创建交互式图表的库，能够生成 HTML 文档或嵌入到网页中，支持高性能的交互式数据可视化。

   **安装**：
   ```bash
   pip install bokeh
   ```

   **示例**：
   ```python
   from bokeh.plotting import figure, show

   p = figure(title="Simple Line Example", x_axis_label='X', y_axis_label='Y')
   p.line([1, 2, 3, 4, 5], [6, 7, 2, 4, 5], legend_label="Temp.", line_width=2)

   show(p)
   ```

### 5. **NumPy + Matplotlib**
   虽然 NumPy 是一个用于科学计算的库，但结合 Matplotlib 可以进行高效的数学绘图，如生成波形、概率分布等。

   **安装 NumPy**：
   ```bash
   pip install numpy
   ```

   **示例**：
   ```python
   import numpy as np
   import matplotlib.pyplot as plt

   x = np.arange(0, 10, 0.1)
   y = np.cos(x)

   plt.plot(x, y)
   plt.show()
   ```

### 6. **SymPy**
   SymPy 是一个符号计算库，可以用于符号数学计算，并能进行简单的数学表达式可视化。

   **安装**：
   ```bash
   pip install sympy
   ```

   **示例**：
   ```python
   from sympy import symbols, sin
   from sympy.plotting import plot

   x = symbols('x')
   plot(sin(x), (x, -5, 5))
   ```

### 7. **Pygal**
   Pygal 适合生成 SVG 矢量图，适用于需要高质量图表的场景，可以生成折线图、条形图、雷达图等。

   **安装**：
   ```bash
   pip install pygal
   ```

   **示例**：
   ```python
   import pygal

   line_chart = pygal.Line()
   line_chart.title = 'Browser usage evolution (in %)'
   line_chart.x_labels = map(str, range(2002, 2013))
   line_chart.add('Firefox', [None, None, 0, 16.6, 25, 31, 36, 45, 46, 38.3, 31.7])
   line_chart.add('Chrome',  [None, None, None, None, None, None, None, None, None, 1.6, 3.9])
   line_chart.render_in_browser()
   ```

这些库覆盖了从简单到复杂、从静态到交互式的各种绘图需求。你可以根据项目的具体需求选择合适的工具。