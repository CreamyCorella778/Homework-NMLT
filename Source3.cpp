#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"
 
void getSemesterIn4(int& no, SchoolYear& sy, Date& sd, Date& ed)
{
	cout << "Hoc ki nay la hoc ki may?: "; cin >> no;
	int ys = 0, ye = 0;
	getYears(ys, ye);
	sy = createSchoolYear(ys, ye);
	string container = ""; cin.ignore();
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
	{
		for (; fname[j] != '_' && fname[j] != '.'; ++j)
			idAndName[i].push_back(fname[j]);
		++j;
	}
	return idAndName;
}

string generateFileName(Course c, Class cl, Semester sem)
{
	string fname = "";
	fname += c.id; fname.push_back('_');
	fname += cl.cls; fname.push_back('_');
	fname += to_string(sem.number);
	fname += ".txt";
	return fname;
}

void getCourseIn4(Course &a, Semester sem)
{
	string container = ""; int so_lan = 5;
	cout << "Nhap ma khoa hoc: "; getline(cin, a.id);
	cout << "Nhap ten khoa hoc: "; getline(cin, a.courseName);
	Node<Staff>* node = new Node<Staff>;
	do
	{
		cout << "Nhap ma so giao vien day chinh: "; getline(cin, container);
		node = findStaff(container);
		--so_lan;
		if (!node)
			cout << "Ban con " << so_lan << " lan nhap. ";
	} while (!node && so_lan);
	if (!node)
	{
		cout << "Khong tim thay giao vien. Chuc ban may man lan sau." << endl;
		a.teacher.id.assign("not found");
		return;
	}
	else
		a.teacher = node->data;
	cout << "Nhap so tin chi: "; cin >> a.credits;
	cout << "Nhap so hoc sinh toi da trong khoa hoc: "; cin >> a.capacity;
	cin.ignore();
	cout << "Nhap ten lop cua khoa hoc: "; getline(cin, container); 
    Node<Class>* n0de = findCLass(container);
    if (!n0de)
    {
        int option = 0;
		cout << "Khong tim thay lop. Ban co muon tao lop moi voi ten vua roi khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon:" << endl
        << "1. Co                        2. Khong: "; 
        cin >> option;
        if (option == 1)
        {
            n0de = new Node<Class>;
            n0de->init(createClass(container));
            cout << "Tao thanh cong." << endl;
        }
        else
        {
            cout << "Loi he thong. Chuc ban may man lan sau." << endl;
            return;
        }
    }
	else
		a.lop = n0de->data;
	cout << "Nhap thu trong tuan cua khoa hoc, tu thu 2 den thu 8 (chu nhat): "; cin >> a.dayInWeek;
	cout << "Nhap tiet hoc trong ngay cua khoa hoc:" << endl
		<< "tiet 1 bat dau luc 7:30" << endl
		<< "tiet 2 bat dau luc 9:30" << endl
		<< "tiet 3 bat dau luc 13:30" << endl
		<< "tiet 4 bat dau luc 15:30: ";
	cin >> a.session;
	a.sem = sem;
}

bool addCoursetoSemester(Course a, Semester sem) 
{
	Node<Course>* node = new Node<Course>; node->init(a);
	addLast(systems.allCourse[sem.number - 1], node);
	string fname = "all_courses_" + sem.sy.schYr + ".txt";
	return writeAllCourses(fname);
}

void getIn4toUpdateCourse(string& courseID, string& cl, int& option)
{
	cout << "Nhap ma khoa hoc can cap nhat: "; getline(cin ,courseID);
	cout << "Nhap ten lop hoc cua khoa hoc: "; getline(cin, cl);
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
		if (option < 1 || option > 8)
			cout << "Nhap khong hop le. ";
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
		} while (!dataa.teacher && times);
		if (!dataa.teacher)
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
		} while (!dataa.lop && times > 0);
		if (!dataa.lop)
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
		if (!dataa.sem)
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

bool updateCourseIn4(Course &course, int option, CourseVarType in4) 
{
	switch (option)
	{
	case 1:
		course.courseName.assign(*in4.courseName);
		break;
	case 2:
		if (!in4.teacher)
			return false;
		else
			course.teacher = in4.teacher->data;
		break;
	case 3:
		course.credits = in4.credits;
		break;
	case 4:
		course.capacity = in4.capacity;
		break;
	case 5:
		if (!in4.lop)
			return false;
		else
			course.lop = in4.lop->data;
		break;
	case 6:
		course.dayInWeek = in4.dayInWeek;
		break;
	case 7:
		course.session = in4.session;
		break;
	case 8:
		course.sem = in4.sem->data;
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
	cout << "Nhap gioi tinh: 1 neu la nam, 0 neu la nu: "; cin >> i;
	a.gender = i == 0 ? false : true;
	cout << "Nhap ngay thang nam sinh (co dang dd/mm/yyyy): "; cin >> container;
	a.birth = getNS(container);
	cin.ignore();
	cout << "Nhap so can cuoc cong dan: "; getline(cin, a.socialID);
}

bool addStudentToCourse(Student st, Course& c) // fname = courseid_classname_semnumber.txt
{
	st.no = countNodes(c.stuList.head) + 1;
	Node<Student>* node = new Node<Student>; node->init(st);
	addLast(c.stuList, node);
	string fname = generateFileName(c, c.lop, c.sem);
	ofstream fp;
	fp.open(fname, ios::app);
	if (!fp.is_open())
		return false;
	else
	{
		countNoInStudentList(c.stuList);
		fp << "\n" << node->data.no << ","
			<< st.stuID << ","
			<< st.firstName << "," << st.lastName << ",";
		if (st.gender)
			fp << "nam,";
		else
			fp << "nu,";
		fp << st.birth.day << "/" << st.birth.month << "/" << st.birth.year << ","
			<< st.socialID;
		fp << ",0,0,0,0";
		fp.close();
		return true;
	}
}

bool removeStudentFromCourse(Student st, Course& c)
{
	Node<Student>* i = c.stuList.head; bool deleted = false;
	for (;i; i = i->next)
		if (!i->data.stuID.compare(st.stuID))
		{
			removeRandomNode(c.stuList, i);
			deleted = true;
			break;
		}
	if (!deleted)
		return false;
	string fname = generateFileName(c, c.lop, c.sem);
	return writeStudentsInCourse(fname, c);
}

bool removeCourse(Course c, Semester sem)
{
	Node<Course>* node = findCourse(c.id, c.lop.cls, sem.number);
	if (!node)
		return false;
	removeRandomNode(systems.allCourse[sem.number - 1], node);
	string fname = "all_courses_" + sem.sy.schYr + ".txt";
	return writeAllCourses(fname);
}

