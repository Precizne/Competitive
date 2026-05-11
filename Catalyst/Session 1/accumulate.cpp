#include <bits/stdc++.h>

using namespace std;

int main () {
  int a[5] = {3, 2, 5, 1, 7};
  int x = accumulate(a, a + 5, 3);
  cout << x << endl;
  return 0;
}