#include "Header1.hpp"
#include "Header2.hpp"

// part 1
int testing4(Semester currSem, string email) 
{
	int func = 0; bool no_good = false;
	do
	{
		no_good = false;
		cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
			<< "1. Tao mot hoc ki moi" << endl
			<< "2. Tao mot khoa hoc moi" << endl
			<< "3. Tao danh sach hoc sinh trong khoa hoc" << endl
			<< "4. Thay doi thong tin khoa hoc" << endl
			<< "5. Them mot hoc sinh vao khoa hoc" << endl
			<< "6. Duoi mot hoc sinh khoi khoa hoc" << endl
			<< "7. Xoa mot khoa hoc" << endl
			<< "8. Xem danh sach khoa hoc trong hoc ki" << endl
			<< "9. Xem danh sach cac lop nam nhat" << endl
			<< "10. Xem danh sach cac hoc sinh trong lop" << endl
			<< "11. Xem danh sach cac hoc sinh trong khoa hoc" << endl
			<< "12. Cac chuc nang khac" << endl
			<< "Cac so khac. Dang xuat: ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			task2();
			break;
		}
		case 2:
		{
			no_good = !task3(currSem);
			break;
		}
		case 3:
		{
			no_good = !task4(currSem);
			break;
		}
		case 4:
		{
			no_good = !task5(currSem);
			break;
		}
		case 5:
		{
			no_good = !task6(currSem);
			break;
		}
		case 6:
		{
			no_good = !task7(currSem);
			break;
		}
		case 7:
		{
			no_good = !task8(currSem);
			break;
		}
		case 8:
		{
			viewCourses(currSem);
			break;
		}
		case 9:
		{
			cout << "Danh sach cac lop nam nay: " << endl;
			viewClasses();
			break;
		}
		case 10:
		{
			no_good = !task9();
			break;
		}
		case 11:
		{
			no_good = !task10(currSem);
			break;
		}
		case 12:
			task1(email);
			break;
		}
	} while (1 <= func && func < 13);
	return no_good ? -1 : 0; // return 0 if user wants to exit the program and -1 when program has issues
}

