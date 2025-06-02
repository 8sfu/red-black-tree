#include <iostream>
//#include <tuple>
#include "tree.h"

Tree::Tree(Node* root){
  m_root = root;
}

Node* Tree::getRoot(){
  return m_root;
}

Node* parentOf(Node* node){
  return node->getParent();
}

int printVal(Node* node){
  if(node == nullptr){
    return -7;
  }else{
    return node->getValue();
  }
}

Node* siblingOf(Node* node){
  //cout << "SIBLING" << endl;
  if(parentOf(node) != nullptr){
    if(node->isLeftChild()){
      return parentOf(node)->getRight();
    }else{
      return parentOf(node)->getLeft();
    }
  }else{
    //cout << "RETURNING NULL" << endl;
    return nullptr;
  }
}

Node* uncleOf(Node* node){
  //cout << "UNCLE" << endl;
  if(node->getParent() != nullptr){
    return siblingOf(node->getParent());
  }else{
    //cout << "RETURNING NULL" << endl;
    return nullptr;
  }
}

Node* grandparentOf(Node* node){
  //cout << "GRANDPARENT" << endl;
  if(node->getParent() != nullptr){
    return node->getParent()->getParent();
  }else{
    //cout << "RETURNING NULL" << endl;
    return nullptr;
  }
}

//tuple<bool,Node*> insertCase(Node* node, Node* root);
//Node* rotateCase(Node* node);


//CHANGE PULLBLACK TO RETURN TUPLES AND RECURSIVELY CALL INSERTCASE
void pullBlack(Node* node, Node* root){ //Node will pull down blackness from its parent
  if(node->getColor() == red && parentOf(node)->getColor() == red && (uncleOf(node) != nullptr && uncleOf(node)->getColor() == red)){
    //cout << "PULLING BLACK DOWN" << endl;
    if(uncleOf(node) != nullptr){
      uncleOf(node)->setColor(black);
      //cout << uncleOf(node)->getValue() << " is black now" << endl;
    }
    if(parentOf(node) != nullptr){
      parentOf(node)->setColor(black);
      //cout << parentOf(node)->getValue() << " is black now" << endl;
    }
    if(grandparentOf(node) != nullptr && parentOf(grandparentOf(node)) != nullptr){ //node isn't the root
      grandparentOf(node)->setColor(red);
      //cout << grandparentOf(node)->getValue() << " is red now" << endl;
    }
    pullBlack(grandparentOf(node),root);
  }/*else if(node->getColor() == red && parentOf(node)->getColor() == red && uncleOf(node) == nullptr || uncleOf(node)->getColor() == black){
   //cout << "ROTATION NEEDED HERE" << endl;
   }*/
}

/*void retrofit(Node* node, Node* parent, Node* left, Node* right, bool isLeft){
    node->setParent(parent);
    if(isLeft){
        parent->setLeft(node);
    }else{
        parent->setRight(node);
    }
    node->setLeft(left);
    left->setParent(parent);
    node->setRight(right);
    right->setParent(parent);
}

void swap(Node* a, Node* b){
    if(a != nullptr && b != nullptr){
        Node* p = a->getParent();
        Node* l = a->getLeft();
        Node* r = a->getRight();
        bool aIsLeft = a->isLeftChild();
        bool bIsLeft = a->isLeftChild();
        retrofit(a,b->getParent(),b->getLeft(),b->getRight(),b->isLeftChild());
        retrofit(b,p,l,r,a->isLeftChild());
    }
    }*/

Node* rotateCaseLL(Node* node){
  Node* g = grandparentOf(node);
  Node* p = parentOf(node);
  Node* u = uncleOf(node);
  Node* x = node;
    
  //cout << "PREROTATION LL" << endl << endl << endl;
  //Tree* checkR1 = new Tree(g);
  //checkR1->printTree();

  //cout << "x is " << printVal(x) << " w left " <<  printVal(x->getLeft()) << " a right " << printVal(x->getRight()) << endl;
  //cout << "g is " << printVal(g) << " w left " <<  printVal(g->getLeft()) << " a right " << printVal(g->getRight()) << endl;
  //cout << "p is " << printVal(p) << " w left " <<  printVal(p->getLeft()) << " a right " << printVal(p->getRight()) << endl;
  if(u != nullptr){
    //cout << "u is " << printVal(u) << " w left " <<  printVal(u->getLeft()) << " a right " << printVal(u->getRight()) << endl;
  }
    
  g->setLeft(p->getRight());
  if(p->getRight() != nullptr){
    p->getRight()->setParent(g);
  }
  p->setRight(g);
  g->setParent(p);
  p->setColor(black);
  g->setColor(red);
    
  p->setParent(nullptr);
    
  //cout << "POSTROTATION LL" << endl << endl << endl;
  //Tree* checkR2 = new Tree(p);
  //checkR2->printTree();
    
  return p;
}

