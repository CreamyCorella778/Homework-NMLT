#include "Header1.h"
#include "Header2.h"

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

int testing3(string& email)
{
	bool userType = false;  string fname = "login.csv.txt";
	int res_testing1 = testing1(userType, email);
	if (res_testing1 == 3)
	{
		int func = 0;
		Date today = getTodayIn4();
		Node<Semester>* node = identifySemesterByToday(today); 
		if (!userType)
		{
			if (node == nullptr)
			{
				do
				{
					cout << "Khong xac dinh duoc hoc ki hien tai. Ban co muon tao mot hoc ki moi khong?" << endl
						<< "Chon so thu tu tuong ung voi lua chon: " << endl
						<< "1. Co                       2. Khong: ";
					cin >> func;
				} while (!(func == 1 || func == 2));
				if (func == 1)
				{
					Semester curr;
					int no = 0;  SchoolYear sy; Date sd, ed;
					getSemesterIn4(no, sy, sd, ed);
					curr = createSemester(no, sy, sd, ed);
					cout << "Hoc ki vua them la: " << endl;
					viewSemester(curr);
					node->init(curr), addLast(systems.allSemester, node);
				}
				else
				{
					cout << "Chuc ban may man lan sau." << endl;
					do
					{
						cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
							<< "1. Xem ho so ca nhan" << endl
							<< "2. Doi mat khau" << endl
							<< "Cac so khac. Dang xuat:";
						cin >> func;
						switch (func)
						{
						case 1:
							printProfileIn4(email);
							break;
						case 2:
							changePassword(fname, email);
							break;
						}
					} while (func == 1 || func == 2);
					return 0;
				}
			}
			int part = whenInSemester(node->data, today);
			if (part < 1)
			{
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
				return -1;
			}
			else if (part == 1)
			{
				
			}
			else if (part == 3)
			{

			}
		}
	}
}