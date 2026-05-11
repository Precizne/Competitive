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
   vector<vector<pair<int, int>>> adj;
   vector<bool> vst;
   vector<int> spt;

   Graph(int n) {
      vtx = n;
      adj.assign(n, vector<pair<int, int>>());
      vst.assign(n, false);
      spt.assign(n, 0ll);
   }

   void add(int u, int v, int w) {
      adj[u].push_back({v, w});
   }

   void reset() {
      vst.assign(vtx, false);
      spt.assign(vtx, 0ll);
   }

   void dijkstra(int s) {
      priority_queue<pair<int, int>> pq;
      pq.push({0, s});
      while(pq.size()) {
         auto [d, u] = pq.top();
         pq.pop();
         spt[u] = max(spt[u], d);
         if(!vst[u]) {
            for(auto [v, w] : adj[u]) {
               pq.push({d + w, v});
            }
         }
         vst[u] = true;
      }
   }
};

void zero() {
   int n;
   cin >> n;
   vector<int> a(n);
   for(auto& i : a) {
      cin >> i;
   }
   Graph g(n);
   for(int i = 0; i < n - 1; i++) {
      g.add(i + 1, i, a[i + 1]);
   }
   for(int i = 0; i < n; i++) {
      int x;
      cin >> x;
      g.add(i, x - 1, 0ll);
   }
   g.dijkstra(0);
   cout << max(a[0], *max_element(g.spt.begin(), g.spt.end())) << endl;
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
   cin >> progress;
   for(int p = 1; p <= progress; p++) {
      // cout << "Case #" << p << ": ";
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
