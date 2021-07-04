from queue import Queue, LifoQueue, PriorityQueue
from copy import deepcopy

# A few graph algorithms...in Python this time!

# P-cleanup

def max_flow_min_cut(adj_list, source, sink):
    # Returns the integer max flow which is also the min-cut
    # Using Edmonds-Karp implementation (bfs to find augmenting paths), we get O(VE^2) time
    # Strongly polynomial in comparison to dfs FF which is O(FE)
    
    n = len(adj_list)
    res_graph = deepcopy(adj_list)
    maxflow = 0

    def bfsParents(adj_list, source, sink, n):
        q = Queue()
        visited = [False for i in range(n)]
        parent = [-1 for i in range(n)]
        q.put(source)
        while not q.empty():
            f = q.get()
            visited[f] = True
            if f == sink:
                return parent
            for i in range(n):
                if adj_list[f][i] > 0 and not visited[i]:
                    q.put(i)
                    parent[i] = f
        
        # No paths left
        return []

    parent = bfsParents(res_graph, source, sink, n)
    while len(parent) > 0:
        curr = sink
        bottleneck = float('inf')
        # Find bottleneck flow
        while curr != source:
            bottleneck = min(bottleneck, res_graph[parent[curr]][curr])
            curr = parent[curr]
        # Update edge values
        curr = sink
        while curr != source:
            res_graph[parent[curr]][curr] -= bottleneck
            res_graph[curr][parent[curr]] += bottleneck
            curr = parent[curr]
        # Augment the flow
        maxflow += bottleneck
        parent = bfsParents(res_graph, source, sink, n)

    return maxflow

def tarjan_scc(adj_list):
    # Returns the SCCs of a directed graph in O(V+E) time
    
    n = len(adj_list)
    visited = [False for i in range(n)]
    llv = [-1 for i in range(n)]
    disc = [-1 for i in range(n)]
    onStack = [False for i in range(n)]

    def tarjan_helper(V, ctr):
        visited[V] = True
        onStack[V] = True
        disc[V] = ctr
        llv[V] = disc[V]
        ctr+=1
        for v in adj_list[V]:
            if onStack[v]:
                llv[V] = min(llv[V], llv[v])
            if not visited[v]:
                ctr = tarjan_helper(v,ctr)
                llv[V] = min(llv[V], llv[v])
        onStack[V] = False
        return ctr
    
    ctr = 0
    for i in range(n):
        if not visited[i]:
            ctr = tarjan_helper(i,ctr)

    return llv


def tarjan_ap_bridges(adj_list):
    # Returns the articulation points and bridges of an undirected graph in O(V+E) time
    # Articulation point: removing the vertex disconnects part of the graph
        # A graph is biconnective if it has no articulation points
    # Bridge: removing the edge disconnects part of the graph

    # A vertex is an articulation point if...
        # A. Root of the dfs tree and has at least two children (in the dfs tree!)
        # B. Parent u of v such that disc[u] <= llv[v]

    # Assign llv and disc values ignoring the parent in the dfs tree

    n = len(adj_list)
    visited = [False for i in range(n)]
    llv = [-1 for i in range(n)]
    disc = [-1 for i in range(n)]
    onStack = [False for i in range(n)]
    parent = [-1 for i in range(n)]
    children = [0 for i in range(n)]

    def tarjan_helper(V,ctr):
        visited[V] = True
        onStack[V] = True
        disc[V] = ctr
        llv[V] = disc[V]
        ctr+=1
        for v in adj_list[V]:
            if v == parent[V]:
                continue
            if not visited[v]:
                parent[v] = V
                children[V]+=1
                ctr = tarjan_helper(v,ctr)
                llv[V] = min(llv[v], llv[V])
            if onStack[v]:
                llv[V] = min(llv[v], llv[V])
        onStack[V] = False
        return ctr

    # Generate low-link and discovery values
    ctr = 0
    for i in range(n):
        if not visited[i]:
            ctr = tarjan_helper(i,ctr)

    ap = []
    # Check both AP conditions
    for i in range(n):
        if parent[i] == -1:
            if children[i] > 1: # root condition
                ap.append(i)
        else:
            for v in adj_list[i]:
                if llv[v] >= disc[i]:
                    ap.append(i)
                    break

    # Check bridge condition: edge (u,v) is a bridge if llv[v] > disc[u] (not >= like AP!)
    bridges = []
    for u in range(n):
        for v in adj_list[u]:
            if llv[v] > disc[u]:
                bridges.append([u,v])

    return ap, bridges

