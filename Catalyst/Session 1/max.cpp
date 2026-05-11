#include <bits/stdc++.h>

using namespace std;

int main () {
  int a[5] = {3, 2, 5, 1, 7};
  int x = *max_element(a, a + 5);
  cout << x << endl;
  return 0;
}