
#pragma once
#include "graph.h"

// Basic tests
void testDFS(vector<vector<vector<int>>>& graphs);
void testBFS(vector<vector<vector<int>>>& graphs);
void testDjikstra(vector<vector<vector<pii>>>& graphs);
void testCycle(vector<vector<vector<int>>>& graphs);
void testTopSort(vector<vector<vector<int>>>& graphs);

// MST tests
void testPrim(vector<vector<vector<pii>>>& graphs);

// Advanced pathfinding tests
void testBeFo(vector<vector<vector<pii>>>& graphs);
void testHierholzer(vector<vector<vector<int>>>& graphs);
void testFlWa(vector<vector<vector<pii>>>& graphs);

// Tarjan tests
void testTarjanSCC(vector<vector<vector<int>>>& graphs);
void testTarjanAP(vector<vector<vector<int>>>& graphs);
void testTarjanBridge(vector<vector<vector<int>>>& graphs);

// Flow test
void testMaxFlow(vector<vector<vector<pii>>>& graphs);
void testMinCut(vector<vector<vector<pii>>>& graphs);
void testBipartite(vector<vector<vector<pii>>>& graphs);

// Advanced algorithm tests
void testHamiltonian(vector<vector<vector<int>>>& graphs);
void testKColors(vector<vector<vector<int>>>& graphs);
void testTSP(vector<vector<vector<pii>>>& graphs);
void testKCentres(vector<vector<vector<pii>>>& graphs);
