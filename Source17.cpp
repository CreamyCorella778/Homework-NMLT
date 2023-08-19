#include "Header1.hpp"
#include "Header2.hpp"

// part 2
int testing7(string email, Semester currSem)
{
    int func = 0; bool no_good = false;
	do
	{
		cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
			<< "1. Xem danh sach khoa hoc trong hoc ki" << endl
			<< "2. Xem danh sach cac lop nam nhat" << endl
			<< "3. Xem danh sach cac hoc sinh trong lop" << endl
			<< "4. Xem danh sach cac hoc sinh trong khoa hoc" << endl
			<< "5. Cac chuc nang khac" << endl
			<< "Cac so khac. Dang xuat: ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			viewCourses(currSem);
			break;
		}
		case 2:
		{
			cout << "Danh sach cac lop nam nay: " << endl;
			viewClasses();
			break;
		}
		case 3:
		{
			no_good = !task9();
			break;
		}
		case 4:
		{
			no_good = !task10(currSem);
			break;
		}
		case 5:
		{	
			task1(email);
			break;
		}
		}
	} while (1 <= func && func <= 5);
	return no_good ? -1 : 0; // return 0 if user wants to exit the program and -1 when program has issues
}