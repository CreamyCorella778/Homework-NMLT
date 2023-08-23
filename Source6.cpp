#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

void viewClasses()
{
	for (Node<Class>* i = systems.allClass.head; i != nullptr; i = i->next)
	{
		cout << i->data.cls;
		if (i->next != nullptr && i->data.eduProgr.compare(i->next->data.eduProgr) != 0)
			cout << endl;
		else
			cout << ", ";
	}
	cout << endl << endl;
}


void viewStudent(Student a)
{
	cout << "Sinh vien " << a.firstName << " " << a.lastName << " co ma so sinh vien "
		<< a.stuID;
	cout << ", gioi tinh " << (a.gender ? "nam " : "nu ");
	cout << ", ngay sinh: " << a.birth.day << "/" << a.birth.month << "/" << a.birth.year;
	cout << ", ma so can cuoc cong dan la " << a.socialID;
	cout << endl;
}

void viewStudents(Class a)
{
	for (Node<Student>* i = a.stuList.head; i != nullptr; i = i->next)
		viewStudent(i->data);
	cout << endl << endl;
}

void viewAllCourses()
{
	for (int index = 0; index < 3; ++index)
	{
		cout << "Danh sach cac hoc phan cua hoc ki " << index + 1;
		for (Node<Course>* i = systems.allCourse[index].head; i != nullptr; i = i->next)
			viewCourse(i->data);
		cout << endl;
	}
}

void viewStudents(Course a)
{
	for (Node<Student>* i = a.stuList.head; i != nullptr; i = i->next)
		viewStudent(i->data);
	cout << endl << endl;
}

void viewStaff(Staff a)
{
	cout << "Giang vien " << a.firstName << " " << a.lastName << ", ma so " << a.id << endl;
}

void viewCourse(Course a)
{
	cout << a.id
		<< " - " << a.courseName
		<< ", cua giang vien " << a.teacher.firstName << " " << a.teacher.lastName
		<< ", lop " << a.lop.cls << ", " << a.credits
		<< " tin chi, toi da " << a.capacity << " hoc sinh, thoi gian: thu "
		<< a.dayInWeek << ", tiet " << a.session << ", hoc ki " << a.sem.number << endl;
}

void viewCourses(Semester sem)
{
	cout << "Cac khoa hoc cua hoc ki " << sem.number << ", nam hoc " << sem.sy.schYr << ":" << endl;
	for (Node<Course>* i = systems.allCourse[sem.number - 1].head; i ; i = i->next)
		viewCourse(i->data);
	cout << endl << endl;
}

void viewCourses(Student stu, Semester sem)
{
	cout << "Cac khoa hoc cua hoc sinh " << stu.firstName << " " << stu.lastName
		<< " trong hoc ki " << sem.number << ":" << endl;
	for (Node<Course>* i = stu.courses.head; i; i = i->next)
		viewCourse(i->data);
}

void viewScoreBoard(Scoreboard a)
{
	cout << fixed << setprecision(3);
	cout << "Diem giua ky: " << a.midTerm << endl;
	cout << "Diem cuoi ky: " << a.Final << endl;
	cout << "Diem khac: " << a.Other << endl;
	cout << "Diem tong: " << a.Total << endl;
}

void viewScoreboards(Student a)
{
	cout << "Bang diem cua sinh vien " << a.firstName << " " << a.lastName << ", ma so " << a.stuID << ":" << endl;
	for (Node<Scoreboard>* i = a.marks.head; i != nullptr; i = i->next)
	{
		cout << "Hoc phan " << i->data.course.courseName << ":" << endl;
		viewScoreBoard(i->data);
	}
}

void viewScoreBoards(Course a)
{
	cout << "Bang diem cua hoc phan " << a.courseName << " cua lop " << a.lop.cls << ":" << endl;
	for (Node<Scoreboard>* i = a.score.head; i != nullptr; i = i->next)
	{
		cout << "Sinh vien " << i->data.student.firstName << " " << i->data.student.lastName 
			<< ", ma so " << i->data.student.stuID << ":" << endl;
		viewScoreBoard(i->data);
	}
	cout << endl << endl;
}

void viewOverallGPAInClass(Class cl, Semester currentSem)
{
	float* overallGPA = countOverallGPAInClass(cl, currentSem);
	int numberOfStu = countNodes(cl.stuList.head); int index = 0;
	cout << "Diem trung binh tich luy cua cac sinh vien trong lop " << cl.cls << ":" << endl;
	for (Node<Student>* i = cl.stuList.head; numberOfStu > index; ++index, i = i->next)
		cout << index + 1 << ". " << i->data.firstName << " "
		<< i->data.lastName << ": " << overallGPA[index];
	cout << endl << endl;
}

void viewScoreBoards(Class cl, Semester sem)
{
	cout << "Bang diem cua lop " << cl.cls << ": " << endl;
	for (int i = 0; i < 40; ++i)
		cout << " ";

	LList<Course> courseList = findCoursesOfClass(cl, sem);
	for (Node<Course>* i = courseList.head; i != nullptr; ++i)
		cout << setw(50) << setfill('-') << left << i->data.courseName;
	cout << setw(30) << setfill('-') << left << "Semester GPA";
	cout << setw(30) << setfill('-') << left << "Overall GPA" << endl;

	for (Node<Student>* index1 = cl.stuList.head; index1 != nullptr; index1 = index1->next)
	{
		cout << setw(40) << index1->data.firstName << " " << index1->data.lastName;
		for (Node<Course>* index2 = courseList.head; index2 != nullptr; index2 = index2->next)
		{
			Node<Scoreboard>* node = index1->data.marks.head;
			for (; node->data.course.id.compare(index2->data.id) != 0; node = node->next)
				continue;
			cout << setw(50) << left << node->data.Final;
		}
		cout << setw(30) << left << index1->data.semGPA;
		cout << setw(30) << left << index1->data.GPA;
		if (index1->next != nullptr)
			cout << endl;
	}
	cout << endl << endl;
}