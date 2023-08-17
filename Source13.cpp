#include "Header1.hpp"
#include "Header2.hpp"

/***************************************
Assume that a semester is divided into 3 equal parts: 
Part 1 = "the beginning of a semester"
Part 2 = other
Part 3 = "the end of a semester"
****************************************/

int whenInSemester(Semester sem, Date today) // part 1 = 1, part 2 = 2, part 3 = 3
{
	Date* parts = divideSemester(sem);
	for (int i = 0; i < 3; ++i)
		if (compareDate(parts[i], today) == 1 && compareDate(today, parts[i + 1]) == 1)
		{
			delete[]parts;
			parts = nullptr;
			return i + 1;
		}
	delete[]parts;
	parts = nullptr;
	return -1;
}

bool whenInSchoolYear(Date today) // true = "the beginning of the school year" (around September), false = otherwise
{
	return (today.month == 9 || (today.day < 16 && today.month == 10));
}

// final edition for teacher/staff
int testing3(string& email)
{
	Date today = getTodayIn4();
	Node<Semester>* node = identifySemesterByToday(today);
	if (!node)
	{
		int func = 0;
   		cout << "Khong xac dinh duoc hoc ki hien tai. Ban co muon tao mot hoc ki moi khong?" << endl
			<< "Chon so thu tu tuong ung voi lua chon: " << endl
			<< "1. Co                       2. Khong: ";
    	cin >> func;
		if (func == 1)
			task2();
		return task1(email);
	}
	int part = whenInSemester(node->data, today); bool beginningSchY = whenInSchoolYear(today);
	if (part < 1)
	{
		cout << "Loi he thong. Chuc ban may man lan sau" << endl;
		return -1;
	}
	else if (beginningSchY)
		return testing5(email, node->data.sy);
	else 
		switch (part)
		{
		case 1:
			return testing4(node->data, email);
		case 2:
			return testing7(email, node->data);
		case 3:
			return testing6(email, node->data);
		default:
			return -1;
		}
}

void main3()
{
	string email = "22120064@staff.hcmuf.edu.vn";
	cout << testing3(email);
}