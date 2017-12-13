// File: Set.h
//	Programmer: Tabitha Roemish
//	Date: 10/30/2017
//	File includes:
//		Set class declaration and definitions

#ifndef SET_H
#define SET_H
#define PRINT_POP 3
#include "LinkedList.h"
using namespace std;
template <class T>
class Set : public LinkedList<T>
{

public:
	Set() : LinkedList<T>() {};
	Set(LinkedList<T>& list);
	virtual ~Set() {LinkedList<T>::clearList();};
	void insert(T object);
	void printPopular(std::ostream& out);
	void print(std::ostream& out);
	int getCount(T object); 
	void sort();
private:
	// sort by count
	node<T>* mergeList(node<T>* a, node<T>* b);
	node<T>* mergeSort(node<T>* hd);
	int listLength(node<T>* hd);
	
};

template <class T>
std::ostream& operator<<(std::ostream& out, Set<T>& st)
{
	st.print(out);
	return out;
}

// Set definitions------------------------------
template <class T>
Set<T>::Set(LinkedList<T>& list)
{
	node<T> * curr = list.getHead();
	while(curr != NULL)
	{
		insert(curr->object);
		curr = LinkedList<T>::nextNode(curr);
	}
}

template <class T>
void Set<T>::insert(T object)
{
	node<T>* temp = LinkedList<T>::search(object);
	if (temp == NULL)
	{
		LinkedList<T>::insert(object); 
	}
	else
		temp->Count++;
}

template <class T>
int Set<T>::getCount(T object)
{
	node<T>* temp = LinkedList<T>::search(object);
	if(temp != NULL)
		return temp->Count;
	else
	{
		cout << "Item not found";
		return 0;
	}
}

template <class T> // O(n) to set list after sort
void Set<T>::sort()
{
	int count = 0;
	node<T>* temp = mergeSort(LinkedList<T>::getHead());
	LinkedList<T>::setHead(temp);
	while (temp != NULL)
	{
		count++;
		if (temp->next != NULL)
			temp->next->prev = temp;
		LinkedList<T>::setTail(temp);
		temp = temp->next;
	}
	LinkedList<T>::setSize(count);
}

template <class T> // O(log n) - recursively merges different sized lists
node<T>* Set<T>::mergeList(node<T>* a, node<T>* b)
{
	node<T>* curr = NULL;
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	if (a->Count > b->Count)
	{
		curr = b;
		curr->next = mergeList(a, b->next);
	}
	else
	{
		curr = a;
		curr->next = mergeList(a->next, b);
	}
	return curr; // returns a node with all nexts set in order
}

template <class T>
int Set<T>::listLength(node<T>* hd)
{
	int count = 0;
	node<T>* temp = hd;
	while (hd != NULL)
	{
		count++;
		hd = hd->next;
	}
	return count;
}

template <class T> // O(log n) / recursively splits list into halves 
node<T>* Set<T>::mergeSort(node<T> * hd)
{
	node<T>* old = hd;
	int mid = listLength(hd) / 2;
	if (hd->next == NULL)
		return hd;
	while (mid - 1 > 0)
	{
		old = old->next;
		mid--;
	}
	node<T>* newOld = old->next;
	old->next = NULL;
	old = hd;
	//recursivley split lists
	node<T>* lst1 = mergeSort(old);
	node<T>* lst2 = mergeSort(newOld);
	//recursivley merge lists back together
	return mergeList(lst1, lst2);
}

template <class T>
void Set<T>::print(std::ostream& out)
{
	node<T>* temp = LinkedList<T>::getHead();
	for (int i = 1; i <= LinkedList<T>::getSize(); i++)
	{
		out << i << ": " << temp->object << " - " << temp->Count << endl;
		temp = LinkedList<T>::nextNode(temp);
	}
}

template <class T>
void Set<T>::printPopular(std::ostream& out)
{
	sort();
	node<T>* temp = LinkedList<T>::getTail();
	if (LinkedList<T>::getSize() >= PRINT_POP)
	{
		for (int i = 1; i<=PRINT_POP; i++)
		{
			out << i << ": " << temp->object << " - " << temp->Count << endl;
			temp = LinkedList<T>::prevNode(temp);
		}
	}
	else
		print(out);
}
#endif
