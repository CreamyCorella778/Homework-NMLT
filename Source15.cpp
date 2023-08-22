#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

// beginning of SchoolYear
int testing5(string email, SchoolYear &sy)  
{
	int func = 0; bool no_good = false;
	do 
	{
		cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
			<< "1. Tao mot nam hoc moi" << endl
			<< "2. Tao danh sach cac lop moi" << endl
			<< "3. Them hoc sinh vao lop tu ban phim" << endl
			<< "4. Them hoc sinh vao lop tu tep tai len" << endl
			<< "5. Cac chuc nang khac" << endl
			<< "Cac so khac. Dang xuat: ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			task11(sy);
			break;
		}
		case 2:
		{
			task12(sy);
			break;
		}
		case 3:
		{
			no_good = !task13();
			break;
		}
		case 4:
		{
			no_good = !task14();
			break;
		}
		case 5:
		{
			task1(email);
			break;
		}
		}
	} while (1 <= func && func <= 5);
	return no_good ? -1 : 0;
}