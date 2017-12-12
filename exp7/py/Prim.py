import json
from functools import reduce


class Edge:
    '''边类 '''

    def __init__(self, v1, v2,   weight=1):
        self.v1 = v1
        self.v2 = v2

        self.weight = weight

    @classmethod
    def reverse(cls, e):
        '''return a new edge which is reversed'''
        return cls(e.v2, e.v1, e.weight)

    def __hash__(self):
        return hash(str(self.v1) + str(self.v2) + str(self.weight))

    def __str__(self):

        return "({}->{}, {})".format(self.v1, self.v2, self.weight)

    def __repr__(self):
        return "[<{},{}>,{}]".format(self.v1, self.v2, self.weight)

    def __eq__(self, obj):
        return hash(self) == hash(obj)


class Vertex:
    '''Vertex class'''

    def __init__(self, index, data):
        self.index = index
        self.data = data


class Network:
    '''Network'''

    def __init__(self, filename=None, dic=None):
        self.edges = []
        self.adjlist = []
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

        except Exception as e:
            print(e)
            raise e

    def build(self):
        ''''build this network'''
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

    @staticmethod
    def prim(net, start):
        '''generate a lowcost tree'''
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
        dic = dict(kind="DN", vertexnum=net.vertex_num, edges=[
                   [e.v1, e.v2, e.weight] for e in edge_added])
        minspantree = Network(dic=dic)
        minspantree.build()
        return minspantree

    def __repr__(self):
        ret = "kind {}, {} vertexs, {} edges. ".format(
            self.kind, self.vertex_num, len(self.edges))
        ret += "Edges:" + str(self.edges)
        return ret

    def __str__(self):
        ret = "kind {}, {} vertexs, {} edges.\n".format(
            self.kind, self.vertex_num, len(self.edges))
        ret += "Edges: \n"
        for i in range(len((self.adjlist))):
            ret += "{} -> {}\n".format(i, [(x.v2, x.weight)
                                           for x in self.adjlist[i]])
        return ret


def main():
    N = Network("network.json")
    N.build()
    print(N)
    while True:
        try:
            start = int(input('请输入起始点:'))
        except ValueError:
            print("错误的输入！")
            continue
        except KeyboardInterrupt:
            print('退出...')
            break
        if start>N.vertex_num or start<0:
            print("顶点不在图中！")
            continue
        print('由{}出发的其中一颗最小生成树如下\n'.format(start))
        m = N.prim(N, start)
        print(m)
        print("边长和为 {} ".format(
            reduce(lambda x, y: x + y, [e.weight for e in m.edges])))


if __name__ == '__main__':
    main()