def kruskal(adj_list):
    # Returns the minimum spanning tree (MST) of the graph using union-find in O(ElogV), same as Prim's
    
    n = len(adj_list)

    class DisjointSet:
        parent = []
        rank = []
        def makeset(self,n):
            self.parent = [-1 for i in range(n)]
            self.rank = [1 for i in range(n)]

        def union(self, a, b):
            if self.rank[a] == self.rank[b]: # union by rank
                self.parent[a] = b
                self.rank[b]+=1
                self.rank[a]+=1
            elif self.rank[a] < self.rank[b]:
                self.parent[a] = b
                self.rank[a] = self.rank[b]
            else:
                self.parent[b] = a
                self.rank[b] = self.rank[a]

        def find(self, a):
            stack = []
            while self.parent[a] != -1:
                stack.append(a)
                a = self.parent[a]
            while len(stack) > 0: # path compression
                self.parent[stack.pop()] = a
            return a

    ds = DisjointSet()
    ds.makeset(n)
    mst = []

    # Sort edges by weight
    edges = [ [i,e[0],e[1]] for i in range(n) for e in adj_list[i]  ]
    edges.sort(key=lambda x: x[2])
    
    count = 0
    for e in edges:
        if ds.find(e[0]) != ds.find(e[1]):
            mst.append([e[0], e[1]])
            ds.union(e[0], e[1])
            count+=1
        if count == n-1:
            break

    return mst
        

# NP-challenge

def tsp(adj_list):
    # Returns the shortest path visiting all vertices of a graph (NP-hard) in O(n^2*2^n)
    # Really only defined for complete graphs (i.e. all vertices have an edge between them)
    # tsp(G) := min{HamCyc(G)}
    pass

def kcentres(adj_list, k):
    # Return a set of centres which minimize the distance between any centre and any vertex
    pass

def kcolorable(adj_list, k):
    # Returns whether or not a graph is k-colorable 
    pass

def hamiltonian(adj_list):
    # Returns a valid Hamiltonian path/cycle of a graph
    pass

# TESTING

if __name__ == '__main__':
    g = [ 
        [0,6,0,0,0,0,7],
        [0,0,5,5,0,0,0],
        [0,0,0,8,0,0,0],
        [0,0,0,0,0,2,0],
        [0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0],
        [0,5,0,0,0,0,0]
    ]

    g1 = [
        [5],
        [0,2],
        [3],
        [4],
        [6],
        [1],
        [4]
    ]

    g2 = [
        [1],[2],[3,4],[1,5],[],[],[1]
    ]

    g3u = [
        [1],
        [0,3,5,6],
        [3,5],
        [1,2,4,6],
        [3],
        [1,2],
        [1,3]
    ]

    g4u = [
        [2,3],[2,5],[0,1],[0],[5],[1,4]
    ]

    g5w = [
        [[1,6], [2,2]],
        [[0,6], [2,3], [3,4], [5,2]],
        [[0,2], [1,3], [3,2]],
        [[2,2], [1,4], [4,1], [5,1], [6,5]],
        [[3,1], [6,3], [7,8]],
        [[1,2], [3,1]],
        [[3,5], [4,3], [7,6]],
        [[4,8], [6,6]]
    ]

    print(kruskal(g5w))