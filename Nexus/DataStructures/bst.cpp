#include <iostream>

using namespace std;

class Node {
public:
   int data;
   Node* parent;
   Node* left;
   Node* right;

   Node(int data = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) {
      this->data = data;
      this->parent = parent;
      this->left = left;
      this->right = right;
   }
};

class BST {
public:
   Node* root;

   BST(Node* root = nullptr) {
      this->root = root;
   }

   void insertNode(int data) {
      Node* p = new Node(data);
      if(p == nullptr) {
         return;
      }
      Node* q = root;
      Node* r = nullptr;
      while(q != nullptr) {
         r = q;
         if(q->data < data) {
            q = q->right;
         }
         else {
            q = q->left;
         }
      }
      p->parent = r;
      if(r == nullptr) {
         root = p;
      }
      else if(r->data < data) {
         r->right = p;
      }
      else {
         r->left = p;
      }
   }

   void deleteNode(int data) {
      Node* p = search(data);
      if(p == nullptr) {
         return;
      }
      if(p->left == nullptr) {
         transplant(p, p->right);
      }
      else if(p->right == nullptr) {
         transplant(p, p->left);
      }
      else {
         Node* q = predecessor(p);
         if(q != p->left) {
            transplant(q, q->left);
            q->left = p->left;
            q->left->parent = q;
         }
         transplant(p, q);
         q->right = p->right;
         q->right->parent = q;
      }
   }

   void transplant(Node* p, Node* q) {
      if(p == nullptr) {
         return;
      }
      if(p->parent == nullptr) {
         root = q;
      }
      else if(p == p->parent->left) {
         p->parent->left = q;
      }
      else {
         p->parent->right = q;
      }
      if(q != nullptr) {
         q->parent = p->parent;
      }
   }

   Node* predecessor() {
      return predecessor(root);
   }

   Node* predecessor(Node* p) {
      if(p == nullptr) {
         return p;
      }
      if(p->left != nullptr) {
         return maximum(p->left);
      }
      Node* q = p->parent;
      while(q != nullptr && p != q->right) {
         p = q;
         q = q->parent;
      }
      return q;
   }

   Node* successor() {
      return successor(root);
   }

   Node* successor(Node* p) {
      if(p == nullptr) {
         return p;
      }
      if(p->right != nullptr) {
         return minimum(p->right);
      }
      Node* q = p->parent;
      while(q != nullptr && p != q->left) {
         p = q;
         q = q->parent;
      }
      return q;
   }

   Node* minimum() {
      return minimum(root);
   }

   Node* minimum(Node* p) {
      if(p == nullptr) {
         return p;
      }
      if(p->left == nullptr) {
         return p;
      }
      return minimum(p->left);
   }

   Node* maximum() {
      return maximum(root);
   }

   Node* maximum(Node* p) {
      if(p == nullptr) {
         return p;
      }
      if(p->right == nullptr) {
         return p;
      }
      return maximum(p->right);
   }


   Node* search(int data) {
      return search(root, data);
   }

   Node* search(Node* p, int data) {
      if(p == nullptr) {
         return p;
      }
      if(p->data == data) {
         return p;
      }
      if(p->data < data) {
         return search(p->right, data);
      }
      return search(p->left, data);
   }

   void inOrder() {
      inOrder(root);
   }

   void inOrder(Node* p) {
      if(p == nullptr) {
         return;
      }
      inOrder(p->left);
      cout << p->data << " ";
      inOrder(p->right);
   }

   void preOrder() {
      preOrder(root);
   }

   void preOrder(Node* p) {
      if(p == nullptr) {
         return;
      }
      cout << p->data << " ";
      preOrder(p->left);
      preOrder(p->right);
   }

   void postOrder() {
      postOrder(root);
   }

   void postOrder(Node* p) {
      if(p == nullptr) {
         return;
      }
      postOrder(p->left);
      postOrder(p->right);
      cout << p->data << " ";
   }
};

int main() {
   BST bst;
   bst.insertNode(5);
   bst.insertNode(8);
   bst.insertNode(1);
   bst.insertNode(3);
   bst.insertNode(7);
   bst.insertNode(2);
   bst.insertNode(6);
   bst.insertNode(4);
   bst.inOrder();
   cout << endl;
   bst.preOrder();
   cout << endl;
   bst.postOrder();
   cout << endl;
   cout << bst.predecessor(bst.search(6))->data << endl;
   cout << bst.successor(bst.search(6))->data << endl;
   bst.deleteNode(5);
   bst.inOrder();
   cout << endl;
   bst.preOrder();
   cout << endl;
   bst.postOrder();
   cout << endl;
   cout << bst.predecessor(bst.search(6))->data << endl;
   cout << bst.successor(bst.search(6))->data << endl;

   return 0;
}
