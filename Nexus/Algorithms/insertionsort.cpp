#include <iostream>

using namespace std;

void swapIt(int* p, int* q) {
   int tmp = *p;
   *p = *q;
   *q = tmp;
}

void insertionSort(int* p, int* q) {
   for(int* i = p; i < q; i++) {
      int* idx = i;
      while(idx > p && *(idx - 1) > *idx) {
         swapIt(idx, idx - 1);
         idx--;
      }
   }
}

int main() {
   int n;
   cin >> n;
   int a[n];
   for(int i = 0; i < n; i++) {
      cin >> a[i];
   }
   insertionSort(a, a + n);
   for(int i = 0; i < n; i++) {
      cout << a[i] << " ";
   }
   cout << endl;

   return 0;
}
