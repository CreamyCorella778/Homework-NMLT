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

Node<Staff>* findStaff(string id)
{
	for (Node<Staff>* i = systems.allStaff.head; i != nullptr; i = i->next)
		if (i->data.id.compare(id) == 0)
			return i;
	return nullptr;
}

int findSecondOccurrenceOfChar(const char* str, char c) 
{
	int index = -1;
	for (int i = 0; i != strlen(str); i++) 
		if (str[i] == c) 
			if (index == -1) 
				index = i;
			else 
				return i;
	return -1;
}

SchoolYear extractSchoolyear(string fname) // fname = all_courses_schoolyear.txt
{
	string res = ""; int startPoint = findSecondOccurrenceOfChar(fname.c_str(), '_') + 1;
	for (int i = startPoint; i - startPoint < 2; ++i)
		res.push_back(fname[i]);
	int c = atoi(res.c_str());
	if (c >= 77)
		return createSchoolYear(1900 + c, 1901 + c);
	else
		return createSchoolYear(2000 + c, 2001 + c);
}

bool writeAllCourses(string fname) // fname = all_courses_schoolyear.txt
{
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (fp.is_open() == false)
		return false;
	else
	{
		fp << "No,ID,Course name,Teacher's id,Class,Credits,Capacity,Day in week,Session,Semester number\n";
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
						<< i->data.teacher.id << ","
						<< i->data.lop.cls << ","
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
		string container = "";
		getline(fp, container, '\n');
		for (int i = 0; i < 2; ++i)
			systems.allCourse[i].init();
		while (!fp.eof())
		{
			Course a;
			getline(fp, container, ',');
			getline(fp, a.id, ',');
			getline(fp, a.courseName, ',');
			getline(fp, container, ',');
			Node<Staff>* node = findStaff(container);
			if (node == nullptr)
			{
				fp.close();
				return false;
			}
			else
				a.teacher = node->data;
			getline(fp, container, ',');
			Node<Class>* nodE = findCLass(container);
			if (nodE == nullptr)
			{
				fp.close();
				return false;
			}
			else
				a.lop = nodE->data;
			getline(fp, container, ','); a.credits = atoi(container.c_str());
			getline(fp, container, ','); a.capacity = atoi(container.c_str());
			getline(fp, container, ','); a.dayInWeek = atoi(container.c_str());
			getline(fp, container, ','); a.session = atoi(container.c_str());
			getline(fp, container, '\n'); a.sem.number = atoi(container.c_str());
			a.sem.sy = extractSchoolyear(fname);
			Node<Course>* noDe = new Node<Course>; noDe->init(a);
			addLast(systems.allCourse[a.sem.number - 1], noDe);
		}
		fp.close();
		return true;
	}
}

bool writeAllClasses(string fname) // fname = all_classes_schoolyear.txt
{
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (fp.is_open() == false)
		return false;
	else
	{
		fp << "No,Class name\n";
		bool written = false;
		if (systems.allClass.head == systems.allClass.tail && systems.allClass.head == nullptr)
			written = false;
		else
		{
			int j = 1;
			for (Node<Class>* i = systems.allClass.head; i != nullptr; i = i->next, ++j)
			{
				fp << j << ","
					<< i->data.cls << ",";
				if (!(i->next == nullptr))
					fp << "\n";
			}
			written = true;
		}
		fp.close();
		return written;
	}
}

bool readAllClasses(string fname)
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string container = "";
		getline(fp, container, '\n');
		systems.allClass.init();
		while (!fp.eof())
		{
			Class a; string container2 = "";
			getline(fp, container, ',');
			getline(fp, container2, '\n');
			a = createClass(container2);
			Node<Class>* node = new Node<Class>; node->init(a);
			addLast(systems.allClass, node);
		}
		fp.close();
		return true;
	}
}

bool writeAllCoursesByStaff(string fname) // fname = staffid.txt
{
	string staID = ""; staID.assign(fname, fname.find_last_of('.') + 1);
	Node<Staff>* node = findStaff(staID);
	if (node == nullptr)
		return false;
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (fp.is_open() == false)
		return false;
	else
	{
		fp << "No,ID,Course name,Teacher's id,Class,Credits,Capacity,Day in week,Session,Semester number\n";
		bool written = false;
		if (node->data.courses.head == node->data.courses.tail && node->data.courses.head == nullptr)
			written = false;
		else
		{
			int j = 1;
			for (Node<Course>* i = node->data.courses.head; i != nullptr; i = i->next, ++j)
			{
				fp << j << ","
					<< i->data.id << ","
					<< i->data.courseName << ","
					<< i->data.teacher.id << ","
					<< i->data.lop.cls << ","
					<< i->data.credits << ","
					<< i->data.capacity << ","
					<< i->data.dayInWeek << ","
					<< i->data.session << ","
					<< i->data.sem.number;
				if (!(i->next == nullptr))
					fp << "\n";
			}
			written = true;
		}
		fp.close();
		return written;
	}
}

bool readAllCoursesByStaff(string fname)
{
	string staID = ""; staID.assign(fname, fname.find_last_of('.') + 1);
	Node<Staff>* node = findStaff(staID);
	if (node == nullptr)
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
		while (!fp.eof())
		{
			Course a, b;
			getline(fp, container, ',');
			getline(fp, a.id, ',');
			getline(fp, a.courseName, ',');
			getline(fp, container, ',');
			a.teacher = node->data;
			getline(fp, container, ','); a.lop = createClass(container);
			getline(fp, container, ','); a.credits = atoi(container.c_str());
			getline(fp, container, ','); a.capacity = atoi(container.c_str());
			getline(fp, container, ','); a.dayInWeek = atoi(container.c_str());
			getline(fp, container, ','); a.session = atoi(container.c_str());
			getline(fp, container, '\n'); a.sem.number = atoi(container.c_str());
			if (findCourse(a.id, a.lop.cls, a.sem.number, b))
				a.sem.sy = b.sem.sy;
			Node<Course>* n0de = new Node<Course>; n0de->init(a);
			addLast(node->data.courses, n0de);
		}
		fp.close();
		return true;
	}
}

