#include <iostream>
#include <tuple>
#include "tree.h"

//(the -key i broken orry for confuing commenting)

Tree::Tree(Node* root){
  m_root = root;
}

Node* Tree::getRoot(){
  return m_root;
}

int printVal(Node* node){
  if(node == nullptr){
    return -7;
  }else{
    return node->getValue();
  }
}

//relative getter functions for red-black balancing

Node* parentOf(Node* node){
  return node->getParent();
}

Node* siblingOf(Node* node){
  if(parentOf(node) != nullptr){
    if(node->isLeftChild()){
      return parentOf(node)->getRight();
    }else{
      return parentOf(node)->getLeft();
    }
  }else{
    return nullptr;
  }
}

Node* uncleOf(Node* node){
  if(node->getParent() != nullptr){
    return siblingOf(node->getParent());
  }else{
    return nullptr;
  }
}

Node* grandparentOf(Node* node){
  if(node->getParent() != nullptr){
    return node->getParent()->getParent();
  }else{
    return nullptr;
  }
}

//4 rotation cae. there i a impler way to write thee with clockwie and counterclockwie
//rotation and color wapping but thi work and it' technically more efficient.

Node* rotateCaseLL(Node* node){
  Node* g = grandparentOf(node);
  Node* p = parentOf(node);
  Node* u = uncleOf(node);
  Node* x = node;
    
  g->setLeft(p->getRight());
  if(p->getRight() != nullptr){
    p->getRight()->setParent(g);
  }
  p->setRight(g);
  g->setParent(p);
  p->setColor(black);
  g->setColor(red);
  p->setParent(nullptr);

  return p;
}

Node* rotateCaseLR(Node* node){
  Node* g = grandparentOf(node);
  Node* p = parentOf(node);
  Node* u = uncleOf(node);
  Node* x = node;

  g->setLeft(x->getRight());
  if(x->getRight() != nullptr){
    x->getRight()->setParent(g);
  }
  p->setRight(x->getLeft());
  x->setLeft(p);
  g->setParent(x);
  x->setRight(g);
  p->setParent(x);
  x->setColor(black);
  g->setColor(red);
  x->setParent(nullptr);
    
  return x;
}

Node* rotateCaseRL(Node* node){
  Node* g = grandparentOf(node);
  Node* p = parentOf(node);
  Node* u = uncleOf(node);
  Node* x = node;
    
  g->setRight(x->getLeft());
  if(x->getLeft() != nullptr){
    x->getLeft()->setParent(g);
  }
  p->setLeft(x->getRight());
  x->setLeft(g);
  g->setParent(x);
  x->setRight(p);
  p->setParent(x);
  x->setColor(black);
  g->setColor(red);
  x->setParent(nullptr);
    
  return x;
}

Node* rotateCaseRR(Node* node){
  Node* g = grandparentOf(node);
  Node* p = parentOf(node);
  Node* u = uncleOf(node);
  Node* x = node;
    
  g->setRight(p->getLeft());
  if(p->getLeft() != nullptr){
    p->getLeft()->setParent(g);
  }
  p->setLeft(g);
  g->setParent(p);
  p->setColor(black);
  g->setColor(red);
  p->setParent(nullptr);
    
  return p;
}

//main rotation function

Node* rotateCase(Node* node){
  Node* p = parentOf(node);
  Node* r = nullptr;
  if(node->getColor() == red && p != nullptr && p->getColor() == red){
    if(node->isLeftChild() && p->isLeftChild()){
      r = rotateCaseLL(node);
    }else if(!node->isLeftChild() && p->isLeftChild()){
      r = rotateCaseLR(node);
    }else if(node->isLeftChild() && !p->isLeftChild()){
      r = rotateCaseRL(node);
    }else{
      r = rotateCaseRR(node);
    }
  }
  return r; //
}

char printCol(Color col){
  if(col){
    return 'r';
  }else{
    return 'b';
  }
}