Node* rotateCaseLR(Node* node){
  Node* g = grandparentOf(node);
  Node* p = parentOf(node);
  Node* u = uncleOf(node);
  Node* x = node;
    
  //cout << "PREROTATION LR" << endl << endl << endl;
  //Tree* checkR1 = new Tree(g);
  //checkR1->printTree();

  //cout << "x is " << printVal(x) << " w left " <<  printVal(x->getLeft()) << " a right " << printVal(x->getRight()) << endl;
  //cout << "g is " << printVal(g) << " w left " <<  printVal(g->getLeft()) << " a right " << printVal(g->getRight()) << endl;
  //cout << "p is " << printVal(p) << " w left " <<  printVal(p->getLeft()) << " a right " << printVal(p->getRight()) << endl;
  if(u != nullptr){
    //cout << "u is " << printVal(u) << " w left " <<  printVal(u->getLeft()) << " a right " << printVal(u->getRight()) << endl;
  }
    
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
    
  //cout << "POSTROTATION LR" << endl << endl << endl;
  //Tree* checkR2 = new Tree(x);
  //checkR2->printTree();
    
  return x;
}

Node* rotateCaseRL(Node* node){
  Node* g = grandparentOf(node);
  Node* p = parentOf(node);
  Node* u = uncleOf(node);
  Node* x = node;
    
  //cout << "PREROTATION RL" << endl << endl << endl;
  //Tree* checkR1 = new Tree(g);
  //checkR1->printTree();

  //cout << "x is " << printVal(x) << " w left " <<  printVal(x->getLeft()) << " a right " << printVal(x->getRight()) << endl;
  //cout << "g is " << printVal(g) << " w left " <<  printVal(g->getLeft()) << " a right " << printVal(g->getRight()) << endl;
  //cout << "p is " << printVal(p) << " w left " <<  printVal(p->getLeft()) << " a right " << printVal(p->getRight()) << endl;
  if(u != nullptr){
    //cout << "u is " << printVal(u) << " w left " <<  printVal(u->getLeft()) << " a right " << printVal(u->getRight()) << endl;
  }
    
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
    
  //cout << "POSTROTATION RL" << endl << endl << endl;
  //Tree* checkR2 = new Tree(x);
  //checkR2->printTree();
    
  return x;
}

Node* rotateCaseRR(Node* node){
  Node* g = grandparentOf(node);
  Node* p = parentOf(node);
  Node* u = uncleOf(node);
  Node* x = node;
    
  cout << "PREROTATION RR" << endl << endl << endl;
  Tree* checkR1 = new Tree(g);
  checkR1->printTree();

  cout << "x is " << printVal(x) << " w left " <<  printVal(x->getLeft()) << " a right " << printVal(x->getRight()) << endl;
  if(g != nullptr){
    cout << "g is " << printVal(g) << " w left " <<  printVal(g->getLeft()) << " a right " << printVal(g->getRight()) << endl;
  }
  cout << "p is " << printVal(p) << " w left " <<  printVal(p->getLeft()) << " a right " << printVal(p->getRight()) << endl;
  if(u != nullptr){
    cout << "u is " << printVal(u) << " w left " <<  printVal(u->getLeft()) << " a right " << printVal(u->getRight()) << endl;
  }
    
  g->setRight(p->getLeft());
  if(p->getLeft() != nullptr){
    p->getLeft()->setParent(g);
  }
  p->setLeft(g);
  g->setParent(p);
  
  p->setColor(black);
  g->setColor(red);    
  p->setParent(nullptr);
    
  cout << "POSTROTATION RR" << endl << endl << endl;
  Tree* checkR2 = new Tree(p);
  checkR2->printTree();
    
  return p;
}

Node* rotateCase(Node* node){
  Node* p = parentOf(node);
  if(p != nullptr){
    cout << node->getValue() << " @ " << node << "  has parent " << p->getValue() << " @ " << p << endl;
  }
  Node* g = grandparentOf(node);
  if(g != nullptr){
    cout << node->getValue() << " @ " << node << " has grandparent " << g->getValue() << " @ " << g << endl;
  }
  Node* u = uncleOf(node);
  if(u != nullptr){
    cout << node->getValue() << " @ " << node << " has corbin " << u->getValue() << " @ " << u << endl;
  }
  Node* temp = nullptr;
  //temp = root;
  cout << "ROTATING" << endl;
  if(node->getColor() == red && p != nullptr && p->getColor() == red){
    if(node->isLeftChild() && p->isLeftChild()){
      cout << "ROTATE CASE LL" << endl;
      temp = rotateCaseLL(node);
      //cout << temp->getValue() << endl;
    }else if(!node->isLeftChild() && p->isLeftChild()){
      cout << "ROTATE CASE LR" << endl;
      temp = rotateCaseLR(node);
      //cout << temp->getValue() << endl;
    }else if(node->isLeftChild() && !p->isLeftChild()){
      cout << "ROTATE CASE RL" << endl;
      temp = rotateCaseRL(node);
      //cout << temp->getValue() << endl;
    }else{
      cout << "ROTATE CASE RR" << endl;
      temp = rotateCaseRR(node);
      //cout << temp->getValue() << endl;
    }
  }else{
    cout << "NO ROTATION NEEDED" << endl;
  }
  //cout << "NEW ROOT WILL BE " << temp->getValue() << " AT " << temp << endl; 
  return temp;
}

