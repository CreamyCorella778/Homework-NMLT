#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Header2.hpp"
using namespace std;

template <class a>
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

template <class T>
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
	float semGPA;
	float GPA;
};

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

struct Scoreboard4Class
{
	Class cls;
	float* Final;
	float* semGPA;
	float* overallGPA;
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
	char* id;
	char* courseName;
	Node<Staff>* teacher;
	int credits;
	int capacity;
	Node<Class>* lop;
	int dayInWeek;
	int session;
	Node<Semester>* sem;
};

struct System
{
	LList<Course>* allCourse; // LList[0] = Semester 1, LList[1] = Semester 2, LList[2] = Semester 3
	LList<Class> allClass;
	LList<Staff> allStaff;
	LList<Semester> allSemester;
}systems;

bool loginSystem(string fname, string& email);
void changePassword(string fname, string email);
void printProfileIn4(string email);

//---------------------------------------------------------------------

void getYears(int& yearStart, int& yearEnd);
SchoolYear createSchoolYear(string schy);
SchoolYear createSchoolYear(int yearStart, int yearEnd);
void getClassIn4(SchoolYear& sy, string& eduProg, int& start, int& end);
Class* createClasses(SchoolYear sy, string eduProg, int start, int end);
bool addStudentToClass(Student stu, Class &cl);
bool addStudentsToClass(string fname);

//----------------------------------------------------------------------

void getSemesterIn4(int& no, SchoolYear& sy, Date& sd, Date& ed);
Semester createSemester(int no, SchoolYear sy, Date sd, Date ed);
void getCourseIn4(Course& a, Semester sem);
bool addCoursetoSemester(Course a, Semester sem);
void viewCourses(Semester sem);
void getIn4toUpdateCourse(string& courseID, string& cl, int& option);
CourseVarType getIn4toUpdateCourse(int option);
bool updateCourseIn4(string courseID, string cl, int option, CourseVarType in4, Semester sem);
void getStudentIn4(Student& a);
bool addStudentToCourse(Student st, Course& c);
bool addStudentsToCourse(string fname, Course &cour);
bool removeStudentFromCourse(Student st, Course& c);
bool removeCourse(Course c, Semester sem);

//----------------------------------------------------------------------

void viewCourses(Student stu, Semester sem);

//----------------------------------------------------------------------

void viewClasses();
void viewStudents(Class a);
void viewAllCourses();
void viewCourses(Semester sem);
void viewStudents(Course a);
void viewStaff(Staff a);

//----------------------------------------------------------------------

bool writeStudentsInCourse(string fname, Course cour);
bool readScoreBoard(string fname);
void viewScoreBoards(Course a);
void getUpdateScbIn4(Student a, Course& cour, int*& option, float*& in4, int& n, int& semNum);
bool updateScoreBoard(Student& stu, Course cour, int* option, float* in4, int n);
void viewScoreBoards(Class cl, Semester sem);
void viewGPAInSemester(Class cl, Semester sem);
void viewOverallGPAInClass(Class cl, Semester currentSem);

//----------------------------------------------------------------------

void viewScoreboards(Student a);

//----------------------------------------------------------------------

void viewStudent(Student a);
void viewStaff(Staff a);

#include "Source4.cpp"