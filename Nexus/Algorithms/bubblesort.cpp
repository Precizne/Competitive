#include <iostream>

using namespace std;

void swapIt(int* p, int* q) {
   int tmp = *p;
   *p = *q;
   *q = tmp;
}

void bubbleSort(int* p, int* q) {
   while(true) {
      bool tag = false;
      for(int* i = p; i < q - 1; i++) {
         if(*i > *(i + 1)) {
            swapIt(i, i + 1);
            tag = true;
         }
      }
      if(!tag) {
         break;
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
   bubbleSort(a, a + n);
   for(int i = 0; i < n; i++) {
      cout << a[i] << " ";
   }
   cout << endl;

   return 0;
}
