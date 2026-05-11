#include <iostream>

using namespace std;

int split(int* p, int* q, int k) {
   if(k == 0) {
      return 0;
   }
   int max = -1;
   for(int i = 1; i <= k; i++) {
      int cur = p[i - 1] + split(p, q, k - i);
      max = (cur > max) ? cur : max;
   }
   return max;
}

int main() {
   int n, k;
   cin >> n >> k;
   int a[n];
   for(int i = 0; i < n; i++) {
      cin >> a[i];
   }
   cout << split(a, a + n, k) << endl;

   return 0;
}
