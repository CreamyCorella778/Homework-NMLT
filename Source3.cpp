#include "Header1.h"
#include "Header2.h"

void getSemesterIn4(int& no, SchoolYear& sy, Date& sd, Date& ed)
{
	cout << "Hoc ki nay la hoc ki may?: "; cin >> no;
	int ys = 0, ye = 0;
	getYears(ys, ye);
	sy = createSchoolYear(ys, ye);
	string container;
	cout << "Nhap ngay bat dau: "; getline(cin, container);
	sd = getNS(container);
	cout << "Nhap ngay ket thuc: "; getline(cin, container);
	ed = getNS(container);
}

Semester createSemester(int no, SchoolYear sy, Date sd, Date ed)
{
	Semester sem;
	getSemesterIn4(no, sy, sd, ed);
	sem.number = no;
	sem.sy = sy;
	sem.startDate = sd;
	sem.endDate = ed;
	Node<Semester>* node = new Node<Semester>; node->init(sem);
	addLast(systems.allSemester, node);
	return sem;
}

string* extractCId_cl_sno(string fname) // fname = courseid_classname_semnumber.txt
{
	int j = 0; string* idAndName = new string[3];
	for (int i = 0; i < 3; ++i)
		for (j; fname[j] - '_' == 0 || fname[j] - '.' == 0; ++j)
			idAndName[i].push_back(fname[j]);
	return idAndName;
}

string generateFileName(Course c, Class cl, Semester sem)
{
	string fname = "";
	fname += c.id;
	fname += cl.cls;
	fname += to_string(sem.number);
	return fname;
}

void getCourseIn4(Course &a, Semester sem)
{
	cout << "Nhap ma hoc phan: "; getline(cin, a.id);
	cout << "Nhap ten hoc phan: "; getline(cin, a.courseName);
	string container = ""; int so_lan = 5;
	cout << "Nhap ma so giao vien chinh day: "; getline(cin, container);
	Node<Course>* i = systems.allCourse[sem.number - 1].head;
	for (i; i != nullptr; i = i->next)
		if (i->data.teacher.id.compare(container) == 0)
			a.teacher = i->data.teacher;
	do
	{
		cout << "Ban co " << so_lan << "nhap. Nhap lai ma so giao vien chinh day : "; getline(cin, container);
		Node<Course>* i = systems.allCourse[sem.number - 1].head;
		for (i; i != nullptr; i = i->next)
			if (i->data.teacher.id.compare(container) == 0)
				a.teacher = i->data.teacher;
		so_lan -= 1;
	} while (i == nullptr && so_lan != 0);
	cout << "Nhap so tin chi: "; cin >> a.credits;
	cout << "Nhap so hoc sinh toi da trong khoa hoc: "; cin >> a.capacity;
	cout << "Nhap ten lop cua hoc phan: "; getline(cin, container); a.lop = createClass(container);
	cout << "Nhap thu trong tuan cua hoc phan, tu thu 2 den thu 8 (chu nhat): "; cin >> a.dayInWeek;
	cout << "Nhap tiet hoc trong ngay cua hoc phan:" << endl
		<< "tiet 1 bat dau luc 7:30" << endl
		<< "tiet 2 bat dau luc 9:30" << endl
		<< "tiet 3 bat dau luc 13:30" << endl
		<< "tiet 4 bat dau luc 15 30";
	cin >> a.session;
}

void addCoursetoSemester(Course a, Semester sem) 
{
	Node<Course>* node = new Node<Course>; node->init(a);
	addLast(systems.allCourse[sem.number - 1], node);
	string fname = "all_course_" + sem.sy.schYr + ".txt";
	writeAllCourses(fname);
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
	for (Node<Course>* i = systems.allCourse[sem.number - 1].head; i != nullptr; i = i->next)
		viewCourse(i->data);
	cout << endl << endl;
}

void getIn4toUpdateCourse(string& courseID, string& cl, int &option)
{
	cout << "Nhap ma hoc phan can cap nhat: "; cin >> courseID;
	cout << "Nhap ten lop hoc cua hoc phan: "; cin >> cl;
	do
	{
		cout << "Chon so thu tu tuong ung voi truong can cap nhat: " << endl
			<< "1. Ten khoa hoc" << endl
			<< "2. Giao vien day" << endl
			<< "3. So tin chi" << endl
			<< "4. So hoc sinh toi da" << endl
			<< "5. Lop" << endl
			<< "6. Thu trong tuan de hoc" << endl
			<< "7. Buoi trong nay de hoc" << endl
			<< "sess 1 starts at 7:30, sess 2 starts at 9:30, sess 3 starts at 13:30, sess 4 starts at 15:30" << endl
			<< "8. Hoc ki de hoc: ";
		cin >> option;
	} while (option < 1 || option > 8);
}

void updateCourseIn4(string courseID, string cl, int option, Semester sem) // ??? watch out this one
{
	Node<Course>* i = systems.allCourse[sem.number - 1].head;
	for (i; !(i->data.id == courseID && i->data.lop.cls == cl); i = i->next)
		continue;
	switch (option)
	{
	case 1:
		// watch out this one weeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}

string* extractFirstLastName(string name)
{
	string* names = new string[2]; string space = " ";
	int index = name.find_last_of(space);
	for (int i = 0; i < index; ++i)
		names[0].push_back(name[i]);
	for (int i = index + 1; i < name.length(); ++i)
		names[1].push_back(name[i]);
	return names;
}

void getStudentIn4(Student& a)
{
	string container;
	cout << "Nhap ten sinh vien: "; getline(cin, container);
	a.firstName = extractFirstLastName(container)[0];
	a.lastName = extractFirstLastName(container)[1];
	cout << "Nhap ma so sinh vien: "; getline(cin, a.stuID);
	int i = 0;
	cout << "Nhap gioi tinh: 1 neu a nam, 0 neu la nu: "; cin >> i;
	a.gender = i == 0 ? false : true;
	cout << "Nhap ngay thang nam sinh (dang dd/mm/yyyy): "; cin >> container;
	a.birth = getNS(container);
	cout << "Nhap so can cuoc cong dan: "; getline(cin, a.socialID);
}

void addStudentToCourse(Student st, Course& c) // fname = courseid_classname_semnumber.txt
{
	st.no = countNodes(c.stuList.head) + 1;
	Node<Student>* node = new Node<Student>; node->init(st);
	addLast(c.stuList, node);
	string fname = generateFileName(c, st.cl, c.sem);
	ofstream fp;
	fp.open(fname, ios::app);
	if (!fp.is_open())
		return;
	else
	{
		Node<Student>* node = new Node<Student>; node->init(st);
		countNoInStudentList(c.stuList);
		fp << "\n" << node->data.no << ","
			<< st.stuID << ","
			<< st.firstName << " " << st.lastName << ",";
		if (st.gender)
			fp << "nam,";
		else
			fp << "nu,";
		fp << st.birth.day << "/" << st.birth.month << "/" << st.birth.year << ","
			<< st.socialID;
		fp.close();
		return;
	}
}

void removeStudentFromCourse(Student st, Course& c)
{
	st.no = 0;
	removeRandomNode(c.stuList, st);
	string fname = generateFileName(c, st.cl, c.sem);
	writeStudentsInCourse(fname, c);
}

void removeCourse(Course c, Semester sem)
{
	removeRandomNode(systems.allCourse[sem.number - 1], c);
	string fname = "all_course_" + sem.sy.schYr + ".txt";
	writeAllCourses(fname);
}

