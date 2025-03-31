#ifndef NODE_H
#define NODE_H

enum color {
  red, 
  black
};

class Node {
 private:
  Node* m_parent;
  Node* m_left;
  Node* m_right;
  int m_value;
  enum color m_color;
 public:
  Node(int value);
  
  Node* getParent();
  Node* getLeft();
  Node* getRight();
  int getValue();
  enum color getColor();

  void setParent(Node* parent);
  void setLeft(Node* left);
  void setRight(Node* right);
  void setValue(int value);
  void setColor(enum color color);
  
  ~Node();
};

#endif
