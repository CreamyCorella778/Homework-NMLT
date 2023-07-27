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

struct Class;
struct Scoreboard;
struct Course;

struct Date
{
	int day;
	int month;
	int year;
	bool isEqual(Date another)
	{
		return this->day == another.day && this->month == another.month && this->year == another.year;
	}
};

struct SchoolYear
{
	int yStart;
	int yEnd;
	string schYr;
	bool isEqual(SchoolYear another)
	{
		return this->yStart == another.yStart && this->yEnd == another.yEnd && this->schYr == another.schYr;
	}
};


struct Semester
{
	int number;
	SchoolYear sy;
	Date startDate;
	Date endDate;
	bool isEqual(Semester another)
	{
		return this->number == another.number && this->sy.isEqual(another.sy) && this->startDate.isEqual(another.startDate) && this->endDate.isEqual(another.endDate);
	}
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
	Class cl;
	LList<Course> courses;
	LList<Scoreboard> marks;
};

struct System
{
	LList<Course>* allCourse; // LList[0] = Semester 1, LList[1] = Semester 2, LList[2] = Semester 3
	LList<Class> allClass;
	LList<Staff> allStaff;
}systems;

bool loginSystem(string fname, string& email);
void changePassword(string fname, string email);

//---------------------------------------------------------------------

void getYears(int& yearStart, int& yearEnd);
SchoolYear createSchoolYear(string schy);
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

//----------------------------------------------------------------------

void viewStudent(Student a);
void viewStaff(Staff a);

#include "Source4.cpp"