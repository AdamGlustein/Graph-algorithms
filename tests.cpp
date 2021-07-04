
/**
 * May 31, 2021
 * Tests for graph algorithms
 * Use the graphs presented in the PowerPoint
 * */

#include "tests.h"

// Basic tests
void testDFS(vector<vector<vector<int>>>& graphs) {
    cout << "Starting DFS tests..." << endl;

    if (dfs(graphs[0], 0, 4)) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;
    
    if (dfs(graphs[0], 0, 7)) cout << "FAILED" << endl;
    else cout << "PASSED" << endl;

    if (dfs(graphs[1], 0, 1)) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (dfs(graphs[2], 0, 6)) cout << "FAILED" << endl;
    else cout << "PASSED" << endl;

    if (dfs(graphs[2], 6, 7)) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (dfs(graphs[2], 2, 4)) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    cout << "Done DFS testing!" << endl << endl;
}

void testBFS(vector<vector<vector<int>>>& graphs) {
    cout << "Starting BFS tests..." << endl;

    if (bfs(graphs[0], 0, 4) == 3) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;
    
    if (bfs(graphs[0], 0, 7) == -1) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (bfs(graphs[1], 0, 1) == 2) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (bfs(graphs[2], 0, 6) == -1) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (bfs(graphs[2], 6, 7) == 1) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (bfs(graphs[2], 2, 4) == 2) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    cout << "Done BFS testing!" << endl << endl;
}

void testDjikstra(vector<vector<vector<pii>>>& graphs) {
    cout << "Starting Djikstra tests..." << endl;

    if (djikstra(graphs[0], 0, 4) == 8) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;
    
    if (djikstra(graphs[0], 0, 7) == 15) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (djikstra(graphs[0], 1, 2) == 3) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (djikstra(graphs[1], 0, 3) == 4) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (djikstra(graphs[1], 0, 7) == 13) cout << "PASSED" << endl;
    else cout << djikstra(graphs[1], 0, 7) << endl;

    if (djikstra(graphs[1], 1, 7) == 12) cout << "PASSED" << endl;
    else cout << djikstra(graphs[1], 1, 7) << endl;

    cout << "Done Djikstra testing!" << endl << endl;
}

void testCycle(vector<vector<vector<int>>>& graphs) {
    cout << "Starting Cycle tests..." << endl;

    if (cycleDetect(graphs[0]) == true) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;
    
    if (cycleDetect(graphs[1]) == true) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (cycleDetect(graphs[2]) == true) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (cycleDetect(graphs[3]) == false) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (cycleDetect(graphs[4]) == true) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (cycleDetect(graphs[5]) == true) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    cout << "Done Cycle testing!" << endl << endl;
}

void testTopSort(vector<vector<vector<int>>>& graphs) {
    cout << "Starting TopSort tests..." << endl;

    vector<int> v1 = {0,6,1,2,3,5,4};
    vector<int> v2 = {0,6,1,2,4,3,5};
    vector<int> v3 = {0,6,1,2,3,4,5};
    vector<int> empty = {};
    if (topologicalSort(graphs[0]) ==  v1 || 
        topologicalSort(graphs[0]) ==  v2 ||
        topologicalSort(graphs[0]) == v3) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (topologicalSort(graphs[1]) == empty) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (topologicalSort(graphs[2]) == empty) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    cout << "Done TopSort testing!" << endl << endl;
}


// MST tests
void testPrim(vector<vector<vector<pii>>>& graphs) {
    cout << "Starting Prim tests..." << endl;

    if (prim(graphs[0]) == 31) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;
    
    if (prim(graphs[1]) == 17) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    // Prim does not work on a directed graph

    cout << "Done Prim testing!" << endl << endl;
}

// Advanced pathfinding tests
void testBeFo(vector<vector<vector<pii>>>& graphs) {
    cout << "Starting Bellman Ford tests..." << endl;
    
    if (bellmanFord(graphs[0], 0, 5) == 13) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;
    
    if (bellmanFord(graphs[1], 0, 3) == 2) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (bellmanFord(graphs[1], 4, 1) == INT32_MAX) cout << "PASSED" << endl;
    else cout << bellmanFord(graphs[1], 4, 1) << endl;

    if (bellmanFord(graphs[1], 0, 4) == 13) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (bellmanFord(graphs[2], 1, 2) == INT32_MIN) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    if (bellmanFord(graphs[2], 0, 4) == INT32_MIN) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    cout << "Done Bellman Ford testing!" << endl << endl;
}

void testHierholzer(vector<vector<vector<int>>>& graphs) {
    cout << "Starting Hierholzer tests..." << endl;
    
    vector<int> ans = hierholzerEulerian(graphs[0]);
    if (ans.size() == 0) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;
    
    ans = hierholzerEulerian(graphs[1]);
    if (ans.size() == 0) cout << "PASSED" << endl;
    else cout << "FAILED" << endl;

    ans = hierholzerEulerian(graphs[2]);
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    cout << endl;

    cout << "Done Hierholzer testing!" << endl << endl;
}

void testFlWa(vector<vector<vector<pii>>>& graphs) {
    cout << "Starting Floyd Warshall tests..." << endl;

    auto ans = floydWarshall(graphs[0]);
    for (int i = 0; i < graphs[0].size(); i++) {
        for (int j = 0; j < graphs[0].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
    ans = floydWarshall(graphs[1]);
    for (int i = 0; i < graphs[1].size(); i++) {
        for (int j = 0; j < graphs[1].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
    ans = floydWarshall(graphs[2]);
    for (int i = 0; i < graphs[2].size(); i++) {
        for (int j = 0; j < graphs[2].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Done Floyd Warshall tests!" << endl << endl;
}