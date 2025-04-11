#include <iostream>
#include "tree.h"

Tree::Tree(Node* root){
  m_root = root;
}

Node* Tree::getRoot(){
  return m_root;
}

Node* parent(Node* node){
  return node->getParent();
}

Node* sibling(Node* node){
  if(node->getParent() == nullptr){
    if(node->isLeftChild()){
      return node->getParent()->getRight();
    }else{
      return node->getParent()->getLeft();
    }
  }else{
    return nullptr;
  }
}

Node* uncle(Node* node){
  if(node->getParent() == nullptr){
    return sibling(node->getParent());
  }else{
    return nullptr;
  }
}

Node* grandparent(Node* node){
  if(node->getParent() == nullptr){
    return node->getParent()->getParent();
  }else{
    return nullptr;
  }
}

int insertCase(Node* node){ //check the tree validity of an add attempt
  if(parent(node) != nullptr){
    if(parent(node)->getColor() == black){ //insert case 1
      return 1;
    }else if(parent(node)->getColor() == red){
      if(sibling(node) == nullptr || sibling(node)->getColor() == black){
	return 2;
      }else if(sibling(node) == red){
	return 3;
      }
    }
  }else{
    return 71;
  }
}

void attachChild(Node* parent, Node* child){
  if(child != nullptr){ //recursively add a child to a parents left or right side
    child->setColor(red);
    if(child->getValue() < parent->getValue()){
      if(parent->getLeft() == nullptr){ //if we have reached a root, attach the child
	parent->setLeft(child);
	child->setParent(parent);
      }else{ //otherwise continue recursing
	attachChild(parent->getLeft(),child);
      }
        }else{
      if(parent->getRight() == nullptr){
	parent->setRight(child);
	child->setParent(parent);
      }else{
	attachChild(parent->getRight(),child);
      }
    }
  }
}


void print(Node* node, string prev, bool isLeft){ //print syntax
  if(isLeft){
    if(node->getRight() != nullptr){
      print(node->getRight(),prev+" | ",false); //add a "|" in front of right children of a left node
    }
    cout << prev << " L " << node->getValue() << " " << node->getColor() << endl;
    if(node->getLeft() != nullptr){
      print(node->getLeft(),prev+"   ",true); // " " for left children of a right node
    }
  }else{
    if(node->getRight() != nullptr){
      print(node->getRight(),prev+"   ",false); // " " for right children of a left node
    }
    cout << prev << " Γ " << node->getValue() << " " << node->getColor() << endl;
    if(node->getLeft() != nullptr){
      print(node->getLeft(),prev+" | ",true); // " | " for left children of a left node
    } 
  }
}

Node* searchSubTree(Node* node, int value){ //recursively search subtrees to see if a value exists
  if(node->getValue() == value){
    return node;
  }else{
    if(value < node->getValue()){
      if(node->getLeft() == nullptr){
	return nullptr;
      }
      return searchSubTree(node->getLeft(),value);
    }else{
      if(node->getRight() == nullptr){
	return nullptr;
      }
      return searchSubTree(node->getRight(),value);
    }
  }
}

Node* leftmostChildOf(Node* node){ //useful in finding successors
  if(node->getLeft() == nullptr){
    return node;
  }else{
    return leftmostChildOf(node->getLeft());
  }
}

Node* successorOf(Node* node){ //get the successor 
  if(node->getRight() == nullptr){
    return nullptr;
    //We don't need to worry about proper inorder traversal yet.
  }else{
  return leftmostChildOf(node->getRight());
  }
}

Node* Tree::delFromTree(Node* node){
  if(node->hasBothChildren()){ //Node has both children
    node->setValue(successorOf(node)->getValue());
    m_root = delFromTree(successorOf(node));
    return m_root;
  }else if(node->hasLeftChild()){ //Node has one child (left)
    if(node->getParent() != nullptr){
      if(node->isLeftChild()){
	node->getParent()->setLeft(node->getLeft());
      }else{
	node->getParent()->setRight(node->getLeft());
      }
      return m_root;
    }
    return m_root->getLeft();
  }else if(node->hasRightChild()){ //Node has one child (right)
    if(node->getParent() != nullptr){
      if(node->isLeftChild()){
	node->getParent()->setLeft(node->getRight());
      }else{
	node->getParent()->setRight(node->getRight());
      }
      return m_root;
    }
    return m_root->getRight();
  }else{ //Node is a leaf
    if(node->getParent() != nullptr){
      if(node->isLeftChild()){
	node->getParent()->setLeft(nullptr);
      }else{
	node->getParent()->setRight(nullptr);
      }
      return m_root;
    }
    return nullptr;
  }
}

void Tree::addNode(Node* node){ //add nodes while considering the root case 
  if(m_root == nullptr){
    m_root = node;
    m_root->setColor(black);
  }else{
    attachChild(m_root,node);
  }
}

bool Tree::hasVal(int value){ //check for nodes while considering the root case
  if(m_root != nullptr){
    if(searchSubTree(m_root,value) != nullptr){
      return true;
    }
  }
  return false;
}

void Tree::deleteVal(int value){ //delete nodes (root case)
  while(this->hasVal(value)){
    m_root = delFromTree(searchSubTree(m_root,value));
  }
}

void Tree::printTree(){ //print (root case)
  cout << endl;
  if(m_root != nullptr){
    if(m_root->getRight() != nullptr){
      print(m_root->getRight(),"      ",false);
    }
    cout << " Root: " << m_root->getValue() << " " << m_root->getColor() << endl;
    if(m_root->getLeft() != nullptr){
      print(m_root->getLeft(),"      ",true);   
    }
  }else{
    cout << "The tree is empty." << endl;
  }
  cout << endl;
}

void Tree::wipe(){ //wipe (root
  m_root = nullptr;
}

Tree::~Tree(){ //delete root
  delete[] m_root;
}
