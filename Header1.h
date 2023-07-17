#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Header2.h"

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

struct Semester
{
	int number;
	SchoolYear sy;
	Date startDate;
	Date endDate;
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
};

struct Class
{
	SchoolYear year;
	string eduProgr;
	int no;
	string cls;
	LList<Student> stuList;
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
};

struct System
{
	LList<Course>* allCourse; // LList[0] = Semester 1, LList[1] = Semester 2, LList[2] = Semester 3
	LList<Class> allClass;
}systems;

bool loginSystem(string fname, string& email);
void changePassword(string fname, string email);

//---------------------------------------------------------------------

SchoolYear createSchoolYear(int yearStart, int yearEnd);
void getClassIn4(SchoolYear& sy, string& eduProg, int& start, int& end);
Class* createClasses(SchoolYear sy, string eduProg, int start, int end);
Student* addStudentsFromCSV(string fname, int& n);

//----------------------------------------------------------------------

void getSemesterIn4(int& no, SchoolYear& sy, Date& sd, Date& ed);
Semester createSemester(int no, SchoolYear sy, Date sd, Date ed);
void getCourseIn4(Course& a);
void addCoursetoSemester(Course a, Semester sem);
void viewCourses(Semester sem);
void getIn4toUpdateCourse(string& courseID, string& cl);
void updateCourse(string courseID, string cl, Semester sem);
void getStudentIn4(Student& a);
void addStudentToCourse(Student st, Course& c);
void removeStudentFromCourse(Student st, Course& c);
void removeCourse(Course c, Semester sem);

//----------------------------------------------------------------------


#include "Source4.cpp"