#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

void getYears(int& yearStart, int& yearEnd)
{
	cout << "Nhap lan luot nam bat dau va nam ket thuc cua nam hoc: ";
	cin >> yearStart >> yearEnd;
}

SchoolYear createSchoolYear(int yearStart, int yearEnd)
{
	SchoolYear sy;
	sy.yStart = yearStart;
	sy.yEnd = yearEnd;
	sy.schYr = to_string(yearStart).append("-").append(to_string(yearEnd));
	return sy;
}

SchoolYear createSchoolYear(string schy)
{
	string ys = "", ye = ""; int i = 0;
	for (; schy[i] != '-'; ++i)
		ys.push_back(schy.at(i));
	++i;
	for (; i < schy.size(); ++i)
		ye.push_back(schy[i]);
	return createSchoolYear(atoi(ys.c_str()), atoi(ye.c_str()));
}

void getClassIn4(SchoolYear& sy, string& eduProg, int& start, int& end)
{
	int times = 0, n = 0;
	cout << "Ban muon su dung nam hoc hien tai hay tao nam hoc moi cho cac lop nay?" << endl
	<< "Chon so thu tu tuong ung voi lua chon:" << endl
	<< "1. Tao moi     Cac so khac. De nguyen: ";
	cin >> n;
	if (n == 1)
	{
		int year = 0;
		cout << "Nhap nam nhap hoc cua hoc sinh nam nay: "; cin >> year;
		sy = createSchoolYear(year, year + 1);
	}
	do
	{
		cout << "Chon so thu tu tuong ung voi chuong trinh hoc:" << endl
		<< "1. APCS" << endl
		<< "2. Chat luong cao" << endl
		<< "3. Viet-Phap" << endl
		<< "4. Viet-Nhat" << endl
		<< "5. Chuan, dai tra" << endl
		<< "6. Tien tien, de an" << endl
		<< "7. Lien thong dai hoc" << endl
		<< "8. Hoan chinh dai hoc" << endl
		<< "9. Cao dang: "; cin >> n;
		--times;
		if (n > 9 || n < 1)
			cout << "Nhap sai roi. Ban con " << times << " lan nhap." << endl;
	} while ((n > 9 || n < 1) && times > 0);
	if (n > 9 || n < 1)
	{
		cout << "Nhap khong hop le. Chuc ban may man lan sau." << endl;
		eduProg.assign("invalid");
		return;
	}
	switch (n)
	{
	case 1:
		eduProg.assign("APCS");
		break;
	case 2:
		eduProg.assign("CLC");
		break;
	case 3:
		eduProg.assign("VP");
		break;
	case 4:
		eduProg.assign("VN");
		break;
	case 5:
		eduProg.assign("CTT");
		break;
	case 6:
		eduProg.assign("CNS");
		break;
	case 7:
		eduProg.assign("B");
		break;
	case 8:
		eduProg.assign("HCB");
		break;
	case 9:
		eduProg.assign("CD");
		break;
	}
	cout << "So thu tu cua lop bat dau tu dau?:"; cin >> start;
	cout << "Can tao bao nhieu lop?: "; cin >> end;
	end = start + end - 1;
}

Class* createClasses(SchoolYear sy, string eduProg, int start, int end)
{
	if (!eduProg.compare("invalid"))
		return nullptr;
	Class* a = new Class[end - start + 1];
	for (int i = 0; i < end - start + 1; ++i)
	{
		a[i].eduProgr.assign(eduProg);
		a[i].year = sy;
		a[i].no = start + i;
		a[i].cls = to_string(sy.yStart % 100).append(eduProg).append(to_string(start + i));
		Node<Class>* b = new Node<Class>; b->init(a[i]);
		addLast(systems.allClass, b);
	}
	return a;
}

string extractEduProg(string fname) // Assume that the file name part is the class name
{
	string ep = "";
	for (int i = 0; i < fname.size(); ++i)
		if (isalpha(fname.at(i)))
			ep.push_back(fname.at(i));
		else if (fname[i] == '.')
			break;
	return ep;
}

SchoolYear extractSchoolYear(string fname) // fname = classname.txt
{
	string b = ""; b.assign(fname, 0, 2);
	int c = atoi(b.c_str());
	if (c >= 77)
		return createSchoolYear(1900 + c, 1901 + c);
	else
		return createSchoolYear(2000 + c, 2001 + c);
}

int extractNo(string fname)
{
	string a = ""; a.assign(fname, 2 + extractEduProg(fname).length(), fname.length() - 2 - 4 - extractEduProg(fname).length());
	return atoi(a.c_str());
}

