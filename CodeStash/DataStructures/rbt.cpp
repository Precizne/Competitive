#include <iostream>

using namespace std;

class Node {
public:
  int data;
  Node* parent;
  Node* left;
  Node* right;
  bool color;
  
  Node(int data = 0, Node* p = nullptr, bool color = false) {
    this->data = data;
    this->parent = p;
    this->left = p;
    this->right = p;
    this->color = color;
  }
};

class RedBlackTree {
public:
  Node* root;
  Node* apex;
  
  RedBlackTree() {
    apex = new Node(0, apex, false);
    root = apex;
  }

  void leftRotate(Node* p) {
    Node* q = p->right;
    p->right = q->left;
    if(q->left != apex) {
      q->left->parent = p;
    }
    q->parent = p->parent;
    if(p->parent == apex) {
      root = q;
    }
    else if(p == p->parent->left) {
      p->parent->left = q;
    }
    else {
      p->parent->right = q;
    }
    q->left = p;
    p->parent = q;
  }

  void rightRotate(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    if(q->right != apex) {
      q->right->parent = p;
    }
    q->parent = p->parent;
    if(p->parent == apex) {
      root = q;
    }
    else if (p == p->parent->left) {
      p->parent->left = q;
    }
    else {
      p->parent->right = q;
    }
    q->right = p;
    p->parent = q;
  }

  void insertNode(int data) {
    Node* newNode = new Node(data, apex, true);
    Node* p = root;
    Node* q = apex;
    while(p != apex) {
      q = p;
      if(newNode->data < p->data) {
        p = p->left;
      }
      else {
        p = p->right;
      }
    }
    newNode->parent = q;
    if(q == apex) {
      root = newNode;
    }
    else if(newNode->data < q->data) {
      q->left = newNode;
    }
    else {
      q->right = newNode;
    }
    insertFixup(newNode);
  }

  void insertFixup(Node* p) {
    while(p->parent->color) {
      if(p->parent == p->parent->parent->left) {
        Node* q = p->parent->parent->right;
        if(q->color) {
          p->parent->color = false;
          q->color = false;
          p->parent->parent->color = true;
          p = p->parent->parent;
        }
        else {
          if(p == p->parent->right) {
            p = p->parent;
            leftRotate(p);
          }
          p->parent->color = false;
          p->parent->parent->color = true;
          rightRotate(p->parent->parent);
        }
      }
      else {
        Node* q = p->parent->parent->left;
        if(q->color) {
          p->parent->color = false;
          q->color = false;
          p->parent->parent->color = true;
          p = p->parent->parent;
        }
        else {
          if(p == p->parent->left) {
            p = p->parent;
            rightRotate(p);
          }
          p->parent->color = false;
          p->parent->parent->color = true;
          leftRotate(p->parent->parent);
        }
      }
    }
    root->color = false;
  }

  int redNumber() {
    return redNumber(root);
  }
  int redNumber(Node* p) {
    if(p == apex) {
      return 0;
    }
    int x = 0;
    if(p->color) {
      x = 1;
    }
    return x + redNumber(p->left) + redNumber(p->right);
  }
  int blackNumber() {
    return blackNumber(root);
  }
  int blackNumber(Node* p) {
    if(p == apex) {
      return 0;
    }
    int x = 0;
    if(!p->color) {
      x = 1;
    }
    return x + blackNumber(p->left) + blackNumber(p->right);
  }

  void deleteNode(Node* p) {
    Node* q = p;
    bool origin = q->color;
    Node* tmp;
    if(q->left == apex) {
      tmp = p->right;
      transplant(p, p->right);
    }
    else if(q->right == apex) {
      tmp = p->left;
      transplant(p, p->left);
    }
    else {
      q = minimum(p->right);
      origin = q->color;
      tmp = q->right;
      if(q != p->right) {
        transplant(q, q->right);
        q->right = p->right;
        q->right->parent = q;
      }
      else {
        p->parent = q;
        transplant(p, q);
        q->left = p->left;
        q->left->parent = q;
        q->color = p->color;
      }
    }
    if(!origin) {
      deleteFixup(tmp);
    }
  }

  void deleteFixup(Node* p) {
    while(p != root && !p->color) {
      if(p == p->parent->left) {
        Node* q = p->parent->right;
        if(q->color) {
          q->color = false;
          p->parent->color = true;
          leftRotate(p->parent);
          q = p->parent->right;
        }
        if(!q->left->color && !q->right->color) {
          q->color = true;
          p = p->parent;
        }
        else {
          if(!q->right->color) {
            q->left->color = false;
            q->color = true;
            rightRotate(q);
            q = p->parent->right;
          }
          q->color = p->parent->color;
          p->parent->color = false;
          q->right->color = false;
          leftRotate(p->parent);
          p = root;
        }
      }
      else {
        Node* q = p->parent->left;
        cout << "****" << q->color << endl;
        if(q->color) {
          q->color = false;
          p->parent->color = true;
          rightRotate(p->parent);
          q = p->parent->left;
        }
        if(!q->right->color && !q->left->color) {
          q->color = true;
          p = p->parent;
        }
        else {
          if(!q->left->color) {
            q->right->color = false;
            q->color = true;
            leftRotate(q);
            q = p->parent->left;
          }
          q->color = p->parent->color;
          p->parent->color = false;
          q->left->color = false;
          rightRotate(p->parent);
          p = root;
        }
      }
    }
    p->color = false;
  }

  Node *minimum(Node *p) {
    if (p == apex || p->left == apex) {
      return p;
    }
    return minimum(p->left);
  }

  void transplant(Node *p, Node *q) {
    if(p->parent == apex) {
      root = q;
    }
    else if(p == p->parent->left) {
      p->parent->left = q;
    }
    else {
      p->parent->right = q;
    }
    if(q != apex) {
      q->parent = p->parent;
    }
  }

  Node* search(int x) {
    return search(root, x);
  }
  Node* search(Node* p, int x) {
    if(p == apex || p->data == x) {
      return p;
    }
    if(x < p->data) {
      return search(p->left, x);
    }
    return search(p->right, x);
  }

  void inOrder() {
    inOrder(root);
  }
  void inOrder(Node* p) {
    if(p == apex) {
      return;
    }
    inOrder(p->left);
    cout << p->data << " ";
    inOrder(p->right);
  }
};

int main() {
  RedBlackTree rbt;
  int n;
  cin >> n;
  for(int i = 0; i < n; i++) {
    int x;
    cin >> x;
    rbt.insertNode(x);
  }
  cout << rbt.redNumber() << endl;
  cout << rbt.blackNumber() << endl;
  rbt.inOrder();
  cout << endl;
  int x;
  cin >> x;
  rbt.deleteNode(rbt.search(x));
  cout << rbt.redNumber() << endl;
  cout << rbt.blackNumber() << endl;
  rbt.inOrder();
  cout << endl;
  return 0;
}
