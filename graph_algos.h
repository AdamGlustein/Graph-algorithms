#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

vector<int> DFS(int start, int end, vector<vector<int>> adj_list);
vector<int> BFS(int start, int end, vector<vector<int>> adj_list);
vector<int> CycleDetect(vector<vector<int>> adj_list);
vector<int> TopSort(vector<vector<int>> adj_list);
vector<int> Djikstra(int start, int end, vector<vector<pair<int,int>>> adj_list);
int FordFulkerson(int source, int sink, vector<vector<int>> adj_matrix);
vector<pair<int,int>> Prim(vector<vector<pair<int,int>>> adj_list);
int BellmanFord(int start, int end, vector<vector<pair<int,int>>> adj_list);
vector<pair<int,int>> Hierholzer(vector<vector<int>> adj_list);
vector<vector<int>> TarjanSCC(vector<vector<int>> adj_list);
