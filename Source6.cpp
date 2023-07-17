#include "Header1.h"
#include "Header2.h"

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
	cout << ", gioi tinh " << a.gender ? "nam " : "nu ";
	cout << ", ngay sinh: " << a.birth.day << "/" << a.birth.month << "/" << a.birth.year;
	cout << ", ma so can cuoc cong dan la " << a.socialID;
}

void viewStudents(Class a)
{
	for (Node<Student>* i = a.stuList.head; i != nullptr; i = i->next)
		viewStudent(i->data);
	cout << endl << endl;
}

void viewCourses(Semester sem)
{
	for (Node<Course>* i = systems.allCourse[sem.number - 1].head; i != nullptr; i = i->next)
		viewCourse(i->data);
	cout << endl << endl;
}

void viewCourses()
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