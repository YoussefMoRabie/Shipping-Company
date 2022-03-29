#include<iostream>
#include"Node.h"
#include"Queue.h"
using namespace std;
int main()
{
	Queue<int> q;
	q.EnQueue(5);
	q.EnQueue(3);
	q.EnQueue(4);
	q.EnQueue(0);
	q.EnQueue(-1);
	q.print();
	cout << "=============================================================" << endl;
	q.EnQueue(12, 3);
	q.EnQueue(77, 2);
	q.EnQueue(109, 3);
	q.print();
}