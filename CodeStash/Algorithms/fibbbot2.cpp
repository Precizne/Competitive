#include <iostream>

using namespace std;

int fibbbot2(int a) {
  int p = 1;
  int q = 0;
  int r;

  if(a == 1) {
    return q;
  }
  if(a == 2) {
    return p;
  }

  for(int i = 2; i < a; i++) {
    r = p + q;
    q = p;
    p = r;
  }

  return r;
}

int main() {
  int x = 10;

  cout<<fibbbot2(x)<<endl;

  return 0;
}