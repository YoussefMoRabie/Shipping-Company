/**
 * @file Node.h
 * @version 0.1
 * @copyright Copyright secured by YMY Team(c) 2022
 */
#pragma once
template<class Type>
class Node
{
private:
	Type item;
	int Priority;
	Node<Type>* next;
public:
	Node() :next(nullptr)
	{
	}
	Node(const Type anitem)
	{
		item = anitem;
		next = nullptr;
	}
	Node(const Type anitem, Node<Type>* nextptr)
	{
		item = anitem;
		next = nextptr;
	}
	void set_item(const Type anitem) { item = anitem; }
	void set_next(Node<Type>* nextptr) { next = nextptr; }

	Type get_item()const 
	{
		return item;
	}
	Node<Type>* get_next()const { return next; }


};
