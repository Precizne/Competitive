#include <iostream>

using namespace std;

class Node {
public:
  int data;
  Node *parent;
  Node *left;
  Node *right;

  Node() {
    this->data = 0;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
  }

  Node(int data) {
    this->data = data;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
  }
};

class Queue {
public:
  Node *a[32];
  int f;
  int b;

  Queue() {
    f = 0;
    b = 0;
  }

  void push(Node *p) {
    if (full()) {
      cout << "Queue Overflow" << endl;
      return;
    }
    a[b] = p;
    b = (b + 1) % 32;
  }

  void pop() {
    if (empty()) {
      cout << "Queue Underflow" << endl;
      return;
    }
    f = (f + 1) % 32;
  }

  Node *front() { return a[f]; }

  Node *back() { return a[(b - 1 + 32) % 32]; }

  bool full() {
    if ((b + 1) % 32 == f) {
      return true;
    }
    return false;
  }

  bool empty() {
    if (b == f) {
      return true;
    }
    return false;
  }
};




  void levelOrder() {
    if (root == nullptr) {
      return;
    }
    Queue q;
    q.push(root);
    while (!q.empty()) {
      cout << q.front()->data << " ";
      if (q.front()->left != nullptr) {
        q.push(q.front()->left);
      }
      if (q.front()->right != nullptr) {
        q.push(q.front()->right);
      }
      q.pop();
    }
  }
};
