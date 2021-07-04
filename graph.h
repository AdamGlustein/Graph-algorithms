
/**
 * May 26th, 2021
 * A thorough exploration of 22 graph algorithms
 * */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

#define pii pair<int, int>
#define mp make_pair

using namespace std;

// 1. Basic
bool dfs(vector<vector<int>>& adj_list, int source, int target);
int bfs(vector<vector<int>>& adj_list, int source, int target);
int djikstra(vector<vector<pii>>& adj_list, int source, int target);
bool cycleDetect(vector<vector<int>>& adj_list);
vector<int> topologicalSort(vector<vector<int>>& adj_list);

// 2. Intermediate

// 2.1 Minimum Spanning Trees
int prim(vector<vector<pii>>& adj_list);

// 2.2 Advanced Path Finders
int bellmanFord(vector<vector<pii>>& adj_list, int source, int target);
vector<int> hierholzerEulerian(vector<vector<int>> adj_list);
vector<vector<int>> floydWarshall(vector<vector<pii>>& adj_list);

// 2.3: Tarjan Derivatives (done in Python)
/**
 * Strongly connected components, articulation points, bridges
 */

// 2.4 Ford-Fulkerson Derivatives (done in Python)
/**
 * Max-flow min-cut problem, maximum bipartite matching
 */

// 3. Advanced (NP-hard) done in Python