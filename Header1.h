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
};

struct Semester
{
	int order;
	int yearStart;
	int yearEnd;
	Date startDate;
	Date endDate;
};

bool loginSystem(string fname, string& email);
void changePassword(string fname, string email);