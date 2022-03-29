#pragma once
template<class Type>
class Node
{
private:
	Type item;
	Node<Type>* next;
public:
	Node() :next(nullptr)
	{}
	Node(const Type anitem)
	{
		item = anitem;
		next = nullptr;
	}
	Node(const Type anitem, Node* nextptr)
	{
		item = anitem;
		next = nextptr;
	}
	void set_item(const Type anitem) { item = anitem; }
	void set_next(Node* nextptr) { next = nextptr; }
	Type get_item()const { return item; }
	Node<Type>* get_next()const { return next; }

};

