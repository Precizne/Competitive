#include <bits/stdc++.h>

using namespace std;

int main () {
  int a[5] = {3, 2, 5, 1, 7};
  sort(a, a + 5);
  for(int i = 0; i < 5; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  sort(a, a + 5, greater<int>());
  for(int i = 0; i < 5; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  return 0;
}