/*tuple<bool,Node*> insertCase(Node* node, Node* root){ //check the tree validity of an add attempt
  tuple<bool,Node*> output;
  //cout << "ROOT IS " << root->getValue() << " AT " << root << endl;
  //cout << "INSERT FIX FOR " << node->getValue() << endl;
  if(parentOf(node) != nullptr){
    //cout << " parent is " << parentOf(node)->getValue() << endl;
  }
  if(node->getColor() == red){
    //cout << "NODE IS RED" << endl;
    if(parentOf(node) == nullptr){
      //cout << "CASE 1" << endl;
      node->setColor(black);
      output = make_tuple(true,root);
      return output;
      //return true;
    }else if(parentOf(node)->getColor() == black){ 
      //cout << "CASE 2" << endl;
      output = make_tuple(false,root);
      return output;
      //return false;
    }else if(parentOf(node)->getColor() == red){
      //cout << "PARENT IS RED" << endl;
      if(uncleOf(node) == nullptr || uncleOf(node)->getColor() == black){
	//cout << "CASE 4"<< endl;
	if(parentOf(grandparentOf(node)) == nullptr){
	  //cout << "CASE 4a" << endl;
	  root = rotateCase(node);
	  //root = rotateCase(node,root);
	  root->setParent(nullptr);
	  output = make_tuple(true,root);
	}else{
	  //cout << "CASE 4b" << endl;
	  Node* greatGrand = parentOf(grandparentOf(node));
	  Node* newGramp = rotateCase(node);
	  if(greatGrand->getValue() < newGramp->getValue()){
	    greatGrand->setRight(newGramp);
	  }else{
	    greatGrand->setLeft(newGramp);
	  }
	  newGramp->setParent(greatGrand);
                    
                    
	  output = make_tuple(true,root);
	}
	return output;
	//return true;
      }else if(uncleOf(node)->getColor() == red){
	//cout << "CASE 3" << endl;
	pullBlack(node,root);
	output = make_tuple(true,root);
	//cout << "I (PROGRAM) COULD PRINT THINGS BUT NOPE" << endl;
	//Tree* temp = new Tree(root);
	//temp->printTree();
                
	return output;
	//return true;
      }
    }
  }
  output = make_tuple(false,root);
  return output;
  //return false;
}

Node* attachChild(Node* parent, Node* child, Node* root){
  //actual attaching code
  if(child != nullptr){ //recursively add a child to a parents left or right side
    child->setColor(red);
    if(child->getValue() < parent->getValue()){
      if(parent->getLeft() == nullptr){ //if we have reached a root, attach the child
	parent->setLeft(child);
	child->setParent(parent);
      }else{ //otherwise continue recursing
	root = attachChild(parent->getLeft(),child,root);
      }
    }else{
      if(parent->getRight() == nullptr){
	parent->setRight(child);
	child->setParent(parent);
      }else{
	root = attachChild(parent->getRight(),child,root);
      }
    }
  }
  //red black tree rebalancing shenanigans
  tuple<bool,Node*> newRoot;
  newRoot = insertCase(child,root);
  while(get<0>(newRoot)){
    root = get<1>(newRoot);
    newRoot = insertCase(child,root);
    //cout << "INSERTCASED enter for step" << endl;
    //char* junk = new char[50];
    //cin >> junk;
    //delete[] junk;
    //cout << endl;

    //cout << "THE NEW ROOT IS " << (root)->getValue() << " AT " << (root) << endl;
    //Tree* c = new Tree(root);
    //c->printTree();
  }
  

    
  return root;
  }*/

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

/*void Tree::addNode(Node* node){ //add nodes while considering the root case 
  if(m_root == nullptr){
    m_root = node;
    m_root->setColor(black);
  }else{
    m_root = attachChild(m_root,node,m_root);
  }
  }*/


