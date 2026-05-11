#include <bits/stdc++.h>

using namespace std;

int main () {
  vector<int> v;
  if(v.empty()) {
    cout << "Empty" << endl;
  }
  else {
    cout << "Not Empty" << endl;
  }
  v.push_back(5);
  v.push_back(3);
  v.push_back(8);
  v.push_back(0);
  if(v.empty()) {
    cout << "Empty" << endl;
  }
  else {
    cout << "Not Empty" << endl;
  }
  cout << v.front() << endl;
  cout << v.back() << endl;
  v.insert(v.begin() + 3, 4, 100);
  for(auto i : v) {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}