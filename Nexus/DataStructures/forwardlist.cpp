#include <iostream>

using namespace std;

class Node {
public:
  int data;
  Node* next;

  Node() {
    this->data = 0;
    this->next = nullptr;
  }

  Node(int data) {
    this->data = data;
    this->next = nullptr;
  }
};

class ForwardList {
public:
  Node* head;

  ForwardList() {
    head = nullptr;
  }

  void insertFront(int data) {
    Node* newnode = new Node(data);
    if(head == nullptr) {
      head = newnode;
      return;
    }
    newnode->next = head;
    head = newnode;
  }

  void insertBack(int data) {
    Node* newnode = new Node(data);
    if(head == nullptr) {
      head = newnode;
      return;
    }
    Node* tmp = head;
    while(tmp != nullptr && tmp->next != nullptr) {
      tmp = tmp->next;
    }
    tmp->next = newnode;
  }

  void insertAfter(Node* p, int data) {
    Node* newnode = new Node(data);
    if(head == nullptr) {
      head = newnode;
      return;
    }
    if(p == nullptr) {
      return;
    }
    newnode->next = p->next;
    p->next = newnode;
  }

  void deleteFront() {
    if(head == nullptr) {
      return;
    }
    Node* tmp = head;
    head = head->next;
    delete(tmp);
    tmp = nullptr;
  }

  void deleteBack() {
    if(head == nullptr) {
      return;
    }
    if(head->next == nullptr) {
      delete(head);
      head = nullptr;
      return;
    }
    Node* tmp1 = head;
    while(tmp1->next->next != nullptr) {
      tmp1 = tmp1->next;
    }
    delete(tmp1->next);
    tmp1->next = nullptr;
  }

  void deleteAfter(Node* p) {
    if(head == nullptr || p == nullptr || p->next == nullptr) {
      return;
    }
    Node* tmp = p->next;
    p->next = tmp->next;
    delete(tmp);
    tmp = nullptr;
  }

  Node* search(int data) {
    if(head == nullptr) {
      return head;
    }
    Node* tmp = head;
    while(tmp != nullptr) {
      if(data == tmp->data) {
        break;
      }
      tmp = tmp->next;
    }
    return tmp;
  }

  void print() {
    if(head == nullptr) {
      return;
    }
    Node* tmp = head;
    while(tmp != nullptr) {
      cout << tmp->data << " ";
      tmp = tmp->next;
    }
  }
  };

  int main() {
    ForwardList fl;
    fl.insertFront(5);
    fl.insertFront(7);
    fl.insertBack(9);
    fl.insertBack(3);
    fl.insertAfter(fl.search(5), 8);
    fl.insertAfter(fl.search(7), 6);
    fl.insertAfter(fl.search(9), 1);
    fl.insertAfter(fl.search(3), 0);
    fl.deleteFront();
    fl.deleteFront();
    fl.deleteBack();
    fl.deleteBack();
    fl.deleteAfter(fl.search(9));
    fl.deleteAfter(fl.search(9));
    fl.deleteAfter(fl.search(5));
    fl.deleteAfter(fl.search(5));
    fl.deleteAfter(fl.search(5));
    fl.print();

    return 0;
  }
