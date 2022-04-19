#pragma once
#include "PriNode.h"
#include<iostream>

template<class Type>
class PriQueue 
{

private:
	PriNode<Type>* front;
	int count;
	PriNode<Type>* rear;
public:
	PriQueue()
	{
		front = nullptr;
		rear = nullptr;
		count = 0;
	}
	bool EnQueue(Type item, float priority = 0)
	{
		PriNode<Type>* temp;
		PriNode<Type>* cur = front;
		temp = new PriNode<Type>;
		temp->set_item(item);
		temp->set_priority(priority);
		if (QueueEmpty())
		{
			front = temp;
			rear = temp;

		}
		else if (front->get_priority() < priority)
		{
			temp->set_next(front);
			front = temp;
		}
		else
		{
			while (cur->get_next() != NULL && cur->get_next()->get_priority() >= priority)
				cur = cur->get_next();
			if (!cur->get_next())
				rear = temp;
			temp->set_next(cur->get_next());
			cur->set_next(temp);

		}

		count++;
		return true;

	}
	bool DeQueue()
	{
		if (count == 0)
			return false;
		PriNode<Type>* delptr;
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
		delete delptr;
		count--;
		return true;
	}
	bool QueueEmpty()
	{
		return !count;
	}
	void DistroyQueue()
	{
		int c = count;
		for (int i = 0; i < c; i++)
			DeQueue();
	}
	PriNode<Type>* GetFront()
	{
		return front;
	}
	PriNode<Type>* GetRear()
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

	~PriQueue()
	{
		DistroyQueue();
	}

	void print()
	{
		PriNode<Type>* temp = front;
		while (temp)
		{
			cout << temp->get_item();
			temp = temp->get_next();
			if (temp)
				cout << ',';
		}
	}
};



