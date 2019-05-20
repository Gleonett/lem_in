#!/Users/ajon-hol/.brew/bin/python3
# coding: utf-8

# In[1]:


import sys
import os
import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import pylab
from matplotlib.pyplot import pause
pylab.ion()


# In[2]:


class MyGraph:
    def __init__(self, inp):
        flag = 0
        c = 1
        self.ants = 0
        self.start = ''
        self.end = ''
        self.nodes = []
        self.links = []
        self.names = [[]]
        self.rooms = [[]]
        self.colors = []
        for line in inp:
            if line.rstrip().isdecimal():
                self.ants = int(line)
            list = line.split()
            if len(line) == 1:
                flag = 3
                continue
            if list[0] == "##start": flag = 1
            if list[0] == "##end": flag = 2
            if len(list) == 3 and flag != 3:
                self.nodes.append([list[0], list[1], list[2]])
                if flag == 1: self.start = list[0]
                if flag == 2: self.end = list[0]
                flag = 0
            elif flag != 3:
                list = line.rstrip().split("-")
                if len(list) == 2: self.links.append(list)
            if flag == 3:
                list = line.rstrip().split(" ")
                for i in range(len(list)):
                    list[i] = (list[i].split("-"))
                self.names.append([])
                self.rooms.append([])
                for j in range(len(list)):
                    for rofls in list[j]:
                        if rofls[0] == 'L': self.names[c].append(rofls)
                        else: self.rooms[c].append(rofls)
                c += 1
                
    def changenode(self, onode, nnode):
        for i in range(len(self.nodes)):
            if self.nodes[i][0] == onode:
                self.nodes[i][0] = nnode
        for i in range(len(self.links)):
            for j in range(len(self.links[i])):
                if self.links[i][j] == onode:
                    self.links[i][j] = nnode
        for i in range(len(self.rooms)):
            for j in range(len(self.rooms[i])):
                 if self.rooms[i][j] == onode:
                    self.rooms[i][j] = nnode
    
    def changestart(self, nstart):
        self.changenode(self.start, nstart)
        self.start = nstart
        
    def changeend(self, nend):
        self.changenode(self.end, nend)
        self.end = nend


# In[3]:

map = input("map: ")
with open (os.path.join('/Users', 'ajon-hol', 'py', map)) as inp:
    Gr = MyGraph(inp)

# In[ ]:


def get_fig(i):
    G = nx.Graph()
    for k in range(len(Gr.nodes)):
         G.add_node(Gr.nodes[k][0], pos=(int(Gr.nodes[k][1]), int(Gr.nodes[k][2])))
    G.add_edges_from(Gr.links)
    if i > 0:
        Gr.colors = [int(Gr.names[i][j][1:]) for j in range(len(Gr.names[i]))]
    pos=nx.get_node_attributes(G,'pos')
    nx.draw(G, pos, node_color='w', edgecolors='black', with_labels = True, font_size = 8, node_size = 400, node_shape='s')
    nx.draw_networkx_nodes(G, pos, nodelist=[Gr.start], node_color='y', node_size = 400, node_shape='s')
    nx.draw_networkx_nodes(G, pos, nodelist=Gr.rooms[i], node_color=Gr.colors, vmin=0, vmax=antbuf,
                           cmap = plt.cm.get_cmap('rainbow'), node_size = 400, node_shape='s')
    nx.draw_networkx_nodes(G, pos, nodelist=[Gr.end], node_color='g', node_size = 400, node_shape='s')

print("Ants: ", Gr.ants)
stepmode = 0
antbuf = Gr.ants
while (not (stepmode == 'y' or stepmode == 'n')):
    stepmode = str(input("Stepmode (y/n): "))
pylab.show()
flow = 0
for i in range(len(Gr.rooms)):
    if stepmode == 'y':
        if i == 0:
            input("Press enter to start...")
        else:
            input("Press enter to step...")
    if i > 0:
        flow = len(Gr.rooms[i]) - len(Gr.rooms[i - 1])
    Gr.ants -= flow
    if (flow >= 0):
        MyGraph.changestart(Gr, 's\n' + str(Gr.ants))
    else:
        MyGraph.changestart(Gr, 's\n' + '0')
    flow = 0
    if Gr.end in Gr.rooms[i]:
        for j in range(len(Gr.rooms[i])):
            if Gr.rooms[i][j] == Gr.end:
                flow += 1
        lst = Gr.end.split('\n')
        if len(lst) == 2:
            endcount = int(lst[1]) + flow
        else:
            endcount = flow
        MyGraph.changeend(Gr, 'e\n' + str(endcount))
    for k in range(len(Gr.rooms[i])):
        if Gr.rooms[i][k] != Gr.start and Gr.rooms[i][k] != Gr.end:
            MyGraph.changenode(Gr, Gr.rooms[i][k], Gr.rooms[i][k].split('\n')[0] + '\n' + Gr.names[i][k])
    for l in range(len(Gr.nodes)):
        if type(Gr.nodes[l][0]) == str and Gr.nodes[l][0] != Gr.start and Gr.nodes[l][0] != Gr.end:
            change = Gr.nodes[l][0].split('\n')
            duck = []
            if len(change) == 2:
                switch = 1
                for m in range(i, len(Gr.rooms)):
                    for n in range(len(Gr.rooms[m])):
                        if type(Gr.rooms[m][n]) == str:
                            fuck = Gr.rooms[m][n].split('\n')
                            if len(fuck) == 2:
                                duck.append(fuck[0])
                if change[0] in duck:
                    switch = 0
                if switch == 1:
                    MyGraph.changenode(Gr, Gr.nodes[l][0], Gr.nodes[l][0].split('\n')[0])
    pylab.clf()
    get_fig(i)
    pylab.draw()
    pause(0.5)
    if stepmode == 'y' and i == len(Gr.rooms) - 1:
        input("Press enter to exit...")

pylab.close()

