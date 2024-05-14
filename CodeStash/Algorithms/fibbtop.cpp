#include <iostream>
#include <unordered_map>

using namespace std;

int fibbtop(int a) {

  if(a == 1) {
    return 0;
  }
  if(a == 2) {
    return 1;
  }

  static unordered_map<int, int> umap;

  bool tag = false;
  for(auto x : umap) {
    if(x.first == a) {
      tag = true;
    }
  }

  if(!tag) {
    umap[a] = fibbtop(a - 1) + fibbtop(a - 2);
  }

  return umap[a];
}

int main() {
  int x = 10;

  cout<<fibbtop(x)<<endl;

  return 0;
}