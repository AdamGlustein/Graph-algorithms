
#include "graph.h"
#include "tests.h"


bool dfs(vector<vector<int>>& adj_list, int source, int target) {
    // Finds if a node can be reached from the source in O(V) time   
    int n = adj_list.size();

    stack<int> s;
    s.push(source);
    vector<bool> visited(n,false);

    while (!s.empty()) {
        auto t = s.top();
        if (t == target) return true; // found
        s.pop();
        visited[t] = true;
        for (auto v: adj_list[t]) {
            if (!visited[v]) s.push(v);
        }
    }
    return false; // not found
}

int bfs(vector<vector<int>>& adj_list, int source, int target) {
    // Finds the fewest edges required to reach a target node from the source in O(V) time
    int n = adj_list.size();

    queue<int> q;
    q.push(source);
    vector<int> length(n,-1);
    length[source] = 0;

    while (!q.empty()) {
        auto f = q.front();
        q.pop();
        if (f == target) return length[f];
        for (auto v: adj_list[f]) {
            if (length[v] == -1) {
                q.push(v);
                length[v] = length[f]+1; // adding path length
            }
        }
    }
    return -1;
}

int djikstra(vector<vector<pii>>& adj_list, int source, int target) {
    // Finds the shortest path between vertices in a positively weighted graph in O(ElogV) time
    int n = adj_list.size();

    priority_queue<pii, vector<pii>, greater<pii>> pq; // min heap
    pq.push(mp(0,source));
    vector<int> distances(n,INT32_MAX);
    distances[source] = 0;

    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        if (p.second == target) return distances[target];
        for (auto v: adj_list[p.second]) {
            if (distances[p.second] + v.second < distances[v.first]) { // new best found
                distances[v.first] = distances[p.second] + v.second;
                pq.push(mp(distances[v.first], v.first));
            }
        }
    }
    return -1; // no path
}

bool cycleDetect(vector<vector<int>>& adj_list) {
    // Returns whether or not the graph contains a cycle in O(V) time
    // Works for both directed and undirected graphs by finding back edges (but I coded it for directed)
    int n = adj_list.size();

    stack<int> s;
    vector<bool> onStack(n,false);
    vector<bool> visited(n,false);
    bool deadEnd;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) s.push(i);
        while (!s.empty()) {
            auto t = s.top();
            onStack[t] = true;
            visited[t] = true;
            deadEnd = true;
            for (auto v: adj_list[t]) {
                if (onStack[v]) return true;
                else if (!visited[v]) {
                    deadEnd = false;
                    s.push(v);
                }
            }
            if (deadEnd) {
                s.pop();
                onStack[t] = false;
            }
        }
    }
    return false;
}

vector<int> topologicalSort(vector<vector<int>>& adj_list) {
    // Returns a valid topological sorting of a directed acyclic graph (DAG) in O(V) time
    // Useful for dependency relationships or prerequisites
    int n = adj_list.size();

    stack<int> sortStack;
    vector<bool> included(n,false);
    vector<bool> onStack(n,false); // for cycles
    stack<int> s;
    bool deadEnd;

    for (int i = 0; i < n; i++) {
        if (!included[i]) {
            s.push(i);
            while (!s.empty()) {
                auto t = s.top();
                onStack[t] = true;
                deadEnd = true;
                for (auto v: adj_list[t]) {
                    if (onStack[v]) return {}; // indicative of cycle
                    else if (!included[v]) {
                        deadEnd = false;
                        s.push(v);
                    }
                }
                if (deadEnd) { // reached an endpoint
                    s.pop();
                    onStack[t] = false;                   
                    if (!included[t]) sortStack.push(t);
                    included[t] = true;
                }
            }
        }
    }

    vector<int> sorted;
    while (!sortStack.empty()) {
        sorted.push_back(sortStack.top());
        sortStack.pop();
    }
    return sorted;
}


int prim(vector<vector<pii>>& adj_list) {
    // Returns a MST of the graph in O(ElogV) time
    // If graph is disconnected return -1
    int n = adj_list.size();

    vector<bool> inMst(n);
    int start = 0;
    int included = 1;
    int cost = 0;
    inMst[start] = true;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (auto v: adj_list[start]) pq.push(mp(v.second, v.first));

    while (included != n && !pq.empty()) {
        auto p = pq.top();
        pq.pop();
        if (!inMst[p.second]) { // add to mst
            cost += p.first;
            included++;
            inMst[p.second] = true;
            for (auto v: adj_list[p.second]) pq.push(mp(v.second, v.first));
        }
    }

    if (included != n) return -1;
    return cost;
}

