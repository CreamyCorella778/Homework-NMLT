#include "Header1.h"
#include "Header2.h"

bool writeAllCoursesOfStudent(string fname, Student stu) // fname = studentid.txt
{
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (fp.is_open() == false)
		return false;
	else
	{
		fp << "No,ID,Course name,Teacher's id,Class,Credits,Capacity,Day in week,Session,Semester number,Midterm,Final,Other,Total\n";
		bool written = false;
		if ((stu.courses.head == stu.courses.tail && stu.courses.head == nullptr) || (stu.marks.head == stu.marks.tail && stu.marks.head == nullptr))
			written = false;
		else
		{
			int no = 1;
			Node<Course>* i = stu.courses.head; Node<Scoreboard>* j = stu.marks.head;
			for (i, j; i != nullptr && j != nullptr; i = i->next, j = j->next, ++no)
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
				if (!(i->next == nullptr && j->next == nullptr))
					fp << "\n";
			}
			written = true;
		}
		fp.close();
		return written;
	}
}

bool readAllCoursesOfStudent(string fname, Student& stu)
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string container = "";
		getline(fp, container, '\n');
		stu.courses.init();
		stu.marks.init();
		while (!fp.eof())
		{
			Course a, b;
			getline(fp, container, ',');
			getline(fp, a.id, ',');
			getline(fp, a.courseName, ',');
			getline(fp, container, ',');
			a.teacher = findStaff(container)->data;
			getline(fp, container, ','); a.lop = createClass(container);
			getline(fp, container, ','); a.credits = atoi(container.c_str());
			getline(fp, container, ','); a.capacity = atoi(container.c_str());
			getline(fp, container, ','); a.dayInWeek = atoi(container.c_str());
			getline(fp, container, ','); a.session = atoi(container.c_str());
			getline(fp, container, ','); a.sem.number = atoi(container.c_str());
			if (findCourse(a.id, a.lop.cls, a.sem.number, b))
				a.sem.sy = b.sem.sy;
			Scoreboard c; 
			c.course = a;
			c.student = stu;
			getline(fp, container, ','); c.midTerm= atof(container.c_str());
			getline(fp, container, ','); c.Final = atof(container.c_str());
			getline(fp, container, ','); c.Other = atof(container.c_str());
			getline(fp, container, '\n'); c.Total = atof(container.c_str());
			Node<Course>* node = new Node<Course>; node->init(a);
			addLast(stu.courses, node);
			Node<Scoreboard>* nodE = new Node<Scoreboard>; nodE->init(c);
			addLast(stu.marks, nodE);
		}
		fp.close();
		return true;
	}
}

