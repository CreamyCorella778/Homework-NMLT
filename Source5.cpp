#include "Header1.hpp"
#include "Header2.hpp"

void initSystems()
{
	systems.allCourse = new LList<Course>[3];
	for (int i = 0; i < 3; ++i)
		systems.allCourse[i].init();
	systems.allClass.init();
}

LList<Course> courseAttending(Student stu, Semester sem)
{
	LList<Course> courseList; courseList.init();
	for (Node<Course>* i = systems.allCourse[sem.number - 1].head; i != nullptr; i = i->next)
		if (findNode(i->data.stuList, stu) != nullptr)
		{
			Node<Course>* node = new Node<Course>; node->init(i->data);
			addLast(courseList, node);
		}
	stu.courses = courseList;
	return courseList;
}

void viewCourses(Student stu, Semester sem)
{
	LList<Course> courseList = courseAttending(stu, sem);
	cout << "Cac khoa hoc cua hoc sinh " << stu.firstName << " " << stu.lastName
		<< " trong hoc ki " << sem.number << ":" << endl;
	for (Node<Course>* i = courseList.head; i != nullptr; i = i->next)
		viewCourse(i->data);
}
