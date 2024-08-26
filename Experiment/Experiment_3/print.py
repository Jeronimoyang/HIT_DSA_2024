import networkx as nx
import matplotlib.pyplot as plt
 
'''
有向图边信息,第一列为起点，第二列为终点，第三列为权重
0 1 2
0 2 5
1 0 3
1 2 1
1 3 3
2 3 3
2 4 4
2 5 6
3 4 1
3 5 7
3 6 4
4 5 1
4 7 4
4 8 6
5 1 10
5 2 7
5 9 2
6 5 2
6 9 1
7 8 1
7 9 2
8 5 7
9 8 1
10 8 3
10 2 7
'''
# 创建一个有向图
G = nx.DiGraph()
 
# 添加节点和边
G.add_weighted_edges_from([(0, 1, 2), (0, 2, 5), (1, 0, 3), (1, 2, 1), (1, 3, 3), (2, 3, 3), (2, 4, 4), (2, 5, 6), (3, 4, 1), (3, 5, 7), (3, 6, 4), (4, 5, 1), (4, 7, 4), (4, 8, 6), (5, 1, 10), (5, 2, 7), (5, 9, 2), (6, 5, 2), (6, 9, 1), (7, 8, 1), (7, 9, 2), (8, 5, 7), (9, 8, 1), (10, 8, 3), (10, 2, 7)])
 
# 使用 spring layout 算法进行布局
pos = nx.spring_layout(G)
 
# 绘制图
nx.draw(G, pos, with_labels=True)
plt.show()
