#ifndef TREE_H
#define TREE_H
#include "node.h"

class Tree {
 private:
  Node* m_root;
 public:
  Tree(Node* root);
  
  Node* getRoot();
  void setRoot(Node* root);
  
  ~Tree();
};

#endif
