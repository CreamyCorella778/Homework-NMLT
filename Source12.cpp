#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

// userType == 1 => Student
int testing2(string email)
{
	int func = 0;
	Date today = getTodayIn4();
	Node<Semester>* node = identifySemesterByToday(today);
	Node<Student>* n0de = extractStudentFromEmail(email);
	if (!node || !n0de)
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return -1;
	}
	Semester curr = node->data; Student stu = n0de->data; 
	do
	{
		cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
			<< "1. Xem danh sach khoa hoc dang theo" << endl
			<< "2. Xem bang diem cac khoa hoc" << endl
			<< "3. Cac chuc nang khac" << endl
			<< "Cac so khac. Dang xuat: ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			viewCourses(stu, curr);
			break;
		}
		case 2:
		{
			viewScoreboards(stu);
			break;
		}
		case 3:
		{
			task1(email);
			break;
		}
		}
	} while (1 <= func && func <= 3);
	return 0;
}

void main2()
{
	string email = "22120064@student.hcmuf.edu.vn"; 
	cout << testing2(email);
}