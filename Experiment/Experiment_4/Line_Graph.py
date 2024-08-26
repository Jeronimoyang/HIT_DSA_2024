import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import matplotlib.gridspec as gridspec

# 数据规模
data_size = [10000,20000,30000,40000,50000,60000,70000,80000,90000, 100000]

# 归并查找用时
merge_sort_time = [1,2,4,5,7,8,9,10,13,11]

# 快速排序用时
quick_sort_time = [1,2,3,5,5,6,7,8,10,11]

# 插入排序用时
insertion_sort_time = [55,215,489,872,1352,1968,2646,3447,4386,5421]

# 设置更加丰富的颜色
colors = ['tab:blue', 'tab:orange', 'tab:green']

plt.figure(facecolor="#EFE9E6") # 设置图形的背景色
plt.gca().set_facecolor("#EFE9E6")

plt.plot(data_size, merge_sort_time, label='Merge Sort', color="#153aab")
plt.plot(data_size, quick_sort_time, label='Quick Sort', color="#fdcf41")
plt.plot(data_size, insertion_sort_time, label='Insertion Sort', color= "#00A752")

plt.xlabel('Data Size')
plt.ylabel('Time (ms)')
plt.title('Algorithm Performance')
plt.legend(facecolor='#EFE9E6') # 设置图例的背景色
plt.grid(True)
plt.xscale('log')
plt.yscale('log')

# 设置 x 轴刻度
plt.xticks(data_size, rotation=45)

# 设置 y 轴刻度
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda x, _: '{:.0f}'.format(x)))

for i in range(len(data_size)):
    plt.text(data_size[i], merge_sort_time[i], f'({data_size[i]}, {merge_sort_time[i]})', fontsize=6, ha='right', va='top')
    plt.text(data_size[i], quick_sort_time[i], f'({data_size[i]}, {quick_sort_time[i]})', fontsize=6, ha='right', va='top')
    plt.text(data_size[i], insertion_sort_time[i], f'({data_size[i]}, {insertion_sort_time[i]})', fontsize=6, ha='right', va='bottom')

plt.show()
