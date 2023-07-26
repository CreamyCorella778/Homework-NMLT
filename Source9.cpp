#include "Header1.h"
#include "Header2.h"

bool writeStaffList(string fname) // fname = all_staffs.txt
{
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (fp.is_open() == false)
		return false;
	else
	{
		fp << "No,Staff ID,First name,Last name\n";
		if (systems.allStaff.head == systems.allStaff.tail && systems.allStaff.head == nullptr)
		{
			fp.close();
			return false;
		}
		else
		{
			int j = 1;
			for (Node<Staff>* i = systems.allStaff.head; i != nullptr; i = i->next, ++j)
				fp << j << ","
					<< i->data.id << ","
					<< i->data.firstName << ","
					<< i->data.lastName << ",";
			fp.close();
			return true;
		}
	}
}

bool readStaffList(string fname) 
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{	
		char* container = new char[100];
		fp.getline(container, '\n');
		systems.allStaff.init();
		while(!fp.eof())
		{
			Staff a;
			fp.getline(container, ',');
			getline(fp, a.id, ',');
			getline(fp, a.firstName, ',');
			getline(fp, a.lastName, '\n');
			Node<Staff>* node = new Node<Staff>; node->init(a);
			addLast(systems.allStaff, node);
		}
		fp.close();
		delete[]container;
		container = nullptr;
		return true;
	}
}

bool writeAllCourses(string fname) // fname = all_courses_schoolyear.txt
{
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (fp.is_open() == false)
		return false;
	else
	{
		fp << "No,ID,Course name,Teacher's first name,Teacher's last name,Credits,Capacity,Day in week,Session,Semester number\n";
		bool written = false;
		for (int index = 0; index < 3; ++index)
			if (systems.allCourse[index].head == systems.allCourse[index].tail && systems.allCourse[index].head == nullptr)
				continue;
			else
			{
				int j = 1;
				for (Node<Course>* i = systems.allCourse[index].head; i != nullptr; i = i->next, ++j)
				{
					fp << j << ","
						<< i->data.id << ","
						<< i->data.courseName << ","
						<< i->data.teacher.firstName << ","
						<< i->data.teacher.lastName << ","
						<< i->data.credits << ","
						<< i->data.capacity << ","
						<< i->data.dayInWeek << ","
						<< i->data.session << ","
						<< i->data.sem.number;
					if (!(i->next == nullptr && index == 2))
						fp << "\n";
				}
				written = true;
			}
		fp.close();
		return written;
	}
}

bool readAllCourses(string fname)
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		char* container = new char[100];
		fp.getline(container, '\n');
		for (int i = 0; i < 2; ++i)
			systems.allCourse[i].init();
		while (!fp.eof())
		{
			Course a;
			fp.getline(container, ',');
			getline(fp, a.id, ',');
			getline(fp, a.firstName  , ',');
			getline(fp, a.lastName, '\n');
			Node<Staff>* node = new Node<Staff>; node->init(a);
			addLast(systems.allStaff, node);
		}
		fp.close();
		return true;
	}
}