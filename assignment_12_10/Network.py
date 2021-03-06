#!/usr/bin/env python3
'''Network '''
import json
from functools import reduce


class Edge:
    '''边类 *不支持平行边*。
     v1 起始顶点序号，
     v2 目标顶点序号，
     weight 权重/长度
    '''

    def __init__(self, v1, v2, weight=1):
        self.v1 = v1
        self.v2 = v2

        self.weight = weight

    @classmethod
    def reverse(cls, e):
        '''return a new edge which is reversed'''
        return cls(e.v2, e.v1, e.weight)

    def __hash__(self):
        return hash(str(self.v1) + str(self.v2))

    def __str__(self):

        return "({}->{}, {})".format(self.v1, self.v2, self.weight)

    def __repr__(self):
        return "[<{},{}>,{}]".format(self.v1, self.v2, self.weight)

    def __eq__(self, obj):
        return hash(self) == hash(obj)


class Vertex:
    '''Vertex class
    顶点类
    index: 改顶点的索引
    data : 该点的数据
    '''

    def __init__(self, index, data):
        self.index = index
        self.data = data

    def __str__(self):
        return str(self.data)

    def __repr__(self):
        return str(self.data)

    def __hash__(self):
        return hash(self.index)


class Network:
    '''网络类。
    filename: 描述该图的json文件。
    dic: 描述该图的字典。

    '''

    def __init__(self, filename=None, dic=None):

        self.edges = []
        self.adjlist = []
        self.vertex = []
        d = {}
        if filename is not None:
            with open(filename) as f:
                d = json.load(f)
        else:
            d = dic
        try:
            self.kind = d['kind']
            self.vertex_num = d['vertexnum']
            for l in d['edges']:
                e = Edge(l[0], l[1], l[2])
                self.edges.append(e)
            if d.__contains__('vertex'):
                for i in range(d['vertexnum']):
                    self.vertex.append(Vertex(i, d['vertex'][i]))
            else:
                for i in range(d['vertexnum']):
                    self.vertex.append(Vertex(i, str(i)))

        except Exception as e:
            print(e)
            raise e

    def build(self):
        '''build this network'''
        self.adjlist = [set() for i in range(self.vertex_num)]
        # 用set去重
        for e in self.edges:
            self.adjlist[e.v1].add(e)
            if self.kind[0] == 'U':
                self.adjlist[e.v2].add(e.reverse(e))
        # change into list and sort
        for i in range(len(self.adjlist)):
            # print(self.adjlist[i])
            self.adjlist[i] = list(self.adjlist[i])
            # print( list(self.adjlist[i]))
            self.adjlist[i].sort(key=lambda x: x.weight)

    def addedge(self, e):
        '''
        将边e加入到当前图中
        '''

        self.edges.append(e)
        self.adjlist[e.v1].append(e)

    def sum_of_edges(self):
        '''返回该图中所有边的长度和
        '''
        return reduce(lambda x, y: x + y, [e.weight for e in self.edges])

    @staticmethod
    def prim(net, start):
        '''
        用prim算法生成一颗最小生成树
        start : 起点
        返回Network类
        '''
        p = start
        edge_added = list()
        vertex_added = list()
        vertex_added.append(p)
        while len(vertex_added) != net.vertex_num:
            e = None
            elist = list()
            # 已经预先排序
            # 找到每个已经加进列表中的顶点相连的代价最小的边，加入elist
            for p in vertex_added:
                for e in net.adjlist[p]:
                    if (e not in edge_added) and (e.v2 not in vertex_added):
                        elist.append(e)
                        break
            # 找到elist中最小的边, 以权重为key
            elist.sort(key=lambda x: x.weight)
            # try :
            e = elist[0]
            edge_added.append(e)
            vertex_added.append(e.v2)
        # print(vertex_added)
        # print(str(edge_added))
        dic = dict(
            kind="DN",
            vertexnum=net.vertex_num,
            edges=[[e.v1, e.v2, e.weight] for e in edge_added],
            vertex=net.vertex
        )
        minspantree = Network(dic=dic)
        minspantree.build()
        return minspantree

    @staticmethod
    def find(path, v):

        while path[v] != -1:
            v = path[v]
        return v

    @staticmethod
    def kruskal(net):
        '''
        用kruskal算法生成一颗最小生成树
        返回Network类
        '''
        mcst = Network(
            dic=dict(kind='DN', vertexnum=net.vertex_num, edges=[], vertex=net.vertex))
        mcst.build()
        net.edges.sort(key=lambda x: x.weight)
        path = [-1 for i in range(net.vertex_num)]
        # edges =set( [  net.edges] )
        added = set()
        for e in net.edges:
            if len(mcst.edges) >= (mcst.vertex_num - 1):
                break
            if e.v1 > e.v2 and net.kind[0] is 'U':
                e = e.reverse()
            if e in added:
                continue
            else:
                added.add(e)

            if net.find(path, e.v1) != net.find(path, e.v2):
                i = net.find(path, e.v1)
                path[i] = e.v2
                mcst.addedge(e)

        return mcst

    def __repr__(self):
        ret = "kind {}, {} vertexs, {} edges. ".format(
            self.kind, self.vertex_num, len(self.edges))
        ret += "Edges:" + str(self.edges)
        return ret

    def __str__(self):
        ret = "kind {}, {} vertexs, {} edges, sum of edges : {}\n".format(
            self.kind, self.vertex_num, len(self.edges), self.sum_of_edges())
        ret += "Edges: \n"
        for i in range(len((self.adjlist))):
            ret += "{} -> {}\n".format(self.vertex[i], [(self.vertex[x.v2], x.weight)
                                                        for x in self.adjlist[i]])
        return ret

    @staticmethod
    def topologic(net):
        '''拓扑排序算法，返回该图的一个拓扑序列(储存为顶点的列表)
        '''
        tpl = []
        # 构建入度表，用于查询无入度的节点
        indegree = [0 for i in range(net.vertex_num)]
        for e in net.edges:
            indegree[e.v2] = indegree[e.v2] + 1
        # 顶点集合
        v_set = set(iter(net.vertex))

        # print(indegree)
        v = None
        while len(v_set) > 0:
            for v in v_set:
                if indegree[v.index] == 0:
                    break
            v_set.discard(v)
            for e in net.adjlist[v.index]:
                indegree[e.v2] = indegree[e.v2] - 1
            tpl.append(v)
        # print(indegree)
        # print(tpl)
        return tpl

    @staticmethod
    def topologic_all(net):
        '''拓扑排序算法，返回该图的所有拓扑序列(储存为顶点的列表)
        未完成
        '''
        # 用list模拟一个stack
        stack = list()
        # 构建入度表，用于查询无入度的顶点
        indegree = [0 for i in range(net.vertex_num)]
        for e in net.edges:
            indegree[e.v2] = indegree[e.v2] + 1
        zeroindegree = [x for x in net.vertex if indegree[x.index] == 0]
        for i in zeroindegree:
            for v in zeroindegree:
                stack.append(v)
                for vertex in net.vertex:
                    if (indegree[vertex.index] != 0)or (vertex in stack):
                        continue
                    stack.append(vertex)
                    for e in net.adjlist[vertex.index]:
                        indegree[e.v2] = indegree[e.v2] - 1
            print(stack)
            stack.pop()
            zeroindegree = [x for x in net.vertex if indegree[x.index] == 0]

    def DFS(self, start=0):
        '''Depth First Search 深度优先搜索\n
        start 搜索起点的索引
        返回值 一个包含搜索结果的列表
        '''
        ret = list()
        # 用list模拟一个stack
        # 里面存放顶点索引
        stack = list()
        stack.append(self.vertex[start])
        visited = [False for i in range(self.vertex_num)]
        while True:
            try:
                # 取栈顶元素
                vertex = stack.pop()
            except IndexError:
                # 栈空时抛出 IndexError异常，此时跳出循环
                # print("Empty")
                break
            if visited[vertex.index] is True:
                continue
            # 该顶点vertex未被访问,则访问
            ret.append(vertex)
            visited[vertex.index] = True
            # vertex 中的每个未被访问过的邻接顶点入栈
            for edge in self.adjlist[vertex.index]:
                adj_vertex = self.vertex[edge.v2]
                if visited[adj_vertex.index] is False:
                    stack.append(adj_vertex)

        return ret

    def havepath(self, start, dest):
        '''判断两个顶点之间是否可达\n
            start 起点
            dest 终点
            返回值 True/False
        '''
        if start == dest:
            return True
        # 用list模拟一个stack
        # 里面存放顶点索引
        have_way = False
        stack = list()
        stack.append(self.vertex[start])
        visited = [False for i in range(self.vertex_num)]
        while True:
            try:
                # 取栈顶元素
                vertex = stack.pop()
            except IndexError:
                # 栈空时抛出 IndexError异常，此时跳出循环
                # print("Empty")
                break
            if visited[vertex.index] is True:
                continue
            # 该顶点vertex == dest 找到,break
            if vertex.index == dest:
                have_way = True
                break
            visited[vertex.index] = True
            # vertex 中的每个未被访问过的邻接顶点入栈
            for edge in self.adjlist[vertex.index]:
                adj_vertex = self.vertex[edge.v2]
                if visited[adj_vertex.index] is False:
                    stack.append(adj_vertex)

        return have_way

    def print_matrix(self):
        '''打印邻接矩阵
         '''
        for vertex in self.vertex:
            line = [0 for i in range(self.vertex_num)]
            for edge in self.adjlist[vertex.index]:
                line[edge.v2] = edge.weight
            print(line)


def main():
    '''main'''
    N = Network("7.9.json")
    N.build()
    print(N)
    N.print_matrix()
    #print(N.prim(N, 0))
    #print(N.kruskal(N))
    print("拓扑排序")
    t = Network.topologic(N)
    print(t)
    print("DFS:")
    dfs = N.DFS(0)
    print(dfs)
    print("{}到{}".format(N.vertex[0], N.vertex[-1]))
    if N.havepath(N.vertex[0].index, N.vertex[-1].index):
        print("有路径可达")
    else:
        print("无路径可达")


if __name__ == '__main__':
    main()
