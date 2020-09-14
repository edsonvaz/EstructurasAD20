/*
 * linkedlist.h
 * solucion en clase
 *  Created on: 05/08/2015
 *      Author: pperezm
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <sstream>
#include "exception.h"

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
	List(const List<T>&) throw (OutOfMemory);
	~List();

	void addFirst(T) throw (OutOfMemory);
	void add(T) throw (OutOfMemory);
	T    getFirst() const throw (NoSuchElement);
	T    removeFirst() throw (NoSuchElement);
	int  length() const;
	T    get(int) const throw (IndexOutOfBounds, NoSuchElement);
	bool contains(T) const;
	bool empty() const;
	void clear();
	std::string toString() const;
	void operator= (const List&) throw (OutOfMemory);

	void addBefore(ListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
	void addAfter(ListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
	T    removeCurrent(ListIterator<T>&) throw (IllegalAction);

	bool set(unsigned int, T) throw (IndexOutOfBounds);
	unsigned int  indexOf(T) const;
	int  lastIndexOf(T) const;
	T    remove(int) throw (IndexOutOfBounds);
	bool removeFirstOcurrence(T);
	bool removeLastOcurrence(T);

private:
	Link<T> *head;
	int 	size;

	friend class ListIterator<T>;
};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::~List() {
	clear();
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
bool List<T>::contains(T val) const {
	Link<T> *p;

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
T List<T>::getFirst() const throw (NoSuchElement) {
	if (empty()) {
		throw NoSuchElement();
	}
	return head->value;
}

template <class T>
void List<T>::addFirst(T val) throw (OutOfMemory) {
	Link<T> *newLink;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}
	newLink->next = head;
	head = newLink;
	size++;
}

template <class T>
void List<T>::add(T val) throw (OutOfMemory) {
	Link<T> *newLink, *p;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}
	
	if (empty()) {
		addFirst(val);
		return;
	}

	p = head;
	while (p->next != 0) {
		p = p->next;
	}

	newLink->next = 0;
	p->next = newLink;
	size++;
}

template <class T>
T List<T>::removeFirst() throw (NoSuchElement) {
	T val;
	Link<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	head = p->next;
	val = p->value;

	delete p;
	size--;

	return val;
}

template <class T>
T List<T>::get(int index) const throw (IndexOutOfBounds, NoSuchElement) {
	int pos;
	Link<T> *p;

	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
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
List<T>::List(const List<T> &source) throw (OutOfMemory) {
	Link<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
	} else {
		p = source.head;
		head = new Link<T>(p->value);
		if (head == 0) {
			throw OutOfMemory();
		}
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new Link<T>(p->value);
			if (q->next == 0) {
				throw OutOfMemory();
			}
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
void List<T>::operator=(const List<T> &source) throw (OutOfMemory) {
	Link<T> *p, *q;

	clear();
	if (source.empty()) {
		size = 0;
		head = 0;
	} else {
		p = source.head;
		head = new Link<T>(p->value);
		if (head == 0) {
			throw OutOfMemory();
		}
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new Link<T>(p->value);
			if (q->next == 0) {
				throw OutOfMemory();
			}
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
void List<T>::addBefore(ListIterator<T> &itr, T val) throw (IllegalAction, OutOfMemory) {
}

template <class T>
void List<T>::addAfter(ListIterator<T> &itr, T val) throw (IllegalAction, OutOfMemory) {
}

template <class T>
T List<T>::removeCurrent(ListIterator<T> &itr) throw (IllegalAction) {
}

template <class T>
bool List<T>::set(unsigned int index, T val) throw (IndexOutOfBounds) {

	/** tarea **/

	return true;
}

template <class T>
unsigned int List<T>::indexOf(T val) const {
	
	/** tarea **/
	
	return -1;
}

template <class T>
int List<T>::lastIndexOf(T val) const {

	/** tarea **/

	return -1;
}

template <class T>
T List<T>::remove(int index) throw (IndexOutOfBounds) {

	/** tarea **/

	return -1;
}

template <class T>
bool List<T>::removeFirstOcurrence(T val) {

	/** tarea **/

	return false;
}

template <class T>
bool List<T>::removeLastOcurrence(T val) {

	/** tarea **/

	return false;
}


template <class T>
class ListIterator {
}

template <class T>
ListIterator<T>::ListIterator(const ListIterator<T> &source) : theList(source.theList) {
}

template <class T>
bool ListIterator<T>::begin() {
}

template <class T>
T& ListIterator<T>::operator() () throw (NoSuchElement) {
}

template <class T>
bool ListIterator<T>::end() {
}

template <class T>
bool ListIterator<T>::operator++ () {
}

template <class T>
void ListIterator<T>::operator= (T val) throw (NoSuchElement) {
}

#endif /* LINKEDLIST_H_ */