void Tree::addAttempt2(int val){ //TOP DOWN INERTION (the -key i broken orry for confuing commenting)
  if(val > 0 && val < 1000){
    cout << "ADDING " << val << endl;
    Node* n = m_root;
    Node* x;
    if(m_root == nullptr){
      cout << "CASE 1" << endl;
      m_root = new Node(val);
      m_root->setColor(black);
    }else{
      while(n != nullptr){
	Tree* t = new Tree(n);
	cout << " n is " << n->getValue();
	t->printTree();
                
	cout << "CASE 2" << endl;
	if(n->getColor() == black 
	   && n->getLeft() != nullptr && n->getLeft()->getColor() == red 
	   && n->getRight() != nullptr && n->getRight()->getColor() == red){
	  cout << "CASE 2a" << endl;
	  if(n != m_root){
	    n->setColor(red);
	  }
	  n->getLeft()->setColor(black);
	  n->getRight()->setColor(black);
                    
	  //ROTATE N
	  if(n->getColor() == red && parentOf(n) != nullptr && parentOf(n)->getColor() == red){
	    Node* g = grandparentOf(n);
	    /*if(g != nullptr){
	      cout << " g is " << g->getValue() << " @ " << g << endl;
	      }*/
	    if(g == nullptr){
	      parentOf(n)->setColor(black);
	    }else if(g != nullptr){
	      if(parentOf(g) == nullptr){
		//cout << "ROOT CASE" << endl;
		Node* s = rotateCase(n); //rotated subtree
		/*if(s != nullptr){
		  cout << " s is " << s->getValue() << " @ " << s << endl;
		  }*/
		m_root = s;
		cout << m_root->getValue() << " " << m_root << endl;
	      }else{
		//cout << "NOT ROOT CASE" << endl;
		Node* branch = parentOf(g);
		Node* s = rotateCase(n); //rotated subtree
		if(s != nullptr){
		  cout << " s2 is " << s->getValue() << " @ " << s << endl;
		}
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
	if(val < n->getValue()){
	  cout << "CASE 2b" << endl;
                    
	  if(n->getLeft() != nullptr){
	    n = n->getLeft();
	  }else{
	    x = new Node(val);
	    n->setLeft(x);
	    x->setParent(n);
	    n = x;
                        
	    //ROTATE N
	    if(n->getColor() == red && parentOf(n)->getColor() == red){
	      Node* g = grandparentOf(n);
	      /*if(g != nullptr){
		cout << " g is " << g->getValue() << " @ " << g << endl;
		}*/
	      if(g == nullptr){
		parentOf(n)->setColor(black);
	      }else if(g != nullptr){
		if(parentOf(g) == nullptr){
		  //cout << "ROOT CASE" << endl;
		  Node* s = rotateCase(n); //rotated subtree
		  /*if(s != nullptr){
		    cout << " s is " << s->getValue() << " @ " << s << endl;
		    }*/
		  m_root = s;
		  cout << m_root->getValue() << " " << m_root << endl;
		}else{
		  //cout << "NOT ROOT CASE" << endl;
		  Node* branch = parentOf(g);
		  Node* s = rotateCase(n); //rotated subtree
		  if(s != nullptr){
		    cout << " s2 is " << s->getValue() << " @ " << s << endl;
		  }
		  if(branch->getValue() > s->getValue()){
		    branch->setLeft(s);
		  }else{
		    branch->setRight(s);
		  }
		  s->setParent(branch);
                                
		}
	      }
	    }

	    this->printTree();
	    return;
	  }
	}
	if(val >= n->getValue()){
	  cout << "CASE 2c" << endl;
    
	  if(n->getRight() != nullptr){
	    n = n->getRight();
	  }else{
	    x = new Node(val);
	    n->setRight(x);
	    x->setParent(n);
	    n = x;
                        
	    //ROTATE N
	    if(n->getColor() == red && parentOf(n)->getColor() == red){
	      Node* g = grandparentOf(n);
	      /*if(g != nullptr){
		cout << " g is " << g->getValue() << " @ " << g << endl;
		}*/
	      if(g == nullptr){
		parentOf(n)->setColor(black);
	      }else if(g != nullptr){
		if(parentOf(g) == nullptr){
		  //cout << "ROOT CASE" << endl;
		  Node* s = rotateCase(n); //rotated subtree
		  if(s != nullptr){
		    cout << " s1 is " << s->getValue() << " @ " << s << endl;
		  }
		  m_root = s;
		  cout << m_root->getValue() << " " << m_root << endl;
		}else{
		  //cout << "NOT ROOT CASE" << endl;
		  Node* branch = parentOf(g);
		  Node* s = rotateCase(n); //rotated subtree
		  if(s != nullptr){
		    cout << " s2 is " << s->getValue() << " @ " << s << endl;
		  }
		  if(branch->getValue() > s->getValue()){
		    branch->setLeft(s);
		  }else{
		    branch->setRight(s);
		  }
		  s->setParent(branch);
                                
		}
	      }
	    }

	    this->printTree();
	    return;
	  }
	}
      }
    }
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
    cout << " Root: (" << m_root->getValue() << " " << printCol(m_root->getColor()) << ")" << endl;
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
