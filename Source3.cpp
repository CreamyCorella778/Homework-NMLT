#include "Header1.hpp"
#include "Header2.hpp"

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
		<< "tiet 4 bat dau luc 15 30: ";
	cin >> a.session;
}

bool addCoursetoSemester(Course a, Semester sem) 
{
	Node<Course>* node = new Node<Course>; node->init(a);
	addLast(systems.allCourse[sem.number - 1], node);
	string fname = "all_course_" + sem.sy.schYr + ".txt";
	return writeAllCourses(fname);
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


void getIn4toUpdateCourse(string& courseID, string& cl, int& option)
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
			<< "7. Buoi trong ngay de hoc" << endl
			<< "sess 1 starts at 7:30, sess 2 starts at 9:30, sess 3 starts at 13:30, sess 4 starts at 15:30" << endl
			<< "8. Hoc ki de hoc: ";
		cin >> option;
	} while (option < 1 || option > 8);
}

CourseVarType getIn4toUpdateCourse(int option)
{
	CourseVarType dataa;
	switch (option)
	{
	case 1:
	{
		dataa.courseName = new string;
		cout << "Nhap ten khoa hoc moi: "; getline(cin, *dataa.courseName);
	}
	break;
	//////////////////////////////////////
	case 2:
	{
		string temp = ""; int times = 5; dataa.teacher = new Node<Staff>;
		do
		{
			cout << "Ban con " << times << " lan nhap. Nhap ma cua giao vien moi : "; cin >> temp;
			--times;
			dataa.teacher = findStaff(temp);
		} while (dataa.teacher == nullptr && times > 0);
		if (dataa.teacher == nullptr)
			cout << "Khong ton tai giao vien. Chuc ban may man lan sau" << endl;
	}
	break;
	//////////////////////////////////////
	case 3:
	{
		cout << "Nhap so tin chi moi: "; cin >> dataa.credits;
	}
	break;
	//////////////////////////////////////
	case 4:
	{
		cout << "Nhap so hoc sinh toi da moi: "; cin >> dataa.capacity;
	}
	break;
	//////////////////////////////////////
	case 5:
	{
		string temp = ""; int times = 5; dataa.lop = new Node<Class>;
		do
		{
			cout << "Ban con " << times << " lan nhap. Nhap ten lop moi : "; cin >> temp;
			--times;
			dataa.lop = findCLass(temp);
		} while (dataa.lop == nullptr && times > 0);
		if (dataa.lop == nullptr)
			cout << "Khong ton tai lop. Chuc ban may man lan sau" << endl;
	}
	break;
	////////////////////////////////////////
	case 6:
	{
		cout << "Nhap thu trong tuan moi cho khoa hoc: "; cin >> dataa.dayInWeek;
	}
	break;
	//////////////////////////////////////
	case 7:
	{
		cout << "sess 1 starts at 7:30, sess 2 starts at 9:30, sess 3 starts at 13:30, sess 4 starts at 15:30" << endl;
		cout << "Nhap buoi hoc moi trong ngay: "; cin >> dataa.session;
	}
	break;
	////////////////////////////////////////
	case 8:
	{
		cout << "Phan nhap hoc ki moi: " << endl;
		int no = 0;  SchoolYear sy; Date sd, ed;
		getSemesterIn4(no, sy, sd, ed);
		Semester sem = { no, sy, sd, ed }; 
		dataa.sem = findNode(systems.allSemester, sem);
		if (dataa.sem == nullptr)
		{
			dataa.sem = new Node<Semester>;
			dataa.sem->data = createSemester(no, sy, sd, ed);
		}
	}
	break;
	default:
		dataa.sem = nullptr;
	}
	return dataa;
}

bool updateCourseIn4(string courseID, string cl, int option, CourseVarType in4, Semester sem) // ??? watch out this one
{
	Node<Course>* i = systems.allCourse[sem.number - 1].head;
	for (i; !(i->data.id == courseID && i->data.lop.cls == cl) && i != nullptr; i = i->next)
		continue;
	if (i == nullptr)
		return false;
	switch (option)
	{
	case 1:
		i->data.courseName = *in4.courseName;
		break;
	case 2:
		if (in4.teacher == nullptr)
			return false;
		else
			i->data.teacher = in4.teacher->data;
		break;
	case 3:
		i->data.credits = in4.credits;
		break;
	case 4:
		i->data.capacity = in4.capacity;
		break;
	case 5:
		if (in4.lop == nullptr)
			return false;
		else
			i->data.lop = in4.lop->data;
		break;
	case 6:
		i->data.dayInWeek = in4.dayInWeek;
		break;
	case 7:
		i->data.session = in4.session;
		break;
	case 8:
		i->data.sem = in4.sem->data;
		break;
	default:
		return false;
	}
	return true;
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

bool addStudentToCourse(Student st, Course& c) // fname = courseid_classname_semnumber.txt
{
	st.no = countNodes(c.stuList.head) + 1;
	Node<Student>* node = new Node<Student>; node->init(st);
	addLast(c.stuList, node);
	string fname = generateFileName(c, st.cl, c.sem);
	ofstream fp;
	fp.open(fname, ios::app);
	if (!fp.is_open())
		return false;
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
		return true;
	}
}

bool removeStudentFromCourse(Student st, Course& c)
{
	st.no = 0;
	removeRandomNode(c.stuList, st);
	string fname = generateFileName(c, st.cl, c.sem);
	return writeStudentsInCourse(fname, c);
}

bool removeCourse(Course c, Semester sem)
{
	removeRandomNode(systems.allCourse[sem.number - 1], c);
	string fname = "all_course_" + sem.sy.schYr + ".txt";
	return writeAllCourses(fname);
}

