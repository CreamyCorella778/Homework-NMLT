#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

bool writeAllCoursesOfStudent(string fname) // fname = studentid.txt
{
	string stuID = ""; stuID.assign(fname, 0, fname.find_last_of('.'));
	Node<Student>* node = findStudent(stuID);
	if (!node && ((node->data.courses.head == node->data.courses.tail && !node->data.courses.head) 
		|| (node->data.marks.head == node->data.marks.tail && !node->data.marks.head)))
		return false;
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (!fp.is_open())
		return false;
	else
	{
		fp << "No,ID,Course name,Teacher's id,Class,Credits,Capacity,Day in week,Session,Semester number,Midterm,Final,Other,Total\n";
		int no = 1;
		Node<Course>* i = node->data.courses.head; Node<Scoreboard>* j = node->data.marks.head;
		for (;(i != nullptr) && (j != nullptr); i = i->next, j = j->next, ++no)
		{
			fp << no << ","
				<< i->data.id << ","
				<< i->data.courseName << ","
				<< i->data.teacher.id << ","
				<< i->data.lop.cls << ","
				<< i->data.credits << ","
				<< i->data.capacity << ","
				<< i->data.dayInWeek << ","
				<< i->data.session << ","
				<< i->data.sem.number << ","
				<< j->data.midTerm << ","
				<< j->data.Final << ","
				<< j->data.Other << ","
				<< j->data.Total;
				fp << "\n";
		}
		fp << node->data.semGPA << "," << node->data.GPA;
		fp.close();
		return true;
	}
}

bool readAllCoursesOfStudent(string fname)
{
	string stuID = ""; stuID.assign(fname, 0, fname.find_last_of('.'));
	Node<Student>* node = findStudent(stuID);
	if (!node)
		return false;
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string container = "";
		getline(fp, container, '\n');
		node->data.courses.init();
		node->data.marks.init();
		while (getline(fp, container, ','))
		{
			Course a;
			getline(fp, a.id, ',');
			if (!getline(fp, a.courseName, ','))
			{
				node->data.semGPA = atof(container.c_str());
				node->data.GPA = atof(a.id.c_str());
				break;
			}
			getline(fp, container, ','); a.teacher = findStaff(container)->data;
			getline(fp, container, ','); a.lop = createClass(container);
			getline(fp, container, ','); a.credits = atoi(container.c_str());
			getline(fp, container, ','); a.capacity = atoi(container.c_str());
			getline(fp, container, ','); a.dayInWeek = atoi(container.c_str());
			getline(fp, container, ','); a.session = atoi(container.c_str());
			getline(fp, container, ','); a.sem.number = atoi(container.c_str());
			Node<Course>* b = findCourse(a.id, a.lop.cls, a.sem.number);
			if (b)
				a.sem.sy = b->data.sem.sy;
			else
			{
				fp.close();
				return false;
			}
			Scoreboard c; 
			c.course = a;
			c.student = node->data;
			getline(fp, container, ','); c.midTerm = atof(container.c_str());
			getline(fp, container, ','); c.Final = atof(container.c_str());
			getline(fp, container, ','); c.Other = atof(container.c_str());
			getline(fp, container, '\n'); c.Total = atof(container.c_str());
			Node<Course>* n0de = new Node<Course>; n0de->init(a);
			addLast(node->data.courses, n0de);
			Node<Scoreboard>* nodE = new Node<Scoreboard>; nodE->init(c);
			addLast(node->data.marks, nodE);
		}
		fp.close();
		return true;
	}
}

