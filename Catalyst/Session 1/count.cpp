#include <bits/stdc++.h>

using namespace std;

int main () {
  int a[8] = {3, 2, 5, 1, 7, 5, 5, 7};
  int x = count(a, a + 8, 5);
  cout << x << endl;
  return 0;
}