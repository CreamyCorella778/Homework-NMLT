#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

void initSystems()
{
	systems.allCourse = new LList<Course>[3];
	for (int i = 0; i < 3; ++i)
		systems.allCourse[i].init();
	systems.allClass.init();
	systems.allSemester.init();
	systems.allStaff.init();
}

LList<Course> courseAttending(Student stu, Semester sem)
{
	LList<Course> courseList; courseList.init();
	for (Node<Course>* i = systems.allCourse[sem.number - 1].head; i; i = i->next)
		if (findNode(i->data.stuList, stu))
		{
			Node<Course>* node = new Node<Course>; node->init(i->data);
			addLast(courseList, node);
		}
	stu.courses = courseList;
	return courseList;
}

Node<Course>* findCourse(string courseID, string className, int semNum)
{
	for (Node<Course>* i = systems.allCourse[semNum - 1].head; i != nullptr; i = i->next)
		if (!i->data.id.compare(courseID) && !i->data.lop.cls.compare(className))
			return i;
	return nullptr;
}

Node<Student>* findStudent(string id, Class cl)
{ 
	for (Node<Student>* i = cl.stuList.head; i != nullptr; i = i->next)
		if (i->data.stuID.compare(id) == 0)
			return i;
	return nullptr;
}

Node<Student>* findStudent(string id)
{
	for (Node<Class>* cl = systems.allClass.head; cl != nullptr; cl = cl->next)
		for (Node<Student>* i = cl->data.stuList.head; i != nullptr; i = i->next)
			if (i->data.stuID.compare(id) == 0)
				return i;
	return nullptr;
}

Node<Class>* findCLass(string name)
{
	for (Node<Class>* i = systems.allClass.head; i != nullptr; i = i->next)
		if (i->data.cls.compare(name) == 0)
			return i;
	return nullptr;
}

Node<Staff>* findStaff(string id)
{
	for (Node<Staff>* i = systems.allStaff.head; i != nullptr; i = i->next)
		if (i->data.id.compare(id) == 0)
			return i;
	return nullptr;
}

