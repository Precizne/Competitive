#include <iostream>

using namespace std;

class Node {
public:
   int data;
   Node* parent;
   Node* left;
   Node* right;
   bool color;

   Node(int data = 0, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, bool color = false) {
      this->data = data;
      this->parent = parent;
      this->left = left;
      this->right = right;
      this->color = color;
   }
};

class RBT {
public:
   Node* root;
   Node* apex;

   RBT(Node* root = nullptr, Node* apex = nullptr) {
      if(apex == nullptr) {
         apex = new Node(0, apex, apex, apex, false);
      }
      if(root == nullptr) {
         root = apex;
      }
      this->root = root;
      this->apex = apex;
   }

   void insertNode(int data) {
      Node* p = new Node(data, apex, apex, apex, true);
      if(p == apex) {
         return;
      }
      Node* fix = p;
      Node* q = root;
      Node* r = apex;
      while(q != apex) {
         r = q;
         if(q->data < data) {
            q = q->right;
         }
         else {
            q = q->left;
         }
      }
      p->parent = r;
      if(r == apex) {
         root = p;
      }
      else if(r->data < data) {
         r->right = p;
      }
      else {
         r->left = p;
      }
      insertFix(fix);
   }

   void insertFix(Node* p) {
      if(p == apex) {
         return;
      }
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

   void deleteNode(int data) {
      Node* p = search(data);
      if(p == apex) {
         return;
      }
      bool color;
      Node* fix;
      if(p->left == apex) {
         color = p->color;
         fix = p->right;
         transplant(p, p->right);
      }
      else if(p->right == apex) {
         color = p->color;
         fix = p->left;
         transplant(p, p->left);
      }
      else {
         Node* q = predecessor(p);
         color = q->color;
         fix = q->left;
         if(q != p->left) {
            transplant(q, q->left);
            q->left = p->left;
            q->left->parent = q;
         }
         else {
            fix->parent = q;
         }
         transplant(p, q);
         q->right = p->right;
         q->right->parent = q;
         q->color = p->color;
      }
      if(!color) {
         deleteFix(fix);
      }
      apex->parent = apex;
   }

   void deleteFix(Node* p) {
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

   void transplant(Node* p, Node* q) {
      if(p == apex) {
         return;
      }
      if(p->parent == apex) {
         root = q;
      }
      else if(p == p->parent->left) {
         p->parent->left = q;
      }
      else {
         p->parent->right = q;
      }
      q->parent = p->parent;
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
      else if(p == p->parent->left) {
         p->parent->left = q;
      }
      else {
         p->parent->right = q;
      }
      q->right = p;
      p->parent = q;
   }

   Node* predecessor() {
      return predecessor(root);
   }

   Node* predecessor(Node* p) {
      if(p == apex) {
         return p;
      }
      if(p->left != apex) {
         return maximum(p->left);
      }
      Node* q = p->parent;
      while(q != apex && p != q->right) {
         p = q;
         q = q->parent;
      }
      return q;
   }

   Node* successor() {
      return successor(root);
   }

   Node* successor(Node* p) {
      if(p == apex) {
         return p;
      }
      if(p->right != apex) {
         return minimum(p->right);
      }
      Node* q = p->parent;
      while(q != apex && p != q->left) {
         p = q;
         q = q->parent;
      }
      return q;
   }

   Node* minimum() {
      return minimum(root);
   }

   Node* minimum(Node* p) {
      if(p == apex) {
         return p;
      }
      if(p->left == apex) {
         return p;
      }
      return minimum(p->left);
   }

   Node* maximum() {
      return maximum(root);
   }

   Node* maximum(Node* p) {
      if(p == apex) {
         return p;
      }
      if(p->right == apex) {
         return p;
      }
      return maximum(p->right);
   }

   int colorCount(bool color) {
      return colorCount(root, color);
   }

   int colorCount(Node* p, bool color) {
      if(p == apex) {
         return 0;
      }
      int count = colorCount(p->left, color) + colorCount(p->right, color);
      return (!(color ^ p->color)) ? 1 + count : 0 + count;
   }

   Node* search(int data) {
      return search(root, data);
   }

   Node* search(Node* p, int data) {
      if(p == apex) {
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
      if(p == apex) {
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
      if(p == apex) {
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
      if(p == apex) {
         return;
      }
      postOrder(p->left);
      postOrder(p->right);
      cout << p->data << " ";
   }
};

int main() {
   RBT rbt;
   rbt.insertNode(5);
   rbt.insertNode(8);
   rbt.insertNode(1);
   rbt.insertNode(3);
   rbt.insertNode(7);
   rbt.insertNode(2);
   rbt.insertNode(6);
   rbt.insertNode(4);
   rbt.inOrder();
   cout << endl;
   rbt.preOrder();
   cout << endl;
   rbt.postOrder();
   cout << endl;
   cout << rbt.predecessor(rbt.search(6))->data << endl;
   cout << rbt.successor(rbt.search(6))->data << endl;
   cout << rbt.colorCount(false) << endl;
   cout << rbt.colorCount(true) << endl;
   rbt.deleteNode(5);
   rbt.inOrder();
   cout << endl;
   rbt.preOrder();
   cout << endl;
   rbt.postOrder();
   cout << endl;
   cout << rbt.predecessor(rbt.search(6))->data << endl;
   cout << rbt.successor(rbt.search(6))->data << endl;
   cout << rbt.colorCount(false) << endl;
   cout << rbt.colorCount(true) << endl;
   return 0;
}
