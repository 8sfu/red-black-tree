#include <iostream>
#include "tree.h"

Tree::Tree(Node* root){
  m_root = root;
}

Node* Tree::getRoot(){
  return m_root;
}

void Tree::setRoot(Node* root){
  m_root = root;
}

Tree::~Tree(){
  delete m_root;
}
