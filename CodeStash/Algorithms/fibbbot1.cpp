#include <iostream>

using namespace std;

int fibbbot1(int a) {
  int b[a];

  b[0] = 0;
  b[1] = 1;

  for(int i = 2; i < a; i++) {
    b[i] = b[i - 1] + b[i - 2];
  }

  return b[a - 1];
}

int main() {
  int x = 10;

  cout<<fibbbot1(x)<<endl;

  return 0;
}