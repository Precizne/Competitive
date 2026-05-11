#include <iostream>

using namespace std;

void swapIt(int* p, int* q) {
   int tmp = *p;
   *p = *q;
   *q = tmp;
}

void selectionSort(int* p, int* q) {
   for(int* i = q - 1; i >= p; i--) {
      int* idx = i;
      for(int* j = p; j <= i; j++) {
         if(*j > *idx) {
            idx = j;
         }
      }
      swapIt(i, idx);
   }
}

int main() {
   int n;
   cin >> n;
   int a[n];
   for(int i = 0; i < n; i++) {
      cin >> a[i];
   }
   selectionSort(a, a + n);
   for(int i = 0; i < n; i++) {
      cout << a[i] << " ";
   }
   cout << endl;

   return 0;
}
