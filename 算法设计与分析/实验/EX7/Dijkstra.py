# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-06-04 21:47:50
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-06-05 19:27:37
import heapq
import math
graph = {
    'a':{"b":5,"c":1},
    'b':{"a":5,"c":2,"d":1},
    'c':{"a":1,"b":2,"d":4,"e":8},
    'd':{"b":1,"c":4,"e":3,"f":6},
    'e':{"c":8,"d":3},
    'f':{"d":6},
	}

def init_distance(graph,s):
    distance = {s:0}
    for one in graph.keys():
        if one != s:
            distance[one] = math.inf
    return distance

visit = set()

def Dijkstra(graph,s):
    pqueue = []
    #放进队列的值 一个是距离 一个是节点
    heapq.heappush(pqueue,(0,s))
    #前一个节点
    parent = {s:None}
    #从s到这个点的距离 初始化为最大值
    distance = init_distance(graph,s)
    while len(pqueue) != 0:
        pair = heapq.heappop(pqueue)
        #到这个点的距离
        cur_distance = pair[0]
        cur = pair[1]
        #被拿出来了就不用放进去了
        visit.add(cur)
        #与当前节点连接的点
        for nexts in graph[cur].keys():
        	#如果还没有拿出来过
            if  nexts not in visit:
            	#松弛操作
                if graph[cur][nexts]+cur_distance < distance[nexts]:  #当前这种走法更小
                    heapq.heappush(pqueue,(graph[cur][nexts]+cur_distance,nexts))
                    parent[nexts] = cur#修改前节点
                    distance[nexts] = graph[cur][nexts]+cur_distance#修改 这种走更短
    return parent,distance


def getPath(parent,end):
	pathList = []
	tmp = parent[end]
	pathList.append(end)
	while tmp != None:
		pathList.append(tmp)
		tmp = parent[tmp]
	return pathList

#a 是起点
parent,distance = Dijkstra(graph,'a')
for i in graph.keys():
	res = getPath(parent,i)
	print("到{}的最短距离是{},路径为{}".format(i,distance[i],res))
