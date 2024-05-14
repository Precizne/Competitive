#include <iostream>

using namespace std;

void swapIt(int* p, int* q) {
   int tmp = *p;
   *p = *q;
   *q = tmp;
}

int* partition(int* p, int* q) {
   int* pivot = q - 1;
   int* insert = p - 1;
   for(int* i = p; i < pivot; i++) {
      if(*i <= *pivot) {
         insert++;
         swapIt(insert, i);
      }
   }
   swapIt(insert + 1, pivot);
   return insert + 1; 
}

void quicksort(int* p, int* q) {
   if(p < q) {
      int n = q - p;
      int* pivot = partition(p, q);
      quicksort(p, pivot);
      quicksort(pivot + 1, q);
   }
}

int main() {
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  quicksort(a, a + n);
  for(int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;

  return 0;
}
