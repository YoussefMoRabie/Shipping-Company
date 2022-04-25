#pragma once
#include"Node.h"
#include <iostream>
using namespace std;
#include "Cargo.h"
#include "Truck.h"
template<class Type>
class LinkedList
{
private:
	int count;
	Node<Type>* First;
	Node<Type>* End;
public:
	LinkedList()
	{
		First = NULL;
		End = NULL;
		count = 0;
	}
	void InsertBegin(Type item)
	{
		Node<Type>* temp;
		temp = new Node<Type>;
		temp->set_item(item);
		if (IsEmpty())
			End = temp;
		else
		temp->set_next(First);
		First = temp;
		count++;
	}
	bool InsertIndex(Type item, int index)
	{
		if (index <= count && index >= 0)
		{
			if (index == 0)
				InsertBegin(item);
			else if (index == count)
				InsertEnd(item);
			else
			{
				Node<Type>* temp;
				temp = new Node<Type>;
				Node<Type>* cur = First;
				for (int i = 0; i < index - 1; i++)
					cur = cur->get_next;
				temp->set_next(cur->get_next());
				cur->set_next(temp);
				count++;
			}
			return true ;
		}
		else
		return false;
	}
	void InsertEnd(Type item)
	{
		Node<Type>* temp;
		temp = new Node<Type>;
		temp->set_item(item);
		if (IsEmpty())
			First = temp;
		else
			End->set_next(temp);
		End = temp;
		count++;
	}
	Type getFirst()
	{
		return First->get_item();
	}

	Type getEnd()
	{
		return End->get_item();
	}

	bool IsEmpty()
	{
		return !count;
	}

	int GetCount()
	{
		return count;
	}
	bool removeFirst()
	{
		if (count == 0)
			return false;
		Node<Type>* delptr;
		delptr = First;
		if (count == 1)
		{
			First = NULL;
			End = NULL;
		}
		else
		{
			First= First->get_next();
		}
		delptr->set_next(nullptr);
		count--;
		return true;
	}
	void print();

};

template<class Type>
inline void LinkedList<Type>::print()
{
}
template<>
inline void LinkedList<Cargo*>::print()
{
	Node<Cargo*>* temp = First;
	while (temp)
	{
		cout << temp->get_item()->GetID();
		temp = temp->get_next();
		if (temp)
			cout << ',';
	}
}
template<>
inline void LinkedList<Truck*>::print()
{
	Node<Truck*>* temp = First;
	while (temp)
	{
		cout << temp->get_item()->GetID() ;
		temp = temp->get_next();
		if (temp)
			cout << ',';
	}
}