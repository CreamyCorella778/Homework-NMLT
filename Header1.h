#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <math.h>
#include <fstream>

using namespace std;

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

struct Course
{
	string id;
	string name;
	string lop;
	int maxStu;
	int dayInWeek;
	int session;
};

struct Staff
{
	string name;
	string email;
	string address;
	Course* currentCourse;
};

struct Student
{
	int no;
	string stuID;
	string firstName;
	string lastName;
	bool gender; //true = male, false = female
	Date birth;
	string socialID;
	string eduProgr;
	Class cls;
	void addClass(Class a)
	{
		this->cls = a;
	}
};

struct Semester
{
	int order;
	SchoolYear sy;
	Date startDate;
	Date endDate;
};

bool loginSystem(string fname, string& email);
void changePassword(string fname, string email);
int countLinesInCSV(string fname);

//---------------------------------------------------------------------

SchoolYear createSchoolYear(int yearStart, int yearEnd);
void getClassIn4(SchoolYear& sy, string& eduProg, int& start, int& end);
Class* createClasses(SchoolYear sy, string eduProg, int start, int end);
Student* addStudentsFromCSV(string fname, int& n);