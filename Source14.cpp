#include "Header1.h"
#include "Header2.h"

int testing4(Semester currSem)
{
	int so_lan = 0, func = 0;
	do
	{
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
			<< "11. Xem danh sach cac hoc sinh trong khoa hoc";
		if (so_lan > 0)
			cout << endl
			<< "12. Xem ho so ca nhan" << endl
			<< "13. Doi mat khau" << endl
			<< "14. Cac chuc nang khac" << endl
			<< "Cac so khac. Dang xuat:";
		else
			cout << ": ";
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
			getCourseIn4(cour, currSem);
			addCoursetoSemester(cour, currSem);
			Node<Course>* nut = new Node<Course>; nut->init(cour);
			addLast(cour.teacher.courses, nut);
			break;
		}
		case 3:
		{
			string fname = "", cou = "", cls = ""; bool found = false; Course course;
			do
			{
				cout << "Nhap ten tep can tai len: "; cin >> fname;
				cout << "Nhap ma khoa hoc: "; getline(cin, cou);
				cout << "Nhap ten lop: "; getline(cin, cls);
				found = findCourse(cou, cls, currSem.number, course);
			} while (!found);
			found = addStudentsToCourse(fname, course);
			if (!found)
			{
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
				break;
			}
			else
			{
				cout << "Them thanh cong. " << endl;
				break;
			}
		}
		case 4:
		{
			string cou = "", cls = ""; int option = 0; bool done = false;
			do 
			{
				cout << "Nhap lan luot ma khoa hoc va ten lop hoc: "; cin >> cou >> cls;
				getIn4toUpdateCourse(cou, cls, option);
				done = updateCourseIn4(cou, cls, option, getIn4toUpdateCourse(option), currSem);
				if (!done)
					cout << "Loi he thong. Moi nhap lai" << endl;
			} while (!done);
			break;
		}
		case 5:
		{
			cout << "Phan lay thong tin hoc sinh can them: " << endl;
			Student stu;
			getStudentIn4(stu);
			cout << "Phan lay thong tin cua khoa hoc can nhan them hoc sinh: " << endl;
			string cou = "", cls = ""; bool found = false; Course course;
			do
			{
			cout << "Nhap ma khoa hoc: "; getline(cin, cou);
			cout << "Nhap ten lop: "; getline(cin, cls);
			found = findCourse(cou, cls, currSem.number, course);
			} while (!found);
			found = addStudentToCourse(stu, course);
			if (!found)
				cout << "Loi he thong. Chuc ban may man lan sau." << endl;
			break;
		}
		case 6:

		}
		++so_lan;
	} while (true /*????????????? watch out this one*/);
}

