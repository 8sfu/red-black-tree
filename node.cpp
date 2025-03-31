#include <iostream>
#include "node.h"

Node::Node(int value){
  m_parent = nullptr;
  m_left = nullptr;
  m_right = nullptr;
  m_value = value;
  m_color = red;
}

Node* Node::getParent(){
  return m_parent;
}

Node* Node::getLeft(){
  return m_left;
}

Node* Node::getRight(){
  return m_right;
}

int Node::getValue(){
  return m_value;
}

enum color Node::getColor(){
  return m_color;
} 

void Node::setParent(Node* parent){
  m_parent = parent;
}

void Node::setLeft(Node* left){
  m_left = left;
}

void Node::setRight(Node* right){
  m_right = right;
}

void Node::setValue(int value){
  m_value = value;
}

void Node::setColor(enum color color){
  m_color = color;
}

Node::~Node(){
  delete m_parent;
  delete m_left;
  delete m_right;
}
