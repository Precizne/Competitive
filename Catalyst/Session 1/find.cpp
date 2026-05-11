#include <bits/stdc++.h>

using namespace std;

int main () {
  int a[8] = {3, 2, 5, 1, 7, 5, 5, 7};
  find(a, a + 8, 9) != (a + 8) ? cout << "Element Found!" << endl : cout << "Element Not Found!" << endl;
}