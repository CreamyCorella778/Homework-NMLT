#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

Date getTodayIn4()
{
	string temp = "";
	cout << "Nhap ngay hom nay: "; cin >> temp;
	return getNS(temp);
}

bool writeAllSemester(string fname) // fname = all_semester.txt // fname might be changed unexpectedly
{
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (!fp.is_open() || (systems.allSemester.head == systems.allSemester.tail && systems.allSemester.head == nullptr))
		return false;
	else
	{
		fp << "Semester number,School year,Start date,End date\n";
		for (Node<Semester>* i = systems.allSemester.head; i != nullptr; i = i->next)
		{
			fp << i->data.number << ","
				<< i->data.sy.schYr << ","
				<< i->data.startDate.day << "/" << i->data.startDate.month << "/" << i->data.startDate.year << ","
				<< i->data.endDate.day << "/" << i->data.endDate.month << "/" << i->data.endDate.year;
			if (i->next)
				fp << "\n";
		}
		fp.close();
		return true;
	}
}

bool readAllSemester(string fname)
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string container = "";
		getline(fp, container, '\n');
		systems.allSemester.init();
		while (getline(fp, container, ','))
		{
			Semester a;
			a.number = atoi(container.c_str());
			getline(fp, a.sy.schYr, ','); a.sy = createSchoolYear(a.sy.schYr);
			getline(fp, container, ','); a.startDate = getNS(container);
			getline(fp, container, '\n'); a.endDate = getNS(container);
			Node<Semester>* node = new Node<Semester>; node->init(a);
			addLast(systems.allSemester, node);
		}
		fp.close();
		return true;
	}
}

void viewSemester(Semester sem)
{
	cout << "Hoc ki " << sem.number << ", thuoc nam hoc " << sem.sy.schYr << endl;
	cout << "Bat dau tu " << sem.startDate.day << "/" << sem.startDate.month << "/" << sem.startDate.year
		<< " den " << sem.endDate.day << "/" << sem.endDate.month << "/" << sem.endDate.year;
	cout << endl;
}

int Check_Nhuan(Date yyyy)
{
	if (((yyyy.year % 4 == 0) && (yyyy.year % 100 != 0)) || (yyyy.year % 400 == 0))
		return 1;
	else
		return 0;
}

int ThuTu(Date theyt)
{
	int ThuTu = 0;
	int ngay_trong_thang[13] = { 0, 31, 28 + Check_Nhuan(theyt), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	//Theo thu tu trong mang tu trai sang phai: so ngay trong thang 0, 1, 2,..., 12 
	for (int i = 0; i <= 12; i++)
		if (i == theyt.month)
		{
			for (int j = 0; j < i; j++)
				ThuTu = ThuTu + ngay_trong_thang[j];
			ThuTu = ThuTu + theyt.day;
			break;
		}
		else
			continue;
	return ThuTu;
}

//dey1 > dey2 => -1; dey1 = dey2 => 0; dey1 < dey2 => 1
int compareDate(Date dey1, Date dey2) 
{
	if (dey1.year > dey2.year)
		return -1;
	else
	{
		if (dey1.year < dey2.year)
			return 1;
		else
		{
			if (ThuTu(dey1) > ThuTu(dey2))
				return -1;
			else
			{
				if (ThuTu(dey1) < ThuTu(dey2))
					return 1;
				else
					return 0;
			}
		}
	}
}

Node<Semester>* identifySemesterByToday(Date today)
{
	for (Node<Semester>* i = systems.allSemester.head; i != nullptr; i = i->next)
		if (compareDate(today, i->data.startDate) == -1 && compareDate(today, i->data.endDate) == 1)
		{
			Node<Semester>* node = new Node<Semester>; node->init(i->data);
			return node;
		}
	return nullptr;
}

int dayOfWeek(int d, int m, int y) 
{
	y -= (14 - m) / 12;
	m += 12 * ((14 - m) / 12) - 2;
	return (d + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
}

int dayOfWeek(Date date)
{
	return dayOfWeek(date.day, date.month, date.year);
}

int* divideInto3Parts(int a, int b)
{
	int* parts = new int[4];
	int step = b > a ? (b - a) / 3 : (a - b) / 3;
	parts[0] = b > a ? a : b; parts[1] = parts[0] + step; parts[2] = parts[1] + step; parts[3] = b > a ? b : a;
	return parts;
}

Date Reverse_ThuTu(int yyyy, int n)
{
	Date date = {1, 1, yyyy};
	int ngay_trong_thang[13] = { 0, 31, 28 + Check_Nhuan(date), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	for (int i = 1; true; i++)
		if (n <= ngay_trong_thang[i])
		{
			date = { n, i, yyyy };
			break;
		}
		else
			n = n - ngay_trong_thang[i];
	return date;
}

Date* divideSemester(Semester sem)
{
	Date* parts = new Date[4];
	int thutu_start = ThuTu(sem.startDate),
		thutu_end = ThuTu(sem.endDate),
		dayOfW_start = dayOfWeek(sem.startDate),
		dayOfW_end = dayOfWeek(sem.endDate);
	int* parts_thutu = divideInto3Parts(thutu_start,
		thutu_end < thutu_start ? thutu_end + 365 + Check_Nhuan(sem.startDate) : thutu_end);
	parts_thutu[1] += ((0 < dayOfW_start + 1) && (dayOfW_start + 1 < 5)) ? 
		1 - dayOfW_start : 
		(dayOfW_start == 0 ? 1 : 8 - dayOfW_start);
	parts_thutu[2] += ((0 < dayOfW_start + 1) && (dayOfW_start + 1 < 5)) ? 
		1 - dayOfW_end :
		(dayOfW_end == 0 ? 1 : 8 - dayOfW_end);
	for (int i = 0; i < 4; ++i)
		parts[i] = Reverse_ThuTu(sem.startDate.year, 
			parts_thutu[i] > 365 + Check_Nhuan(sem.startDate) ? 
			parts_thutu[i] - 365 - Check_Nhuan(sem.startDate) : parts_thutu[i]);
	return parts;
}

