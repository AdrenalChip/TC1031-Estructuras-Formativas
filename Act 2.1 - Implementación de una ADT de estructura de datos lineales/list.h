#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}

template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();
	void clear();
	std::string toString() const;
	void insertion(int);
    int length() const;
	bool empty() const;
	void addFirst(T);
	int search(int);
	void update(int,int);
	int deleteAt(int);
private:
	Link<T> *head;
	int 	size;

	friend class ListIterator<T>;
};
template <class T>
void List<T>::clear() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}
template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

template <class T>
int List<T>::length() const {
	return size;
}
template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::~List() {
	clear();
}
template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
void List<T>::addFirst(T val) {
	Link<T> *newLink;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		cout<<"OutOfMemory";
	}
	newLink->next = head;
	head = newLink;
	size++;
}

template <class T>
void List<T>::insertion(int val){
	Link<T> *newLink, *p;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		cout<<"OutOfMemory";
	}
	if (empty()) {
		addFirst(val);
		return;
	}
	p = head;
	while (p->next != 0) { //buscar el final
		p = p->next;
	}
	newLink->next = 0;
	p->next = newLink;
	size++;
}
template <class T>
int List<T>::search(int val){
	Link <T> *p;
	p=head;
	int pos=0;
	int contador=0;
	while (contador != size){
		if (p->value==val){
			pos=contador;
		}else{
			pos=-1;
		}
		contador=contador+1;
		p=p->next;
	}
	return pos;
}
template <class T>
void List<T>::update(int pos,int val){
	Link <T> *p;
	p=head;
	int contador=0;
	while (contador != size){
		if (contador==pos){
			p->value=val;
		}
		contador=contador+1;
		p=p->next;
	}
}
template <class T>
int List<T>::deleteAt(int pos){
	Link <T> *p;
	T val;
	p = head;
	int contador=0;
	while (contador <size){
		if (contador==pos){
			val=p->value;
			delete p;
			size--;
		}
		contador=contador+1;
		head= p->next;
	}
	return val;

}
#endif