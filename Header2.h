#pragma once
#include "Header1.h"

void initSystems();
template <class a>
void addLast(LList<a> l, Node<a>* insert);
template <class a>
int countNodes(Node<a>* head);
template <class a>
void removeRandomNode(LList<a> l, a data);
template <class a>
Node<a>* findNode(LList<a> l, a data);

//------------------------------------------

int countLinesInCSV(string fname);
Date getNS(string birth);
void getYears(int& yearStart, int& yearEnd);
Class createClass(string cl);
void viewCourse(Course a);

#include "Source4.cpp"