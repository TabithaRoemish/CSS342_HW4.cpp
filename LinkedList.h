// File: LinkedList.h
//	Programmer: Tabitha Roemish
//	Date: 10/30/2017
//	File Includes:
//		Linked list class declaration
//		Linked list class definitions
//		Node class declaration & defintions

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

template <class T>
class node
{
public:
	node<T>(T thing) : object(thing), next(NULL), prev(NULL), Count(0) {};
	~node<T>() {};
	node<T>* next;
	node<T>* prev;
	T object;
	int Count;
};

template <class T>
class LinkedList
{
public:
	LinkedList() : head(NULL), tail(NULL), size(0) {};
	virtual ~LinkedList() { clearList(); };

	void clearList(); 
	void insert(T object);
	void deleteObject(T object);
	
	
	// accessors
	int getSize() { return size; };
	node<T>* getHead() { return head; };
	node<T>* getTail() { return tail; };
	node<T>* nextNode(node<T>* nd) { return nd->next; };
	node<T>* prevNode(node<T>* nd) { return nd->prev; };
	node<T>* search(T thing);

	void print(std::ostream& out) ;
protected: 
	//mutators
	void setHead(node<T>* hd) { head = hd; };
	void setTail(node<T>* tl) { tail = tl; };
	void setSize(int sz) { size = sz; };
private:
	node<T>* head;
	node<T>* tail;
	int size;
	
};

template <class T>
std::ostream& operator<<(std::ostream& out, LinkedList<T>& list)
{
	list.print(out);
	return out;
}

//LinkedList Definitions ------------------------


template <class T>
void LinkedList<T>::insert(T object)
{
	size++;
	try
	{
		node<T> * newNode = new node<T>(object);
		newNode->Count++;
		if (head == NULL && tail == NULL)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
	}
	catch (bad_alloc & ba)
	{
		cerr << "Could not allocate memory";
	}
}

//uses cout to confirm object has been deleted
template <class T>
void LinkedList<T>::deleteObject(T object)
{
	node<T>* temp = seach(object);
	if (size != 0 && temp != NULL)
	{
		if (nextNode(temp) != NULL && prevNode(temp) != NULL)
		{
			nextNode(temp)->prev = prevNode(temp);
			prevNode(temp)->next = nextNode(temp);
		}
		else if (nextNode(temp) == NULL)
		{
			tail = prevNode(temp);
			tail->next = NULL;
		}
		else
		{
			head = nextNode(temp);
			head->prev = NULL;
		}
		delete temp;
		size--;
		cout << object << " has been deleted. Current list size is " << size << endl;
	}
}
template <class T>
void LinkedList<T>::clearList()
{
	node<T> * temp = head;
	if (head != NULL)
	{
		for (int i = 1; i < size; i++)
		{
			temp = nextNode(temp);
			delete temp->prev;
		}
		delete temp;
		//reset list properties
		size = 0;
		head = NULL;
		tail = NULL;
	}
}

//returns null if not found
template <class T>
node<T>* LinkedList<T>::search(T thing)
{
	node<T>* temp = head;
	while (temp != NULL)
		if (thing == temp->object)
			return temp;
		else
			temp = nextNode(temp);
	return temp; // null
}


template <class T>
void LinkedList<T>::print(std::ostream& out)
{
	node<T>* temp = head;
	for (int i = 1; i <= size; i++)
	{
		out << i << ": " << temp->object << endl;
		temp = nextNode(temp);
	}
}


#endif