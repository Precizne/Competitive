#include <bits/stdc++.h>

using namespace std;

int main () {
  int a[8] = {7, 7, 7, 7, 7, 2, 4, 0};
  vector<int> v({5, 7, 3, 2, 6});
  for(auto i : v) {
    cout << i << " ";
  }
  cout << endl;
  v.assign(a, a + 8);
  for(auto i : v) {
    cout << i << " ";
  }
  cout << endl;
  auto x = unique(v.begin(), v.end());
  for(auto i : v) {
    cout << i << " ";
  }
  cout << endl;
  v.erase(x, v.end());
  for(auto i : v) {
    cout << i << " ";
  }
  cout << endl;
  vector<int> w;
  w.assign(v.begin(), x);
  for(auto i : w) {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}