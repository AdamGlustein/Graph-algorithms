#include "graph_algos.h"

/* This document contains the code of many important graph algorithms.
All implementations use adjacency lists. The algorithms include: 
1. DFS
2. Topological Sort
3. Cycle detection
4. BFS
5. Djikstra's Shortest Path  (Positive edge weights)
6. Bellman-Ford's Shortest Path (Negative edge weights)
7. Prim's Minimum Spanning Tree 
8. Ford-Fulkerson Maximum Flow (plus MinCut and Bipartite Matching)
9. Edmond-Karps implementation 
10. Tarjan's Strongly Connected Components 
11. Hierholzer's Euler Circuit/Path
*/

vector<int> DFS(int start, int end, vector<vector<int>> adj_list) {
    // Returns path from start vertex to end vertex
    int n = adj_list.size();
    if (start == end) return {start}; // edge case

    stack<int> s;
    vector<bool> visited(n,false);
    vector<int> parent(n,-1);
    s.push(start);
    while (!s.empty()) {
        int curr = s.top(); s.pop();
        visited[curr] = true;
        for (int i = 0; i < adj_list[curr].size(); i++) {
            if (adj_list[curr][i] == end) { // found
                int tmp = adj_list[curr][i];
                parent[tmp] = curr;
                vector<int> path;
                while (tmp != -1) {
                    path.push_back(tmp);
                    tmp = parent[tmp];
                }
                reverse(path.begin(), path.end());
                return path;
            }
            else if (!visited[adj_list[curr][i]]) { // new node
                s.push(adj_list[curr][i]);
                parent[adj_list[curr][i]] = curr;
            }
        }
    }
    return {}; // not found
    // Time: O(V+E), Space: O(V)
}

vector<int> BFS(int start, int end, vector<vector<int>> adj_list) {
    // Returns shortest path from start to end in unweighted graph
    int n = adj_list.size();
    if (start == end) return {start};

    vector<bool> visited(n,false);
    vector<int> parent(n,-1);
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        visited[curr] = true;
        for (int dest: adj_list[curr]) {
            if (dest == end) {
                parent[dest] = curr;
                vector<int> path;
                while (dest != -1) {
                    path.push_back(dest);
                    dest = parent[dest];
                }
                reverse(path.begin(), path.end()); // optimally push to a stack instead
                return path;
            }
            else if (!visited[dest]) {
                q.push(dest);
                parent[dest] = curr;
            }
        }
    }
    return {};
    // Time: O(V+E), Space: O(V)
}

vector<int> CycleDetect(vector<vector<int>> adj_list) {
    // Returns a cycle in the graph
    int n = adj_list.size();
    vector<bool> visited(n,false);
    vector<bool> on_stack(n,false);
    vector<int> parent(n,-1);
    
    for (int i = 0; i < n; i++) {
        stack<int> s;
        if (!visited[i]) s.push(i);
        while (!s.empty()) {
            int curr = s.top(); 
            on_stack[curr] = true;
            visited[curr] = true;
            bool dead_end = true;
            for (int dest: adj_list[curr]) {
                if (on_stack[dest]) { // back edge
                    vector<int> cycle;
                    int tmp = curr;
                    while (tmp != dest) {
                        cycle.push_back(tmp);
                        tmp = parent[tmp];
                    }
                    cycle.push_back(dest);
                    return cycle;
                }
                else if (!visited[dest]) {
                    s.push(dest);
                    parent[dest] = curr;
                    dead_end = false;
                }
            }
            if (dead_end) {
                on_stack[curr] = false;
                s.pop();
            }

        }
    }
    return {}; // no cycle
    // Time: O(V+E), one full DFS across all components
    // Space: O(V)
}

vector<int> TopSort(vector<vector<int>> adj_list) {
    // Return topological sorting of list (if not cyclic)
    int n = adj_list.size();
    stack<int> s;
    vector<bool> visited(n,false);
    vector<bool> on_stack(n,false); // for cycle
    vector<bool> in_sort(n,false);
    vector<int> sorted;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) s.push(i);
        while (!s.empty()) {
            int curr = s.top();
            visited[curr] = true;
            on_stack[curr] = true;
            bool dead_end = true;
            for (int dest: adj_list[curr]) {
                if (on_stack[dest]) return {};
                else if (!visited[dest]) {
                    s.push(dest);
                    dead_end = false;
                }
            }
            if (dead_end) {
                s.pop();
                on_stack[curr] = false;
                if (!in_sort[curr]) {
                    sorted.push_back(curr);
                    in_sort[curr] = true;
                }
            }
        }
    }
    reverse(sorted.begin(), sorted.end());
    return sorted;
    // Time: O(V+E), Space: O(V)
}