void print(Node* node, string prev, bool isLeft){ //print syntax
  if(isLeft){
    if(node->getRight() != nullptr){
      print(node->getRight(),prev+" | ",false); //add a "|" in front of right children of a left node
    }
    cout << prev << " L (" << node->getValue() << " " << printCol(node->getColor()) << ")" << endl;
    if(node->getLeft() != nullptr){
      print(node->getLeft(),prev+"   ",true); // " " for left children of a right node
    }
  }else{
    if(node->getRight() != nullptr){
      print(node->getRight(),prev+"   ",false); // " " for right children of a left node
    }
    cout << prev << " Γ (" << node->getValue() << " " << printCol(node->getColor()) << ")" << endl;
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
    return parentOf(node);
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

void Tree::addAttempt2(int val){ //Top down iterative insertion balancing 
  if(val > 0 && val < 1000){
    Node* n = m_root;
    Node* x;
    if(m_root == nullptr){
      m_root = new Node(val);
      m_root->setColor(black);
    }else{
      while(n != nullptr){
	if(n->getColor() == black 
	   && n->getLeft() != nullptr && n->getLeft()->getColor() == red 
	   && n->getRight() != nullptr && n->getRight()->getColor() == red){
	  //push n's blackness down to its kids
	  if(n != m_root){ //keep n black if its a root, set it red otherwise
	    n->setColor(red);
	  }
	  n->getLeft()->setColor(black);
	  n->getRight()->setColor(black);
	  //rotate the subtree of n's grandparent
	  if(n->getColor() == red && parentOf(n) != nullptr && parentOf(n)->getColor() == red){
	    Node* g = grandparentOf(n);
	    if(g == nullptr){
	      parentOf(n)->setColor(black);
	    }else if(g != nullptr){
	      if(parentOf(g) == nullptr){ //ROOT CAE
		Node* s = rotateCase(n);
		m_root = s;
	      }else{
		Node* branch = parentOf(g);
		Node* s = rotateCase(n);
		if(branch->getValue() > s->getValue()){
		  branch->setLeft(s);
		}else{
		  branch->setRight(s);
		}
		s->setParent(branch);
	      }
	    }
	  }
	}
	else if(val < n->getValue()){
	  if(n->getLeft() != nullptr){
	    n = n->getLeft();
	  }else{
	    x = new Node(val);
	    n->setLeft(x);
	    x->setParent(n);
	    n = x;
	    //rotate the subtree of n's grandparent
	    if(n->getColor() == red && parentOf(n)->getColor() == red){
	      Node* g = grandparentOf(n);
	      if(g == nullptr){
		parentOf(n)->setColor(black);
	      }else if(g != nullptr){
		if(parentOf(g) == nullptr){
		  Node* s = rotateCase(n);
		  m_root = s;
		}else{
		  Node* branch = parentOf(g);
		  Node* s = rotateCase(n); 
		  if(branch->getValue() > s->getValue()){
		    branch->setLeft(s);
		  }else{
		    branch->setRight(s);
		  }
		  s->setParent(branch);
                                    
		}
	      }
	    }
	    return;
	  }
	}
	else if(val >= n->getValue()){
	  if(n->getRight() != nullptr){
	    n = n->getRight();
	  }else{
	    x = new Node(val);
	    n->setRight(x);
	    x->setParent(n);
	    n = x;
	    //rotate the subtree of n's grandparent
	    if(n->getColor() == red && parentOf(n)->getColor() == red){
	      Node* g = grandparentOf(n);
	      if(g == nullptr){
		parentOf(n)->setColor(black);
	      }else if(g != nullptr){
		if(parentOf(g) == nullptr){
		  Node* s = rotateCase(n);
		  m_root = s;
		}else{
		  Node* branch = parentOf(g);
		  Node* s = rotateCase(n);
		  if(branch->getValue() > s->getValue()){
		    branch->setLeft(s);
		  }else{
		    branch->setRight(s);
		  }
		  s->setParent(branch);
                                    
		}
	      }
	    }
	    return;
	  }
	}
      }
    }
  }
}

bool Tree::hasVal(int value){ //earch for node (call recurive earch function on root)
  if(m_root != nullptr){
    if(searchSubTree(m_root,value) != nullptr){
      return true;
    }
  }
  return false;
}

void Tree::deleteVal(int value){ //delete node (call recurive delete helper on root)
  while(this->hasVal(value)){
    m_root = delFromTree(searchSubTree(m_root,value));
  }
}

void Tree::printTree(){ //print (call recurive print helper on root)
  cout << endl;
  if(m_root != nullptr){
    if(m_root->getRight() != nullptr){
      print(m_root->getRight(),"      ",false);
    }
    cout << " Root: (" << m_root->getValue() << " " << printCol(m_root->getColor()) << ")" << endl;
    if(m_root->getLeft() != nullptr){
      print(m_root->getLeft(),"      ",true);   
    }
  }else{
    cout << "The tree is empty." << endl;
  }
  cout << endl;
}

void Tree::wipe(){ //wipe
  m_root = nullptr;
}

Tree::~Tree(){ //delete root
  delete[] m_root;
}
