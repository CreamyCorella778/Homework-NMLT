#pragma once
#include <string>
#include <cstring>
#include <math.h>
#include "Header1.h"
#include "Source4.cpp"
#include "Source9.cpp"
using namespace std;

struct Class;
struct Scoreboard;
struct Course;
struct Date;

struct Class
{
	SchoolYear year;
	string eduProgr;
	int no;
	string cls;
	LList<Student> stuList;
	bool isEqual(Class another)
	{
		return (this->year.isEqual(another.year)) && (this->eduProgr == another.eduProgr) && this->no == another.no && this->cls == another.cls;
	}
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

struct Staff
{
	string firstName;
	string lastName;
	string id;
	LList<Course> courses;
};

struct Course
{
	string id;
	string courseName;
	Staff teacher;
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

union CourseVarType
{
	string id;
	string courseName;
	Node<Staff>* teacher;
	int credits;
	int capacity;
	Node<Class>* lop;
	int dayInWeek;
	int session;
	Node<Semester>* sem;
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
void viewScoreBoards(Course a);
Node<Class>* findCLass(string name);
bool findCourse(string courseID, string className, int semNum, Course& found);
Node<Staff>* findStaff(string id);
void countNoInStudentList(LList<Student>& l);
bool writeAllCourses(string fname);
Node<Class>* findCLass(string name);
