#include <bits/stdc++.h>

using namespace std;

class DPTree {
public:
   map<pair<int, int>, int> seg;
   
   bool exist(int l, int r) {
      return seg.find({l, r}) != seg.end();
   }

   void add(int l, int r, int v) {
      seg[{l, r}] = v;
   }

   int get(int l, int r) {
      return seg[{l, r}];
   }

   void update(int l, int r, int p) {
      seg[{l, r}]--;
      if(l < r) {
         int m = l + (r - l) / 2;
         if(p <= m) {
            update(l, m, p);
         }
         else {
            update(m + 1, r, p);
         }
      }
   }
};
