#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

// part 3
int testing6(string email, Semester currSem)
{
	int func = 0; bool no_good = false;
	do
	{
		cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
			<< "1. Xuat (Ghi) danh sach hoc sinh trong khoa hoc vao tep" << endl
			<< "2. Nhap bang diem cua mot khoa hoc" << endl
			<< "3. Xem bang diem cua mot khoa hoc" << endl
			<< "4. Cap nhat diem cua hoc sinh trong khoa hoc" << endl
			<< "5. Xem bang diem cua lop" << endl
			<< "6. Xem danh sach khoa hoc trong hoc ki" << endl
			<< "7. Xem danh sach cac lop nam nhat" << endl
			<< "8. Xem danh sach cac hoc sinh trong lop" << endl
			<< "9. Xem danh sach cac hoc sinh trong khoa hoc" << endl
			<< "10. Cac chuc nang khac" << endl
			<< "Cac so khac. Dang xuat: ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			no_good = !task15(currSem);
			break;
		}
		case 2:
		{
			no_good = !task16();
			break;
		}
		case 3:
		{
			no_good = !task17(currSem);
			break;
		}
		case 4:
		{
			no_good = !task18(currSem);
			break;
		}
		case 5:
		{
			no_good = !task19(currSem);
			break;
		}
		case 6:
		{
			viewCourses(currSem);
			break;
		}
		case 7:
		{
			cout << "Danh sach cac lop nam nay: " << endl;
			viewClasses();
			break;
		}
		case 8:
		{
			no_good = !task9();
			break;
		}
		case 9:
		{
			no_good = !task10(currSem);
			break;
		}
		case 10:
		{
			task1(email);
			break;
		}
		}
	} while (1 <= func && func <= 10);
	return no_good ? -1 : 0; // return 0 if user wants to exit the program and -1 when program has issues
}