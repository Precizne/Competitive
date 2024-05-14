#include <iostream>

using namespace std;

int main() {
  int x,y;
  cin>>x>>y;

  x += 2 * (y - x);
  y -= (x - y);
  x -= (x - y) / 2;

  cout<<x<<endl<<y<<endl;

  return 0;
}
