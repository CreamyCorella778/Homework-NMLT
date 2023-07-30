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
		if (!userType)
		{
			Node<Semester>* node = identifySemesterByToday(today); Semester curr;
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
					int no = 0;  SchoolYear sy; Date sd, ed;
					getSemesterIn4(no, sy, sd, ed);
					curr = createSemester(no, sy, sd, ed);
					cout << "Hoc ki vua them la: " << endl;
					viewSemester(curr);
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
			else
				curr = node->data;
			int part = whenInSemester(curr, today);
			if (part < 1)
			{
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
				return -1;
			}
			else if (part == 1)
			{
				cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
					<< "1. Tao mot hoc ki moi" << endl
					<< "2. Tao mot khoa hoc moi" << endl
					<< "3. Tao danh sach hoc sinh trong khoa hoc" << endl
					<< "4. Thay doi thong tin khoa hoc" << endl
					<< "5. Them 1 hoc sinh vao khoa hoc" << endl
					<< "6. Duoi 1 hoc sinh khoi khoa hoc" << endl
					<< "7. Xoa 1 khoa hoc" << endl
					<< "8. Xem danh sach khoa hoc trong hoc ki" << endl
					<< "9. Xem danh sach cac lop nam nhat" << endl
					<< "10. Xem danh sach cac hoc sinh trong lop" << endl
					<< "11. Xem danh sach cac hoc sinh trong khoa hoc" << endl;
				cin >> func;
				switch (func)
				{
				case 1:
				{
					int no = 0;  SchoolYear sy; Date sd, ed;
					getSemesterIn4(no, sy, sd, ed);
					Semester sem = createSemester(no, sy, sd, ed);
					cout << "Hoc ki vua them la: " << endl;
					viewSemester(sem);
					break;
				}
				case 2:
				{
					Course cour; 
					getCourseIn4(cour, curr);

				}
				}
			}
		}
	}
}