int bellmanFord(vector<vector<pii>>& adj_list, int source, int target) {
    // Shortest path in a graph with negative edge weights in O(VE) time
    // Also applicable for "weird" pathfinding, for example you get to cut out one edge
    int n = adj_list.size();

    vector<int> distances(n, INT32_MAX);
    distances[source] = 0;

    for (int i = 0; i < n-1; i++) { // V-1 relaxations
        for (int j = 0; j < n; j++) {
            if (distances[j] != INT32_MAX) { // visited
                for (auto e: adj_list[j]) {
                    distances[e.first] = min(distances[j] + e.second, distances[e.first]);
                }
            }
        }
    }

    if (distances[target] == INT32_MAX) return INT32_MAX; // 1. not found

    for (int i = 0; i < n; i++) {
        for (auto e: adj_list[i]) { // 2. check for negative cycle
            if (distances[e.first] > distances[i] + e.second) return INT32_MIN;
        }
    }

    return distances[target]; 
}

vector<vector<int>> floydWarshall(vector<vector<pii>>& adj_list) {
    // Finds the shortest path between ALL pairs of vertices, negative weight allowed
    // Dead simple: instantiate all distances to A. Vertex-to-itself and B. All edges
    // Loop through all i,j,k and 'cut-off' the path between i-j using node k => O(V^3) time
    int n = adj_list.size();

    vector<vector<int>> sp(n, vector<int>(n, 100000));
    for (int i = 0; i < n; i++) { // cover vertices and edges
        sp[i][i] = 0; 
        for (auto e: adj_list[i]) sp[i][e.first] = e.second;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                sp[i][j] = min(sp[i][j], sp[i][k]+sp[k][j]);
            }
        }
    }

    return sp;

    // Note: if all weights are positive, then can just do V iterations of Djikstra at VElogV if E ~= V
}

vector<int> hierholzerEulerian(vector<vector<int>> adj_list) {
    // Finds the Eulerian path/cycle in a directed graph in O(V+E) time
    // Eulerian path/cycle traverses all edges exactly once (with the cycle ending at start vertex)

    int n = adj_list.size();

    vector<int> degree(n);
    int start = 0;
    int end = 0;

    // Check if graph is Eulerian - either all zero degree (cyclic) or one (1,-1) pair
    for (int i = 0; i < n; i++) {
        for (int v: adj_list[i]) degree[v]--;
        degree[i] += adj_list[i].size();
    }
    bool oneFlag = false;
    bool minusFlag = false;
    for (int i = 0; i < n; i++) {
        if (abs(degree[i]) > 1) return {};
        else if (degree[i] == 1) {
            if (oneFlag) return {};
            else {
                oneFlag = true;
                start = i;
            }
        }
        else if (oneFlag == -1) {
            if (minusFlag) return {};
            else {
                minusFlag = true;
                end = i;
            }
        }
    }

    // Find the Euler path using dfs
    stack<int> dfs;
    dfs.push(start);
    vector<int> euler = {};

    while (!dfs.empty()) {
        int t = dfs.top();
        if (!adj_list[t].empty()) {
            dfs.push(adj_list[t].back());
            adj_list[t].pop_back();
        }
        else {
            euler.push_back(t);
            dfs.pop();
        }
    }

    reverse(euler.begin(), euler.end());
    return euler;
}



