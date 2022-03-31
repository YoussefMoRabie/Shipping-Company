#include"Node.h"
#include <cassert>

template <class T>
class Stack
{
	Node<T>* Head;

	void copyStack(const Stack<T>& R) {
		if (R.Head == NULL)
		{
			IntializeStack();
			return;
		}
		if (R.Head == Head)
			return;
		IntializeStack();
		Node<T>* ptr;
		Node<T>* Rptr;
		Head = new Node<T>;
		Head->setitem(R.Head->getitem());
		ptr = Head;
		Rptr = R.Head->getnext();
		while (Rptr) {
			ptr->getnext() = new Node<T>;
			ptr = ptr->getnext();
			ptr->setitem(Rptr->getitem());
			Rptr = Rptr->getnext();

		}
		ptr->setnext(NULL);
	}
public:
	Stack() {
		Head = NULL;
	}
	Stack(const Stack<T>& R) {
		Head = NULL;
		copyStack(R);

	}
	void IntializeStack() {
		if (Head == NULL)
			return;
		Node<T>* ptr = Head;
		Node<T>* nextptr;


		while (ptr) {
			nextptr = ptr->getnext();
			delete ptr;
			ptr = nextptr;
		}
		Head = NULL;
	}
	bool IsEmptyStack() {
		return (Head == NULL);
	}

	const Stack<T>& operator =(const Stack<T>& R) {
		copyStack();
		return *this;

	}
	void Push(T data) {
		Node <T>* ptr = new Node<T>(data);
		if (Head == NULL)
		{
			Head = ptr;
			Head->setnext(NULL);
			return;
		}

		ptr->setnext(Head);
		Head = ptr;
	}

	bool Pop() {
		if (IsEmptyStack())
			return false;
		Node <T>* ptr = Head;
		Head = Head->getnext();
		delete ptr;
		return true;
	}
	const T& Top() {
		assert(Head != NULL);
		return Head->getitem();
	}
	~Stack() {
		IntializeStack();
	}
};

