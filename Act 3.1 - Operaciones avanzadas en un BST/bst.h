#ifndef bst_H
#define bst_H

#include <string>
#include <sstream>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
template <class T> class BST;

template <class T>
class Node {
private:
	T value;
	Node *left, *right;
    int level,balance;
	Node<T>* succesor();

public:
	Node(T);
	Node(T, Node<T>*, Node<T>*,int);
	void add(T);
	bool find(T);
	void remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
    void postorder(std::stringstream&) const;
    void levelorder(std::stringstream&) const;
    int max_depth() ;
    bool ancestors(Node*,int,stringstream&);
	friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0),level(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri,int lev)
	: value(val), left(le), right(ri), level(lev) {}

template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new Node<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new Node<T>(val);
		}
	}
}

template <class T>
bool Node<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) {
		left = left->left;
		le->left = 0;
		return le;
	}

	Node<T> *parent, *child;
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

template <class T>
void Node<T>::remove(T val) {
	Node<T> * succ, *old;

	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				succ = left->succesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				succ = right->succesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(val);
			}
		}
	}
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
        aux<< " ";
	}
	if (right != 0) {
		right->postorder(aux);
        aux<< " ";
	}
    aux<< value;
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
int Node<T>::max_depth() {
	int le =1 , ri = 1;
	if (left != 0)
		le = left->max_depth() + 1;
	if (right != 0)
		ri = right->max_depth() + 1;
	if(le > ri)
		level = le;
	else
		level = ri;
	balance = le - ri;
	return level;
}

template <class T>
bool Node<T>::ancestors(Node* root,int target,stringstream &aux)
{if (root == NULL)
     return false;
  if (root->value == target)
     return true;
  
  if (ancestors(root->left, target,aux) ||
       ancestors(root->right, target,aux) ) {
      aux<<root->value<<" ";
      return true;
  } else {
      return false;
  }
}
///
template <class T>
void Node<T>::levelorder(std::stringstream &aux) const {
     
}
///
template <class T>
class BST {
private:
	Node<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string preorder() const;
    std::string visit() const;
    std::string postorder() const;
    std::string levelorder() const;
    int height();
    string ancestors (int);
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}
template <class T>
void BST<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template<class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::levelorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->LevelOrder(aux);
	}
	aux << "]";
	return aux.str();
}
template <class T>
std::string BST<T>::visit() const{
    std::stringstream aux;
    aux << preorder();
    aux << "\n";
    aux << inorder();
    aux << "\n";
    aux << postorder();
    aux << "\n";
    //aux <<levelorder();
    return aux.str();
}
template <class T>
int BST<T>::height(){
    int h=root->max_depth();
    return h;
}
template<class T>
std::string BST<T>::ancestors(int target){
    bool x;
    stringstream aux;
    aux << "[";
	if (!empty()) {
		x=root->ancestors(root,target,aux);
	}
	aux << "]";
    string y=aux.str();
    y.erase(y.end()-2);
    stringstream aux1;
    aux1<<y;
	return aux1.str();
}
#endif