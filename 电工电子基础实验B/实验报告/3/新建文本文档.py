# import packages
import matplotlib.pyplot as plt
import numpy as np
import sys
# 常用字体: ’Dejavu Sans‘,’Times New Roman‘,'Arial'
# 设置图片尺寸  set size of fgure units cm
plt.rcParams['figure.figsize'] = (5,2.5)
plt.xlabel('Position')
plt.ylabel('Temperatrue')
plt.rcParams.update({'font.size': 9})
# 采用紧凑布局
plt.tight_layout()
# 生成数据 
a = np.linspace(0,10,100)
b = 0.8*a
c = 1.2*a
u = np.sin(a)
v = np.cos(b)
w = u+v
# line color
# set 是经典的RGB色，简直辣眼睛
# set1: red,green,blue
# set2: frebrick,forestgreen,darkgreen
plt.plot(a,u,color='firebrick',marker='^',markevery=10,mew=0.25)
plt.plot(b,v,color='forestgreen',marker='o',markevery=10,mew=0.25)
plt.plot(c,w,color='darkblue',marker='s',markevery=10,mew=0.25)
# create legend without frame
plt.title('Sample Figure')
# 绘制图例，不要框框
plt.legend(['L1','L2','L3'],frameon=False)
plt.xlim(0,8)
plt.ylim(-3,3)
# 亲测SVG能插入最word2016
plt.savefig('plt.svg')
# 可用格式有 png pdf ...
plt.savefig('plt.pdf',dpi=300)
plt.show()