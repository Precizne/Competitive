#include <bits/stdc++.h>
 
using namespace std;

class BitGraph {
public:
   int vtx;
   vector<int> adj;

   BitGraph(int n) {
      vtx = n;
      adj.assign(n, 0);
   }

   void add(int u, int v) {
      adj[u] |= (1ll << v);
      adj[v] |= (1ll << u);
   }

   int longestHamPath() {
      int smask = (1ll << vtx) - 1;
      vector<int> dp(smask + 1);
      for(int mask = 0; mask <= smask; mask++) {
         for(int i = 0; i < vtx; i++) {
            if(popcount((uint)mask) == 1 && (mask & (1ll << i))) {
               dp[mask] |= mask;
            }
            else if(popcount((uint)mask) > 1) {
               dp[mask] |= (1ll << i) * ((dp[mask ^ (1ll << i)] & adj[i]) != 0);
            }
         }
      }
      int p = 0;
      for(int mask = 0; mask <= smask; mask++) {
         if(dp[mask]) {
            p = max(p, (int)popcount((uint)mask));
         }
      }
      return p;
   }

   void trace() {
      for(int u = 0; u < vtx; u++) {
         cerr << adj[u] << endl;
      }
   }
};
