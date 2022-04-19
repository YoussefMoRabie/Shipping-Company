#pragma once
template<class Type>
class PriNode
{

	private:
		Type item;
		int Priority;
		PriNode<Type>* next;
	public:
		PriNode() :next(nullptr)
		{
			Priority = 0;
		}
		PriNode(const Type anitem)
		{
			item = anitem;
			next = nullptr;
			Priority = 0;
		}
		PriNode(const Type anitem, PriNode<Type>* nextptr)
		{
			item = anitem;
			next = nextptr;
			Priority = 0;
		}
		void set_item(const Type anitem) { item = anitem; }
		void set_next(PriNode<Type>* nextptr) { next = nextptr; }
		void set_priority(int p)
		{
			Priority = p;
		}

		Type get_item()const { return item; }
		PriNode<Type>* get_next()const { return next; }
		int get_priority()
		{
			return Priority;
		}

	};



