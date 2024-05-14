#include <iostream>

using namespace std;

int splitTopDown(int* p, int* q, int k, int* r, int* s) {
   if(r[k] >= 0) {
      return r[k];
   }
   int max = -1;
   if(k == 0) {
      max = 0;
   }
   else {
      for(int i = 1; i <= k; i++) {
         int cur = p[i - 1] + splitTopDown(p, q, k - i, r, s);
         max = (cur > max) ? cur : max;
      }
   }
   r[k] = max;
   return max;
}

int splitTopDown(int* p, int* q, int k) {
   int a[k + 1];
   for(int i = 0; i <= k; i++) {
      a[i] = -1;
   }
   return splitTopDown(p, q, k, a, a + k);
}

int splitBottomUp(int* p, int* q, int k) {
   int a[k + 1];
   a[0] = 0;
   for(int i = 1; i <= k; i++) {
      a[i] = -1;
      int max = -1;
      for(int j = 1; j <= i; j++) {
         int cur = p[j - 1] + a[i - j];
         max = (cur > max) ? cur : max;
      }
      a[i] = max;
   }
   return a[k];
}

int main() {
   int n, k;
   cin >> n >> k;
   int a[n];
   for(int i = 0; i < n; i++) {
      cin >> a[i];
   }
   cout << splitTopDown(a, a + n, k) << endl;
   cout << splitBottomUp(a, a + n, k) << endl;

   return 0;
}
