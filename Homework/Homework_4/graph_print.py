"""
import networkx as nx
import matplotlib.pyplot as plt

# 创建有向图
G = nx.DiGraph()
# 添加节点
G.add_nodes_from(['A', 'B', 'C', 'D'])
# 添加边
G.add_edge('A', 'B')
G.add_edge('A', 'E')
G.add_edge('B', 'C')
G.add_edge('C', 'M')
G.add_edge('C', 'F')
G.add_edge('D', 'A')
G.add_edge('D', 'H')
G.add_edge('E', 'J')
G.add_edge('F', 'B')
G.add_edge('G', 'D')
G.add_edge('G', 'O')
G.add_edge('H', 'L')
G.add_edge('I', 'E')
G.add_edge('I', 'L')
G.add_edge('J', 'G')
G.add_edge('K', 'H')
G.add_edge('L', 'K')
G.add_edge('M', 'E')
G.add_edge('N', 'G')
G.add_edge('O', 'A')

# 绘制有向图
pos = nx.spring_layout(G) # 计算节点的位置
nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color='gray', font_size=10, node_size=800, arrowsize=20)
plt.show()
"""
import networkx as nx
import matplotlib.pyplot as plt
 
# 创建一个有向图
G = nx.DiGraph()
 
# 添加节点和边
G.add_edge('A', 'B')
G.add_edge('A', 'E')
G.add_edge('B', 'C')
G.add_edge('C', 'M')
G.add_edge('C', 'F')
G.add_edge('D', 'A')
G.add_edge('D', 'H')
G.add_edge('E', 'J')
G.add_edge('F', 'B')
G.add_edge('G', 'D')
G.add_edge('G', 'O')
G.add_edge('H', 'L')
G.add_edge('I', 'E')
G.add_edge('I', 'L')
G.add_edge('J', 'G')
G.add_edge('K', 'H')
G.add_edge('L', 'K')
G.add_edge('M', 'E')
G.add_edge('N', 'G')
G.add_edge('O', 'A')
 
# 使用 spring layout 算法进行布局
pos = nx.spring_layout(G)
 
# 绘制图
nx.draw(G, pos, with_labels=True)
plt.show()
