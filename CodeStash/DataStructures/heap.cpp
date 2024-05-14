#include <iostream>

using namespace std;

class Heap {
  public:
    int* root;
    int apex;
    int capacity;
    
    Heap() {
      this->root = new int[32];
      this->apex = 0;
      this->capacity = 32;
    }
    
    Heap(int capacity) {
      this->root = new int[capacity];
      this->apex = 0;
      this->capacity = capacity;
    }
    
    void insertNode(int n) {
      if(isFull()) {
        cout << "Heap Buffer Overflow!" << endl;
        return;
      }
      int tmp = apex;
      root[apex] = n;
      apex++;
      while(tmp > 0) {
        if(root[tmp] > root[parent(tmp)]) {
          swap(root[tmp], root[parent(tmp)]);
        }
        else {
          break;
        }
        tmp = parent(tmp);
      }
    }
    
    void heapify() {
      heapify(0);
    }
    void heapify(int n) {
      int l = left(n);
      int r = right(n);
      int max = (l < apex && root[l] > root[n]) ? ((r < apex && root[r] > root[l]) ? r : l) : ((r < apex && root[r] > root[n]) ? r : n);
      if(max != n) {
        swap(root[max], root[n]);
        heapify(max);
      }
    }
    
    void buildHeap() {
      for(int i = (apex - 1) / 2; i >= 0; i--) {
        heapify(i);
      }
    }
    
    void heapSort() {
      buildHeap();
      int tmp = apex;
      for(int i = (apex - 1); i >= 1; i--) {
        swap(root[0], root[i]);
        apex--;
        heapify();
      }
      apex = tmp;
    }
    
    int parent(int n) {
      return (n - 1) / 2;
    }
    
    int left(int n) {
      return 2 * n + 1;
    }
    
    int right(int n) {
      return 2 * n + 2;
    }
    
    bool isFull() {
      if(apex >= capacity) {
        return true;
      }
      return false;
    }
    
    bool isEmpty() {
      if(apex == 0) {
        return true;
      }
      return false;
    }
    
    void swap(int& p, int& q) {
      int tmp = p;
      p = q;
      q = tmp;
    }
    
    void print() {
      for(int i = 0; i < apex; i++) {
        cout << root[i] << " ";
      }
      cout << endl;
    }
};

int main() {
  int n;
  cin >> n;
  Heap hp;
  for(int i = 0; i < n; i++) {
    int x;
    cin >> x;
    hp.insertNode(x);
  }
  hp.heapSort();
  hp.print();

  return 0;
}