#pragma once
#include <string>
#include <cstring>
#include <cmath>
#include "Header1.hpp"
//#include "Source4.cpp"
//#include "Source9.cpp"
using namespace std;

struct Date;
template <class a>
struct Node;
template <class T>
struct LList;
struct SchoolYear;
struct Semester;
struct Student;
struct Scoreboard4Class;
struct Staff;
union CourseVarType;
struct Class;
struct Course;
struct Scoreboard;


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

int testing1(int &userType, string &email);
int testing2(string &email);
int testing3(string& email);
int testing4(Semester currSem, string email);
int testing5(string email, SchoolYear &sy);
int testing6(string email, Semester currSem);

//======================================================================

void initSystems();
template <class a>
void addLast(LList<a> l, Node<a>* insert);
template <class a>
int countNodes(Node<a>* head);
template <class a>
void removeRandomNode(LList<a> l, a data);
template <class a>
Node<a>* findNode(LList<a> l, a data);
template <class a>
Node<a>* findNodeByIndex(LList<a> l, int index);

//------------------------------------------------------------------------

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
Node<Semester>* identifySemesterByToday(Date today);
int compareDate(Date dey1, Date dey2) ;
SchoolYear extractSchoolYear(string fname);
Date* divideSemester(Semester sem);
Node<Student>* extractStudentFromEmail(string email);
Date getTodayIn4();
void viewSemester(Semester sem);
float calculateOverallGPA(Student &stu, Semester currentSem);
float calculateSemGPA(Student &stu);
string generateFileName(Course c, Class cl, Semester sem);
string generateFileName(Class cl, Semester sem);
