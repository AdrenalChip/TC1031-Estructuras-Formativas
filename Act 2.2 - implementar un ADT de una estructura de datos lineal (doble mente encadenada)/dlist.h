
#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>
#include <iostream>
using namespace std;


template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
	friend class DListIterator<T>;
};

template <class T>
class DList {
public:
	DList(); //
	DList(const DList<T>&);
	~DList(); //

	void addFirst(T);//
	void insertion(T);
	T    getFirst() const; //
	T    removeFirst();
	T	 getLast();
	T    removeLast();
	int  length() const; //
	T    get(int) const; //
	bool contains(T) const; //
	bool empty() const; //
	void clear(); //
	string toStringBackward() const;
    string toStringForward() const;
	bool set(int, T);
	int  indexOf(T) const;
	int  lastIndexOf(T) const;
	T    remove(int);

private:
	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;

	friend class DListIterator<T>;
};

template <class T>
DList<T>::DList() {}

template <class T>
DList<T>::~DList() {
	clear();
}

template <class T>
bool DList<T>::empty() const {
	return 0;
}

template <class T>
int DList<T>::length() const {
	return size;
}

template <class T>
bool DList<T>::contains(T val) const {
	DLink<T> *p;

	p = head;
	while (p != 0) {
		if (p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

template <class T>
void DList<T>::addFirst(T val) {
	DLink<T> *newLink;

	newLink = new DLink<T>(val);
	if (newLink == 0) {
		cout<< "OutOfMemory";
	}

	if (empty()) {
		head = newLink;
		tail = newLink;
	} else {
		newLink->next = head;
		head->previous = newLink;
		head = newLink;
	}
	size++;
}

template <class T>
void DList<T>::insertion(T val){
	DLink<T> *newLink;

	newLink = new DLink<T>(val);
	if (newLink == 0) {
		cout<< "OutOfMemory";
	}

	if (empty()) {
		head = newLink;
		tail = newLink;
	} else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

template <class T>
T DList<T>::getFirst() const{
	if (empty()) {
		cout<< "NoSuchElement";
	}
	return head->value;
}

template <class T>
T DList<T>::get(int index) const{
	int pos;
	DLink<T> *p;

	if (index < 0 || index >= size) {
		cout<<"IndexOutOfBounds";
	}

	if (index == 0) {
		return getFirst();
	}

	p = head;
	pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}

	return p->value;
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
string DList<T>::toStringForward() const {
        stringstream aux;
		DLink<T> *p;

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
string DList<T>::toStringBackward() const {
		stringstream aux;
		DLink<T> *p;

		p = tail;
		aux << "[";
		while (p != 0) {
			aux << p->value;
			if (p->previous != 0) {
				aux << ", ";
			}
			p = p->previous;
		}
		aux << "]";
		return aux.str();
	}
#endif