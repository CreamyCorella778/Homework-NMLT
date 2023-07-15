#include "Header1.h"

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
	return sem;
}

string* extractCId_cl_sno_sy(string fname) // CSV file is courseid_classname_semnumber_schoolyear.txt
{
	int j = 0; string* idAndName = new string[4];
	for (int i = 0; i < 4; ++i)
		for (j; fname[j] - '_' == 0 || fname[j] - '.' == 0; ++j)
			idAndName[i].push_back(fname[j]);
	return idAndName;
}

void getCourseIn4(Course &a)
{
	cout << "Nhap ma hoc phan: "; getline(cin, a.id);
	cout << "Nhap ten hoc phan: "; getline(cin, a.courseName);
	cout << "Nhap ten giao vien chinh day: "; getline(cin, a.teacher);
	cout << "Nhap so tin chi: "; cin >> a.credits;
	cout << "Nhap so hoc sinh toi da trong khoa hoc: "; cin >> a.capacity;
	string container;
	cout << "Nhap ten lop cua hoc phan: "; getline(cin, container); a.lop = createClass(container);
	cout << "Nhap thu trong tuan cua hoc phan, tu thu 2 den thu 8 (chu nhat): "; cin >> a.dayInWeek;
	cout << "Nhap tiet hoc trong ngay cua hoc phan:" << endl
		<< "tiet 1 bat dau luc 7:30" << endl
		<< "tiet 2 bat dau luc 9:30" << endl
		<< "tiet 3 bat dau luc 13:30" << endl
		<< "tiet 4 bat dau luc 15 30";
	cin >> a.session;
}

void addCoursetoSemester(string fname) // CSV file is semesternumber_schoolyear.txt
{

}