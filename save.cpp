#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
 
#define Precizne cin.tie(nullptr) -> sync_with_stdio(false);
#define int long long
#define uint unsigned int
#define INF(t) numeric_limits<t>::max()
#define endl "\n"
 
using namespace std;

class Graph {
public:
   int vtx;
   vector<vector<int>> adj;
   vector<bool> vst;
   vector<int> dp1;
   vector<bool> dp2;

   Graph(int n) {
      vtx = n;
      adj.assign(n, vector<int>());
      vst.assign(n, 0ll);
      dp1.assign(n, false);
   }

   void add(int u, int v) {
      adj[u].push_back(v);
      adj[v].push_back(u);
   }

   bool dfs1(int u, bool f) {
      vst[u] = true;
      bool p = false, q = true;
      for(auto v : adj[u]) {
         if(!vst[v]) {
            bool x = dfs1(v, !f);
            p |= x;
            q &= x;
            dp1[u] += x;
         }
      }
      return (f && p) || (!f && q);
   }

   void dfs2(int u) {
      vst[u] = true;
      dp2[u];
   }

   void reset() {
      vst.assign(vtx, false);
   }

   void trace() {
      for(int u = 0; u < vtx; u++) {
         cerr << u << " : ";
         for(auto v : adj[u]) {
            cerr << v << " ";
         }
         cerr << endl;
      }
   }
};

void zero() {
   int n, q;
   cin >> n >> q;
   Graph g(n);
   for(int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      g.add(u - 1, v - 1);
   }
   g.dfs1(0, true);
   g.reset();
   g.dfs2(0);
   while(q--) {
      int x;
      cin >> x;
      cout << (g.dp2[x - 1] ? "Ron" : "Hermione") << endl;
   }
}

signed main() {
   Precizne
   
   #ifndef ONLINE_JUDGE
      auto begin = chrono::high_resolution_clock::now();
      freopen("input.txt", "r", stdin); 
      freopen("output.txt", "w", stdout);
      freopen("error.txt", "w", stderr);
   #endif
   
   int progress = 1;
   // cin >> progress;
   for(int p = 1; p <= progress; p++) {
      // cout << "Case #" << p << ": " << endl;
      #ifndef ONLINE_JUDGE
         cerr << "Case #" << p << ": " << endl;
      #endif
      zero();
   }
 
   #ifndef ONLINE_JUDGE
      auto end = chrono::high_resolution_clock::now();
      auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
      cerr << fixed << "Time: " << elapsed.count() * 1e-9 << " secs" << endl;
   #endif
 
   return 0;
}
