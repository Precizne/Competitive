
#include <iostream>

using namespace std;

class Node {
  public:
    int data;
    Node* prev;
    Node* next;
    
    Node() {
      this->data = 0;
      this->prev = nullptr;
      this->next = nullptr;
    }
    
    Node(int data) {
      this->data = data;
      this->prev = nullptr;
      this->next = nullptr;
    }
};

class List {
  public:
    Node* head;
    
    List() {
      head = nullptr;
    }
    
    void insertFront(int data) {
      Node* newnode = new Node(data);
      if(head == nullptr) {
        head = newnode;
        return;
      }
      newnode->next = head;
      head->prev = newnode;
      head = newnode;
    }
    
    void insertBack(int data) {
      Node* newnode = new Node(data);
      if(head == nullptr) {
        head = newnode;
        return;
      }
      Node* tmp = head;
      while(tmp->next != nullptr) {
        tmp = tmp->next;
      }
      tmp->next = newnode;
      newnode->prev = tmp;
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
      if(p->next != nullptr) {
        p->next->prev = newnode;
      }
      p->next = newnode;
      newnode->prev = p;
    }
    
    void deleteFront() {
      if(head == nullptr) {
        return;
      }
      Node* tmp = head;
      head = head->next;
      head->prev = nullptr;
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
      Node* tmp = head;
      while(tmp->next->next != nullptr) {
        tmp = tmp->next;
      }
      delete(tmp->next);
      tmp->next = nullptr;
    }
    
    void deleteAfter(Node* p) {
      if(head == nullptr || p == nullptr || p->next == nullptr) {
        return;
      }
      Node* tmp = p->next;
      p->next = tmp->next;
      if(p->next != nullptr) {
        p->next->prev = p;
      }
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
    
    void printrev() {
      if(head == nullptr) {
        return;
      }
      Node* tmp = head;
      while(tmp->next != nullptr) {
        tmp = tmp->next;
      }
      while(tmp != nullptr) {
        cout << tmp->data << " ";
        tmp = tmp->prev;
      }
    }
};

int main() {
  List l;
  l.insertFront(5);
  l.insertFront(7);
  l.insertBack(9);
  l.insertBack(3);
  l.insertAfter(l.search(5), 8);
  l.insertAfter(l.search(7), 6);
  l.insertAfter(l.search(9), 1);
  l.insertAfter(l.search(3), 0);
  l.deleteFront();
  l.deleteFront();
  l.deleteBack();
  l.deleteBack();
  l.deleteAfter(l.search(9));
  l.deleteAfter(l.search(9));
  l.deleteAfter(l.search(5));
  l.deleteAfter(l.search(5));
  l.deleteAfter(l.search(5));
  l.print();

  return 0;
}
