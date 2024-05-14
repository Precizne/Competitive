#include <bits/stdc++.h>

using namespace std;

// Disjoint Set Union

class DSU {
public:
   int vtx;
   vector<int> prnt, rank, size;

   DSU(int n) {
      vtx = n;
      make(n);
   }

   void make(int n) {
      prnt.resize(n);
      rank.resize(n, 0);
      size.resize(n, 1);
      for(int i = 0; i < n; i++) {
         prnt[i] = i;
      }
   }

   int find(int u) {
      if(u == prnt[u]) {
         return u;
      }
      return prnt[u] = find(prnt[u]);
   }

   void unionRank(int u, int v) {
      u = find(u);
      v = find(v);
      if(u != v) {
         if(rank[u] > rank[v]) {
            swap(u, v);
         }
         prnt[u] = v;
         if(rank[u] == rank[v]) {
            rank[v]++;
         }
      }
   }

   void unionSize(int u, int v) {
      u = find(u);
      v = find(v);
      if(u != v) {
         if(size[u] > size[v]) {
            swap(u, v);
         }
         prnt[u] = v;
         size[v] += size[u];
      }
   }
};
