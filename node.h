#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

enum Color {
  black,
  red
};

class Node {
  int m_value;
  Node* m_parent;
  Node* m_left;
  Node* m_right;
  enum Color m_color;
 public:
  Node(int value);
  
  bool hasBothChildren();
  bool hasLeftChild();
  bool hasRightChild();
  bool isLeftChild();
  bool isBlack();
  
  //GETTERS AND SETTERS
  int getValue();
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  Node* getSibling();
  enum Color getColor();
  
  void setLeft(Node* left);
  void setRight(Node* right);
  void setParent(Node* parent);
  void setValue(int value);
  void setColor(enum Color color);
  
  ~Node();
};

#endif
