#include <bits/stdc++.h>

using namespace std;

class SegmentTree {
public:
   int n;
   vector<int> tree;

   SegmentTree(vector<int> arr) {
      n = arr.size();
      tree.resize(2 * n);
      build(arr);
   }

   void build(vector<int> arr) {
      for(int i = 0; i < n; i++) {
         tree[n + i] = arr[i];
      }
      for(int i = n - 1; i > 0; i--) {
         tree[i] = tree[i * 2] + tree[i * 2 + 1];
      }
   }

   void update(int index, int value) {
      index += n;
      tree[index] = value;
      while(index > 1) {
         index /= 2;
         tree[index] = tree[index * 2] + tree[index * 2 + 1];
      }
   }

   int query(int left, int right) {
      left += n;
      right += n;
      int result = 0;
      while(left <= right) {
         if(left % 2 == 1) {
            result += tree[left];
            left++;
         }
         if(right % 2 == 0) {
            result += tree[right];
            right--;
         }
         left /= 2;
         right /= 2;
      }
      return result;
   }
};
