#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <math.h>
#include <fstream>

using namespace std;

template <typename a>
struct Node
{
	a data;
	Node* next;
	void init(a dat)
	{
		this->data = dat;
		this->next = nullptr;
	}
};

template <typename T>
struct LList
{
	Node<T>* head;
	Node<T>* tail;
	void init()
	{
		this->head = this->tail = nullptr;
	}
};

struct Date
{
	int day;
	int month;
	int year;
};

struct SchoolYear
{
	int yStart;
	int yEnd;
	string schYr;
};

struct Class
{
	SchoolYear year;
	string eduProgr;
	int no;
	string cls;
};

struct Semester
{
	int number;
	SchoolYear sy;
	Date startDate;
	Date endDate;
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
	void addCourse(Semester sem)
	{
		this->sem = sem;
	}
};

struct Staff
{
	string name;
	string email;
	string address;
};

struct Student
{
	int no;
	string stuID;
	string firstName;
	string lastName;
	bool gender; // true = male, false = female
	Date birth;
	string socialID;
	Class cls;
	void addClass(Class a)
	{
		this->cls = a;
	}
};

struct System
{
	LList<Course> allCourse;
	LList<Class> allClass;
	LList<Student> allStudent;
}system;

bool loginSystem(string fname, string& email);
void changePassword(string fname, string email);

//---------------------------------------------------------------------

SchoolYear createSchoolYear(int yearStart, int yearEnd);
void getClassIn4(SchoolYear& sy, string& eduProg, int& start, int& end);
Class* createClasses(SchoolYear sy, string eduProg, int start, int end);
Student* addStudentsFromCSV(string fname, int& n);

//----------------------------------------------------------------------


