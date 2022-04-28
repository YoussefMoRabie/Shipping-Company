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
	bool Find_Remove(Type val,Type& x)
	{
		Node<Type>* prev = NULL;
		Node<Type>* ptr = First;
		while (ptr)
		{
			if (*(ptr->get_item()) == val)
			{
				if (prev == NULL)
				{
					x = ptr->get_item();
					First = First->get_next();
				}
				else
				{
					x = ptr->get_item();
					prev->set_next(ptr->get_next());
				}
				count--;
				return true;
			}
			prev = ptr;
			ptr = ptr->get_next();
		}
		return false;
	}

	bool removeFirst(Type& x)
	{
		if (count == 0)
			return false;

		Node<Type>* ptr;
		ptr = First;
		if (count == 1)
		{
			First = NULL;
			End = NULL;
		}
		else
		{
			First= First->get_next();
		}
		x = ptr->get_item();
		count--;
		return true;
	}
	void print()
	{
		Node<Type>* temp = First;
		while (temp)
		{
			cout << (temp->get_item());
			temp = temp->get_next();
			if (temp)
				cout << ',';
		}
	}

};
