#include "Header1.h"
#include "Header2.h"

Date getTodayIn4()
{
	string temp = "";
	cout << "Nhap ngay hom nay: "; cin >> temp;
	return getNS(temp);
}

int testing2(string &email)
{
	bool userType = false;  string fname = "login.csv.txt";
	int res_testing1 = testing1(userType, email);
	if (res_testing1 == 3)
	{
		int func = 0;
		Date today = getTodayIn4();
		Semester curr = identifySemesterByToday(today)->data;
		if (userType)
		{
			Student stu = extractStudentFromEmail(email);
			cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
				<< "1. Xem danh sach khoa hoc dang theo" << endl
				<< "2. Xem bang diem cac khoa hoc: ";
			cin >> func;
			switch (func)
			{
			case 1:
				viewCourses(stu, curr);
				break;
			case 2:
				viewScoreboards(stu);
				break;
			}
			do
			{
				cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
					<< "1. Xem danh sach khoa hoc dang theo" << endl
					<< "2. Xem bang diem cac khoa hoc" << endl
					<< "3. Xem ho so ca nhan" << endl
					<< "4. Doi mat khau" << endl
					<< "Cac so khac. Dang xuat" << endl;
				cin >> func;
				switch (func)
				{
				case 1:
					viewCourses(stu, curr);
					break;
				case 2:
					viewScoreboards(stu);
					break;
				case 3:
					printProfileIn4(email);
					break;
				case 4:
					changePassword(fname, email);
					break;
				}
			} while (1 <= func <= 4);
			return 0;
		}
	}
}