Class createClass(string cl)
{
	Class a;
	a.eduProgr.assign(extractEduProg(cl));
	a.year = extractSchoolYear(cl);
	string no = ""; int pos_to_copy = cl.find_last_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") + 1;
	a.no = atoi(no.assign(cl, pos_to_copy, cl.size() - pos_to_copy).c_str());
	a.cls.assign(cl);
	return a;
}

Class createCLass(string fname)
{
	string a = ""; a.assign(fname, 0, fname.find_last_of('.'));
	Class lop = createClass(a);
	return lop;
}

Date getNS(string birth) 
{
	int* ngay_sinh = new int[2]; int j = 0; char* ngsinh = new char[birth.length()];
	memcpy(ngsinh, birth.c_str(), birth.length());
	size_t i = 0;
	int phan_cach = 0;
	Date ket_qua = { 0, 0, 0 }; int* p = &ket_qua.day;
	for (i = 0; i < strlen(ngsinh) + 1; i++)
		if (!isdigit(ngsinh[i])) 
		{
			*p = j == 2 ? ngay_sinh[0] * 10 + ngay_sinh[1] : ngay_sinh[0];
			ngay_sinh[0] = ngay_sinh[1] = 0;
			p++; j = 0;
			phan_cach++;
			if (phan_cach == 2)
				break;
		}
		else
		{
			ngay_sinh[j] = (int)(ngsinh[i] - '0');
			j++;
		}
	ngsinh = _strdup(ngsinh + i + 1);
	*p = atoi(ngsinh);
	delete[]ngay_sinh;
	return ket_qua;
}

// add a student to class in systems and write the student to the respective csv file
bool addStudentToClass(Student stu, Class &cl) // fname = classname.txt
{
	string fname = cl.cls + ".txt";
	ofstream fp;
	fp.open(fname, ios::app);
	if (!fp.is_open())
		return false;
	else
	{
		Node<Student>* node = new Node<Student>; node->init(stu);
		addLast(cl.stuList, node);
		countNoInStudentList(cl.stuList);
		fp << "\n" << node->data.no << ","
			<< stu.stuID << ","
			<< stu.firstName << "," 
			<< stu.lastName << ",";
		if (stu.gender)
			fp << "nam,";
		else
			fp << "nu,";
		fp << stu.birth.day << "/" << stu.birth.month << "/" << stu.birth.year << ","
			<< stu.socialID;
		fp.close();
		return true;
	}
}

// read student lists of a class from csv file
bool addStudentsToClass(string fname) // fname = classname.txt
{
	Node<Class>* node = findCLass(createCLass(fname).cls);
	if (!node)
		return false;
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string container = ""; getline(fp, container, '\n');
		while (getline(fp, container, ','))
		{
			Student stu;
			stu.no = atoi(container.c_str());
			getline(fp, stu.stuID, ',');
			getline(fp, stu.firstName, ',');
			getline(fp, stu.lastName, ',');
			getline(fp, container, ',');
			if (!_stricmp("nam", container.c_str()))
				stu.gender = true;
			else
				stu.gender = false;
			getline(fp, container, ',');
			stu.birth = getNS(container);
			getline(fp, stu.socialID, '\n');
			Node<Student>* n0de = new Node<Student>; n0de->init(stu);
			addLast(node->data.stuList, n0de);
			n0de->data.marks.init();
		}
		fp.close();
		return true;
	}
}

bool writeStudentsInClass(string fname) // fname = classname.txt
{
	Node<Class>* node = findCLass(createCLass(fname).cls);
	if (!node || (node->data.stuList.head == node->data.stuList.tail && !node->data.stuList.head))
		return false;
	countNoInStudentList(node->data.stuList);
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (!fp.is_open())
		return false;
	else
	{
		fp << "No,Student ID,First name,Last name,Gender,Date of birth,Social ID\n";
		for (Node<Student>* i = node->data.stuList.head; i; i = i->next)
		{
			fp << i->data.no << ","
			<< i->data.stuID << ","
			<< i->data.firstName << "," 
			<< i->data.lastName << ",";
			if (i->data.gender)
				fp << "nam,";
			else
				fp << "nu,";
			fp << i->data.birth.day << "/" << i->data.birth.month << "/" << i->data.birth.year << ","
				<< i->data.socialID;
			if (!i->next)
				fp << endl;
		}
		fp.close();
		return true;
	}
}