#pragma once
#include "Header1.hpp"
#include "Header2.hpp"

template <class a>
void addLast(LList<a>& l, Node<a>* insert)
{
	if (l.head == l.tail && l.head == nullptr)
		l.head = l.tail = insert;
	else
	{
		l.tail->next = insert;
		l.tail = insert;
	}
}

template <class a>
int countNodes(Node<a>* head)
{
	if (head == nullptr)
		return 0;
	else
		return 1 + countNodes(head->next);
}

template <class a>
void removeRandomNode(LList<a>& l, Node<a>* &i)
{
	if (!i)
		return;
	else if (i == l.head)
		l.head = i->next;
	else
	{
		Node<a>* i_prev = l.head;
		for (i_prev; i_prev->next != i; i_prev = i_prev->next);
		i_prev->next = i->next;
		i->next = nullptr;
	}
	delete i;
	i = nullptr;
}

template <class a>
Node<a>* findNode(LList<a> l, a data)
{
	Node<a>* i = l.head;
	for (i; i != nullptr; i = i->next)
		if (i->data.isEqual(data))
			return i;
	return nullptr;
}

template <class a>
Node<a>* findNodeByIndex(LList<a> l, int index)
{
	Node<a>* i = l.head; int j = 0;
	if ((!l.head && !l.tail) || index < 0 || index + 1 > countNodes(l.head))
		return nullptr;
	for (i, j; i && j < index; i = i->next, ++j)
		continue;
	return i;
}