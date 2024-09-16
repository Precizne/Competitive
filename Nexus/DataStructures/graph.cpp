#include <bits/stdc++.h>

using namespace std;

// Graph

class Graph {
public:
   int vtx;
   vector<vector<int>> adj;
   vector<bool> vst;

   Graph(int n) {
      vtx = n;
      adj.assign(n, vector<int>());
      vst.assign(n, false);
   }

   void add(int u, int v) {
      adj[u].push_back(v);
      adj[v].push_back(u);
   }

   void reset() {
      vst.assign(vtx, false);
   }
};