vector<int> Djikstra(int start, int end, vector<vector<pair<int,int>>> adj_list) {
    // Return shortest path in weighted graph: {path..., distance}
    if (start == end) return {0,start};
    int n = adj_list.size();

    vector<int> distances(n,10000000);
    vector<int> parent(n,-1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, std::greater<pair<int,int>>> pq;
    pq.push(make_pair(0,start));
    distances[start] = 0;

    while (!pq.empty()) {
        int curr = pq.top().second; 
        pq.pop();
        if (curr == end) {
            vector<int> path;
            path.push_back(distances[end]);
            while (curr != start) {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }
        for (pair<int,int> edge: adj_list[curr]) {
            if (distances[curr] + edge.second < distances[edge.first]) {
                distances[edge.first] = distances[curr] + edge.second;
                pq.push(make_pair(distances[edge.first], edge.first));
                parent[edge.first] = curr;
            }
        }
    }
    return {}; // no path
    // Time: O(V+ElogV), Space: O(V)
}

int FordFulkerson(int source, int sink, vector<vector<int>> adj_matrix) {
    // Returns maximum flow from s-t 
    int n = adj_matrix.size();
    int flow = 0;

    stack<vector<int>> s; // {node, parent, bottleneck}
    vector<bool> visited(n,false);
    vector<int> parent(n,-1);
    s.push({source, -1, 100000});

    while (!s.empty()) { // augmenting paths
        vector<int> curr = s.top(); s.pop();
        visited[curr[0]] = true;

        for (int i = 0; i < n; i++) {
            int edge = adj_matrix[curr[0]][i];
            if (i == sink && edge != 0) {
                int augment = min(edge, curr[2]);
                cout << augment << ": ";
                flow += augment;
                parent[sink] = curr[0];
                int bt = sink;
                for (int x: parent) cout << x << " "; cout << endl;
                while (bt != source) { // updates edges
                    cout << parent[bt] << " ";
                    adj_matrix[parent[bt]][bt] -= augment;
                    adj_matrix[bt][parent[bt]] += augment;
                    bt = parent[bt];
                }
                while (s.size() > 1) s.pop(); // clearing stack
                fill(visited.begin(), visited.end(), false); // reset visited
                fill(parent.begin(), parent.end(), -1); // reset parents
            }
            else if (edge != 0 && !visited[i]) { // continue DFS
                s.push({i, curr[0], min(curr[2], edge)});
                parent[i] = curr[0];
            }
        }
    }
    return flow;
}

vector<pair<int,int>> Prim(vector<vector<pair<int,int>>> adj_list) {
    // Returns a minimum spanning tree for the graph
    typedef pair<int,int> iPair;
    int n = adj_list.size();
    vector<bool> in_tree(n,false);
    vector<iPair> mst;
    priority_queue<vector<int>, vector<vector<int>>, std::greater<vector<int>>> pq; // {weight, node, parent}
    int tree_size = 0;

    pq.push({0,0,0});
    while (tree_size < n) {
        vector<int> curr = pq.top(); pq.pop();
        if (!in_tree[curr[1]]) { // add to MST
            mst.push_back(make_pair(curr[2], curr[1]));
            in_tree[curr[1]] = true;
            tree_size++;
        }
        for (iPair edge: adj_list[curr[1]]) {
            if (!in_tree[edge.first]) {
                pq.push({edge.second, edge.first, curr[1]});
            }
        }
    }
    return mst;
    // Time: O(V+E), Space: O(E)
}

int BellmanFord(int start, int end, vector<vector<pair<int,int>>> adj_list) {
    // Returns shortest path in graph with negative edge weighting (to any node)
    typedef pair<int,int> iPair;
    int n = adj_list.size();
    vector<int> distances(n,1000000);
    distances[start] = 0;
    for (int i= 0; i < n-1; i++) {
        stack<iPair> s;
        vector<bool> visited(n,false);
        s.push(make_pair(0,start));
        while (!s.empty()) {
            iPair curr = s.top(); s.pop();
            visited[curr.second] = true;
            for (iPair edge: adj_list[curr.second]) {
                if (edge.second + curr.first < distances[edge.first]) {
                    distances[edge.first] = edge.second + curr.first;
                }
                if (!visited[edge.first]) s.push(make_pair(distances[edge.first],edge.first));
            }
        }
    }
    int first = distances[end];
    for (int i= 0; i < n-1; i++) { // second iteration to check for negative cycles
        stack<iPair> s;
        vector<bool> visited(n,false);
        s.push(make_pair(0,start));
        while (!s.empty()) {
            iPair curr = s.top(); s.pop();
            visited[curr.second] = true;
            for (iPair edge: adj_list[curr.second]) {
                if (edge.second + curr.first < distances[edge.first]) {
                    distances[edge.first] = edge.second + curr.first;
                }
                if (!visited[edge.first]) s.push(make_pair(distances[edge.first],edge.first));
            }
        }
    }
    int second = distances[end];
    if (first == second) return first;
    else return -100000; // negative cycle
    // Time: O(VE), Space: O(V)
}

vector<pair<int,int>> Hierholzer(vector<vector<int>> adj_list) {
    // Return Euler path/circuit if it exists
    int n = adj_list.size();
    vector<int> in_degree(n,0);
    vector<int> out_degree(n,0);
    for (int i = 0; i < n; i++) { // O(E)
        for (int dest: adj_list[i]) {
            in_degree[dest]++;
            out_degree[i]++;
        }
    }
    int source = -1; int sink  = -1;
    for (int i = 0; i < n; i++) { // finding source and sink if semi-Eulerian
        if (abs(out_degree[i] - in_degree[i]) > 1) {
            return {};
        }
        else if (out_degree[i] - in_degree[i] == 1) {
            if (source == -1) source = i;
            else return {};
        }
        else if (in_degree[i] - out_degree[i] == 1) {
            if (sink == -1) sink = i;
            else return {};
        }
    }
    if (source == -1 && sink != -1 || sink == -1 && source != -1) return {};
    if (source == -1) { // Euler circuit exist
        source = 0;
        sink = 0;
    }
    // DFS exploration removing each edge each time; once a dead end is reached, push on to vector and continue
    stack<pair<int,int>> s;
    vector<pair<int,int>> euler;
    for (int dest: adj_list[source]) {
        s.push(make_pair(source, dest));
    }

    while (!s.empty()) {
        pair<int,int> edge = s.top();
        cout << edge.first << " " << edge.second << endl;
        bool dead_end = true;
        for (int dest: adj_list[edge.second]) {
            dead_end = false;
            s.push(make_pair(edge.second, dest));
        }
        if (dead_end) {
            euler.push_back(edge);
            s.pop();
        }
        adj_list[edge.first].pop_back(); // removing edge
    }
    reverse(euler.begin(), euler.end());
    return euler;
}

vector<vector<int>> TarjanSCC(vector<vector<int>> adj_list) {
    // Returns the strongly connected components of the graph
    int n = adj_list.size();
    vector<bool> visited(n, false);
    vector<bool> on_stack(n, false);
    vector<int> llv(n, -1);
    vector<int> disc(n, -1);
    vector<int> parent(n,-1);
    int id = 0;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        stack<int> s;
        s.push(i);
        while (!s.empty()) {
            int curr = s.top();
            if (!visited[curr]) {
                disc[curr] = id; id++;
                llv[curr] = disc[curr];
                on_stack[curr] = true;
                visited[curr] = true;
            }
            bool dead_end = true;
            for (int dest: adj_list[curr]) {
                if (on_stack[dest]) { // SCC found
                    int currC = curr;
                    llv[currC] = min(llv[currC], llv[dest]);
                    while (currC != dest) {
                        llv[parent[currC]] = min(llv[parent[currC]], llv[currC]);
                        currC = parent[currC];
                    }
                }
                else if (!visited[dest]) {
                    dead_end = false;
                    s.push(dest);
                    parent[dest] = curr;
                }
            }
            if (dead_end) {
                s.pop();
                on_stack[curr] = false;
            }
        }
    }
    unordered_map<int, vector<int>> sccs;
    for (int i = 0; i < n; i++)
        sccs[llv[i]].push_back(i);
    vector<vector<int>> SCC;
    for (auto it = sccs.begin(); it != sccs.end(); it++) {
        SCC.push_back(it->second);
    }
    return SCC;
    // Time: O(V+E) (one-pass DFS), Space: O(V)
}

int main() {
    // Driver
    // Create a graph as an adjacency list and test out each algorithm!
    vector<vector<int>> adj_list;
    adj_list = {
        {1},
        {2,3,4},
        {0,3},
        {},
        {3},
        {6},
        {7},
        {5}
    };
    vector<vector<int>> sccs = TarjanSCC(adj_list);
    cout << "SCCs: " << endl;
    for (vector<int> scc: sccs) {
        for (int x: scc) cout << x << " ";
        cout << endl;
    }
    cout << endl;
}