int main() {
    // Undirected graph 1 (dfs/bfs/cycleDetect)
    vector<vector<int>> u1  = {
        {1},
        {0,3,5,6},
        {3,5}, 
        {1,2,4,6},
        {3},
        {1,2},
        {1,3}
    };
    // Undirected graph 2 
    vector<vector<int>> u2 = {
        {2,3},
        {2,5},
        {0,1},
        {0},
        {5},
        {1,4}
    };
    // Undirected graph 3
    vector<vector<int>> u3 = {
        {1,2,4,5},
        {0,3,4,5},
        {0,3,5},
        {1,2,5},
        {0,1},
        {0,1,2,3},
        {7},
        {6}
    };

    // Directed graph 1 (topSort/Eulerian/tarjan)
    vector<vector<int>> d1 = {
        {1,6},
        {2,3},
        {3,4},
        {5},
        {},
        {},
        {1}
    };
    // Directed graph 2
    vector<vector<int>> d2 = {
        {1},
        {2},
        {3,4},
        {1,5},
        {},
        {},
        {1}
    };
    // Directed graph 3 (Eulerian)
    vector<vector<int>> d3 = {
        {5},
        {0,2},
        {3},
        {4},
        {6},
        {1},
        {4}
    };
    // Directed graph 4 (Eulerian)
    vector<vector<int>> d4 = {
        {5},
        {2,4,6,0},
        {3},
        {1},
        {1,6},
        {1},
        {4,1}
    };

    // Weighted undirected graph 1 (djikstra/minTrees/bellman/floydWarshall)
    vector<vector<pii>> wu1 = {
        {mp(1,6), mp(2,2)},
        {mp(2,3), mp(0,6), mp(4,4), mp(5,2)},
        {mp(0,2), mp(1,3), mp(3,2)},
        {mp(2,2), mp(4,7), mp(6,5)},
        {mp(1,4), mp(5,1), mp(3,7), mp(6,3), mp(7,8)},
        {mp(1,2), mp(4,1)},
        {mp(3,5), mp(4,3), mp(7,6), mp(8,12)},
        {mp(4,8), mp(6,6)},
        {mp(6,12)}
    };
    // Weighted undirected graph 2
    vector<vector<pii>> wu2 = {
        {mp(1,6), mp(2,2)},
        {mp(2,3), mp(0,6), mp(5,2), mp(3,4)},
        {mp(0,2), mp(1,3), mp(3,2)},
        {mp(2,2), mp(4,1), mp(6,5), mp(1,4), mp(5,1)},
        {mp(3,1), mp(7,8), mp(6,3)},
        {mp(1,2), mp(3,1)},
        {mp(3,5), mp(4,3), mp(7,6)},
        {mp(4,8), mp(6,6)}
    };

    // Weighted directed graph 1 (maxFlow)
    vector<vector<pii>> wd1 = {   
        {mp(1,6),mp(6,7)},
        {mp(2,5),mp(3,5)},
        {mp(3,8),mp(4,3)},
        {mp(5,2)},
        {},
        {},
        {mp(1,5)}
    };
    // Weighted directed graph 2 (negative edge BF)
    vector<vector<pii>> wd2 = {   
        {mp(1,6),mp(6,7)},
        {mp(2,5),mp(3,5)},
        {mp(3,-8),mp(4,3)},
        {mp(5,2)},
        {},
        {},
        {mp(1,-2)}
    };
    // Weighted directed graph 3 (negative cycle)
    vector<vector<pii>> wd3 = {   
        {mp(1,6),mp(6,7)},
        {mp(2,5)},
        {mp(3,1),mp(4,3)},
        {mp(5,2),mp(1,-7)},
        {},
        {},
        {mp(1,5)}
    };

    // Testing

    cout << "Testing: " << endl;
    vector<vector<vector<int>>> uwtests = {u1,u2,u3};
    vector<vector<vector<pii>>> wtests = {wu1,wu2};
    vector<vector<vector<int>>> dtests = {d1, d2, d3};
    vector<vector<vector<pii>>> wdtests = {wd1,wd2,wd3};
    vector<vector<vector<int>>> uwtests_l = {u1,u2,u3,d1,d2,d3};
    vector<vector<vector<pii>>> wtests_l = {wu1,wu2,wd1};
    vector<vector<vector<int>>> htests = {d1,d2,d4};
    
    // Basic
    testDFS(uwtests); // O(V+E)
    testBFS(uwtests); // O(V+E)
    testCycle(uwtests_l); // O(V+E)
    testTopSort(dtests); // O(V+E)
    testDjikstra(wtests); // O(ElogV)
    
    // MSTs
    testPrim(wtests_l); // O(ElogV)

    // Pathfinding
    testBeFo(wdtests); // O(VE)
    testFlWa(wtests_l); // O(V^3)
    testHierholzer(htests); // O(V+E)

    // Tarjan and Flow done in Python!
}