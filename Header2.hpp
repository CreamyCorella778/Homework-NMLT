#pragma once
#include <string>
#include <cstring>
#include <cmath>
#include "Header1.hpp"
//#include "Source4.cpp"
//#include "Source9.cpp"
using namespace std;

template <class a>
struct Node;
template <class T>
struct LList;
struct Date;
struct SchoolYear;
struct Semester;
struct Staff;
struct Class;
struct Course;
struct Student;
struct Scoreboard;
struct Scoreboard4Class;
union CourseVarType;
struct System;


bool loginSystem(string fname, string& email);
bool changePassword(string fname, string email);
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
bool updateCourseIn4(Course &course, int option, CourseVarType in4);
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
void getUpdateScbIn4(int*& option, float*& in4, int& n);
bool writeGPAofClassInSem(string fname, Class cl, Semester sem);
bool updateScoreBoard(Student& stu, Course& cour, Semester currSem, int* option, float* in4, int n);
void viewScoreBoards(Class cl, Semester sem);
void viewGPAInSemester(Class cl, Semester sem);
void viewOverallGPAInClass(Class cl, Semester currentSem);

//----------------------------------------------------------------------

void viewScoreboards(Student a);

//----------------------------------------------------------------------

void viewStudent(Student a);
void viewStaff(Staff a);

//----------------------------------------------------------------------

bool readStaffList(string fname);
bool readAllSemester(string fname);
bool readAllClasses(string fname);
bool readAllCoursesOfStudent(string fname);
bool readAllCourses(string fname);


//----------------------------------------------------------------------

bool writeAllCoursesOfStudent(string fname);
bool writeAllCourses(string fname);


//----------------------------------------------------------------------

int testing1(int &userType, string &email);
int testing2(string email);
int testing3(string& email);
int testing4(string email, Semester currSem);
int testing5(string email, SchoolYear &sy);
int testing6(string email, Semester currSem);
int testing7(string email, Semester currSem);

//---------------------------------------------------------------------

int task1(string email);
void task2();
bool task3(Semester currSem);
bool task4(Semester currSem);
Node<Course>* task3_5(Semester currSem);
bool task5(Semester currSem);
bool task6(Semester currSem);
bool task7(Semester currSem);
bool task8(Semester currSem);
bool task9();
bool task10(Semester currSem);
void task11(SchoolYear &sy);
void task12(SchoolYear &sy);
bool task13();
bool task14();
bool task15(Semester currSem);
bool task16();
bool task17(Semester currSem);
bool task18(Semester currSem);
bool task19(Semester currSem);

//---------------------------------------------------------------------

void main1();
void main2();
void main3();

//======================================================================

void initSystems();
template <class a>
void addLast(LList<a>& l, Node<a>* insert);
template <class a>
int countNodes(Node<a>* head);
template <class a>
void removeRandomNode(LList<a>& l, a data);
template <class a>
Node<a>* findNode(LList<a> l, a data);
template <class a>
Node<a>* findNodeByIndex(LList<a> l, int index);

//------------------------------------------------------------------------

int countLinesInCSV(string fname);
Date getNS(string birth);
void getYears(int& yearStart, int& yearEnd);
Class createClass(string cl);
Class createCLass(string fname);
void viewCourse(Course a);
string* extractCId_cl_sno(string fname);
void viewScoreBoards(Course a);
Node<Class>* findCLass(string name);
Node<Course>* findCourse(string courseID, string className, int semNum);
Node<Staff>* findStaff(string id);
void countNoInStudentList(LList<Student>& l);
bool writeAllCourses(string fname);
Node<Class>* findCLass(string name);
Node<Student>* findStudent(string id);
Node<Semester>* identifySemesterByToday(Date today);
int compareDate(Date dey1, Date dey2) ;
SchoolYear extractSchoolYear(string fname);
Date* divideSemester(Semester sem);
Node<Student>* extractStudentFromEmail(string email);
Date getTodayIn4();
void viewSemester(Semester sem);
void viewScoreBoard(Scoreboard a);
float calculateOverallGPA(Student &stu, Semester currentSem);
float calculateSemGPA(Student &stu);
string generateFileName(Course c, Class cl, Semester sem);
string generateFileName(Class cl, Semester sem);
LList<Course> findCoursesOfClass(Class cl, Semester sem);
float* countOverallGPAInClass(Class cl, Semester currentSem);
