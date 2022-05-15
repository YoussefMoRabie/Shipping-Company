#pragma once
#include"Node.h"
#include <iostream>
using namespace std;

template<class Type>
class Queue
{
private:
	Node<Type>* front;
	int count;
	Node<Type>* rear;
public:
	Queue()
	{
		front = nullptr;
		rear = nullptr;
		count = 0;
	}
	 bool EnQueue(Type item)
	{
		Node<Type>* temp;
		temp = new Node<Type>;
		temp->set_item(item);
		if (QueueEmpty())
			front = temp;
		else
			rear->set_next(temp);

		rear = temp;
		count++;
		return true;

	}
	bool DeQueue(Type& x)
	{
		if (count == 0)
			return false;
		Node<Type>* delptr;
		delptr = front;
		if (count == 1)
		{
			rear = NULL;
			front = NULL;
		}
		else
		{
			front = front->get_next();
		}
		delptr->set_next(nullptr);
		x = delptr->get_item();
		count--;
		return true;
	}
	bool QueueEmpty()
	{
		return !count;
	}
	void DistroyQueue()
	{
		Type x;
		int c = count;
		for (int i = 0; i < c; i++)
			DeQueue(x);
	}
	Node<Type>* GetFront()
	{
		return front;
	}
	Node<Type>* GetRear()
	{
		return rear;
	}
	int GetCount()
	{
		return count;
	}
	Type Peek()
	{
		if (!QueueEmpty())
			return front->get_item();
		else
			return NULL;
	}
	
	~Queue()
	{
		DistroyQueue();
	}

	void print()
	{
		Node<Type>* temp = front;
		while (temp)
		{
			cout << temp->get_item();
			temp = temp->get_next();
			if (temp)
				cout << ',';
		}
	}
};

