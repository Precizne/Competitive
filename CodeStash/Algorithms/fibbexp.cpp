#include <iostream>

using namespace std;

int fibbexp(int a) {
  if(a == 1) {
    return 0;
  }
  if(a == 2) {
    return 1;
  }

  return fibbexp(a - 1) + fibbexp(a - 2);
}

int main() {
  int x = 10;

  cout<<fibbexp(x)<<endl;

  return 0;
}