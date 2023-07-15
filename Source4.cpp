#include "Header1.h"

template <class a>
void addLast(LList<a> l, Node<a>insert)
{
	if (l.head == l.tail && l.head == nullptr)
		l.head = l.tail = insert;
	else
	{
		l.tail->next = insert;
		l.tail = insert;
	}
}

