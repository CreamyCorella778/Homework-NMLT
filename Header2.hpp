#pragma once
#include <string>
#include <cstring>
#include <cmath>
#include "Header1.hpp"
#include "Source4.cpp"
#include "Source9.cpp"
using namespace std;

struct Class;
struct Scoreboard;
struct Course;
struct Date;

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
Node<Student>* findStudent(string id);
bool writeAllCoursesOfStudent(string fname);

