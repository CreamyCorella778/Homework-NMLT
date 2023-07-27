#include "Header1.h"
#include "Header2.h"

Date getDateIn4()
{
	string temp = "";
	cout << "Nhap ngay hom nay: "; cin >> temp;
	return getNS(temp);
}

