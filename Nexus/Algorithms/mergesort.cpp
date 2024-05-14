#include <iostream>

using namespace std;

void merge(int* a, int p, int q, int r) {
   int n = q - p + 1;
   int m = r - q;
   int f[n];
   int g[m];
   for(int i = 0; i < n; i++) {
      f[i] = a[p + i];
   }
   for(int i = 0; i < m; i++) {
      g[i] = a[q + 1 + i];
   }
   int i = 0;
   int j = 0;
   int k = p;
   while(i < n && j < m) {
      if(f[i] <= g[j]) {
         a[k] = f[i];
         i++;
      }
      else {
         a[k] = g[j];
         j++;
      }
      k++;
   }
   while(i < n) {
      a[k] = f[i];
      i++;
      k++;
   }
   while(j < m) {
      a[k] = g[j];
      j++;
      k++;
   }
}

void mergeSort(int* a, int p, int r) {
   if(p >= r) {
      return;
   }
   int q = (p + r) / 2;
   mergeSort(a, p, q);
   mergeSort(a, q + 1, r);
   merge(a, p, q, r);
}

int main() {
   int n;
   cin >> n;
   int a[n];
   for(int i = 0; i < n; i++) {
      cin >> a[i];
   }
   mergeSort(a, 0, n - 1);
   for(int i = 0; i < n; i++) {
      cout << a[i] << " ";
   }
   cout << endl;

   return 0;
}
