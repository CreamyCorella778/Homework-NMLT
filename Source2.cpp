#include "Header1.h"
#include "Header2.h"

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

void getClassIn4(SchoolYear& sy, string& eduProg, int& start, int& end)
{
	int year;
	cout << "Nhap nam nhap hoc cua hoc sinh nam nay: "; cin >> year;
	sy = createSchoolYear(year, year + 1);
	cout << "Chon so thu tu tuong ung voi loai chuong trinh day hoc: " << endl
		<< "1. APCS" << endl
		<< "2. CLC" << endl
		<< "3. Viet-Phap" << endl
		<< "4. Chuan, dai tra" << endl
		<< "5. Tien tien, de an" << endl;
	int n = 0;
	cin >> n;
	switch (n)
	{
	case 1:
		eduProg = "APCS";
		break;
	case 2:
		eduProg = "CLC";
		break;
	case 3:
		eduProg = "VP";
		break;
	case 4:
		eduProg = "CTT";
		break;
	case 5:
		eduProg = "DA";
		break;
	default:
		cout << "Nhap sai roi. Chuc ban may man lan sau.";
		return;
	}
	cout << "So thu tu cua lop bat dau tu dau?:"; cin >> start;
	cout << "Can tao bao nhieu lop?: "; cin >> end;
	end = start + end - 1;
}

Class* createClasses(SchoolYear sy, string eduProg, int start, int end)
{
	Class* a = new Class[end - start + 1];
	for (int i = 0; i < end - start + 1; ++i)
	{
		a[i].eduProgr = eduProg;
		a[i].year = sy;
		a[i].no = start + i;
		a[i].cls = to_string(sy.yStart % 100).append(eduProg).append(to_string(start + i));
		Node<Class>* b; b->init(a[i]);
		addLast(systems.allClass, b);
	}
	return a;
}

string extractEduProg(string fname) // Assume that the file name part is the class name
{
	string ep = "\0";
	for (int i = 0; i < fname.size(); ++i)
		if (isalpha(fname.at(i)))
			ep.push_back(fname.at(i));
		else if (fname.at(i) - '.' == 0)
			break;
	return ep;
}

SchoolYear extractSchoolYear(string fname)
{
	string b; b.assign(fname, 2);
	int c = atoi(b.c_str());
	if (c >= 77)
		return createSchoolYear(1900 + c, 1901 + c);
	else
		return createSchoolYear(2000 + c, 2001 + c);
}

int extractNo(string fname)
{
	string a;  a.assign(fname, 2 + extractEduProg(fname).length(), fname.length() - 2 - 4 - extractEduProg(fname).length());
	return atoi(a.c_str());
}

Class createClass(string cl)
{
	Class a;
	a.eduProgr = extractEduProg(cl);
	a.year = extractSchoolYear(cl);
	a.no = extractNo(cl);
	a.cls = cl;
	return a;
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

bool addStudentsFromCSV(string fname, int& n, Class &lop)
{
	lop.eduProgr = extractEduProg(fname);
	lop.year = extractSchoolYear(fname);
	lop.no = extractNo(fname);
	ifstream fp;
	fp.open(fname, ios::in);
	if (fp.is_open() == false)
		return false;
	else
	{
		n = countLinesInCSV(fname) - 1;
		string container; getline(fp, container, '\n');
		while (fp.eof() == false)
		{
			Student stu;
			getline(fp, container, ','); stu.no = atoi(container.c_str());
			getline(fp, stu.stuID, ',');
			getline(fp, stu.firstName, ',');
			getline(fp, stu.lastName, ',');
			getline(fp, container, ',');
			if (container.compare("nam") == 0 || container.compare("Nam") == 0)
				stu.gender = true;
			else
				stu.gender = false;
			getline(fp, container, ',');
			stu.birth = getNS(container);
			getline(fp, stu.socialID, '\n');
			Node<Student>* node; node->init(stu);
			addLast(lop.stuList, node);
		}
		fp.close();
		return true;
	}
}

