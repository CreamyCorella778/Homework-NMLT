#pragma once
#include <string>
#include <cstring>
#include <math.h>
#include "Header1.h"

struct Class
{
	SchoolYear year;
	string eduProgr;
	int no;
	string cls;
	LList<Student> stuList;
};

struct Scoreboard
{
	Student student;
	Course course;
	float Total;
	float Final;
	float midTerm;
	float Other;
};

struct Course
{
	string id;
	string courseName;
	string teacher;
	int credits;
	int capacity;
	Class lop;
	int dayInWeek;
	int session;
	/* sess 1 starts at 7:30
	*  sess 2 starts at 9:30
	*  sess 3 starts at 13:30
	*  sess 4 starts at 15:30 */
	Semester sem;
	LList<Student> stuList;
	LList<Scoreboard> score;
};

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
string* extractCId_cl_sno(string fname);

#include "Source4.cpp"