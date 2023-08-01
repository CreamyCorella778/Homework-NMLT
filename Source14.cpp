#include "Header1.h"
#include "Header2.h"

int testing4(Semester currSem, string email)
{
	int so_lan = 0, func = 0; bool no_good = false;
	string fname = "login.csv.txt";
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
			<< "11. Xem danh sach cac hoc sinh trong khoa hoc";
		if (so_lan > 0)
			cout << endl
			<< "12. Xem ho so ca nhan" << endl
			<< "13. Doi mat khau" << endl
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
			no_good = !addCoursetoSemester(cour, currSem);
			if (no_good)
			{
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
				break;
			}
			Node<Course>* nut = new Node<Course>; nut->init(cour);
			addLast(cour.teacher.courses, nut);
			break;
		}
		case 3:
		{
			string fname = "", cou = "", cls = ""; bool found = false; Course course;
			do
			{
				cout << "Nhap ten tep can tai len: "; getline(cin, fname);
				cout << "Nhap ma khoa hoc: "; getline(cin, cou);
				cout << "Nhap ten lop: "; getline(cin, cls);
				found = findCourse(cou, cls, currSem.number, course);
			} while (!found);
			no_good = !addStudentsToCourse(fname, course);
			if (no_good)
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
				cout << "Nhap lan luot ma khoa hoc va ten lop hoc: "; getline(cin, cou); getline(cin, cls);
				getIn4toUpdateCourse(cou, cls, option);
				done = updateCourseIn4(cou, cls, option, getIn4toUpdateCourse(option), currSem);
				if (!done)
					cout << "Loi he thong. Moi nhap lai: " << endl;
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
			no_good = !addStudentToCourse(stu, course);
			if (no_good)
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
		case 6:
		{
			cout << "Phan lay thong tin hoc sinh can duoi: " << endl;
			Student stu;
			getStudentIn4(stu);
			cout << "Phan lay thong tin cua khoa hoc can duoi hoc sinh: " << endl;
			string cou = "", cls = ""; bool found = false; Course course;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, cou);
				cout << "Nhap ten lop: "; getline(cin, cls);
				found = findCourse(cou, cls, currSem.number, course);
			} while (!found);
			no_good = !removeStudentFromCourse(stu, course);
			if (no_good)
			{
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
				break;
			}
			else
			{
				cout << "Duoi thanh cong. " << endl;
				break;
			}
		}
		case 7:
		{
			cout << "Phan lay thong tin cua khoa hoc can xoa: " << endl;
			string cou = "", cls = ""; bool found = false; Course course;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, cou);
				cout << "Nhap ten lop: "; getline(cin, cls);
				found = findCourse(cou, cls, currSem.number, course);
			} while (!found);
			no_good = !removeCourse(course, currSem);
			if (no_good)
			{
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
				break;
			}
			else
			{
				cout << "Xoa thanh cong. " << endl;
				break;
			}
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
			string cls = "";
			cout << "Nhap ten lop: "; cin >> cls; Class lop;
			Node<Class>* node = findCLass(cls);
			if (node == nullptr)
			{
				char a = 0;
				cout << "Ban co muon tao lop moi voi ten vua roi khong? Chon so thu tu tuong ung voi lua chon: " << endl
					<< "1. Co                                          2. Khong: "; cin >> a;
				if (a == 2)
				{
					cout << "Loi he thong. Chuc ban may man lan sau" << endl;
					no_good = true;
					break;
				}
				else
				{
					lop = createClass(cls);
					cout << "Tao thanh cong." << endl;
				}
			}
			else
				lop = node->data;
			cout << "Danh sach cac hoc sinh cua lop " << lop.cls << ":\n";
			viewStudents(lop);
			break;
		}
		case 11:
		{
			cout << "Phan lay thong tin cua khoa hoc can xem: " << endl;
			string cou = "", cls = ""; bool found = false; Course course;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, cou);
				cout << "Nhap ten lop: "; getline(cin, cls);
				found = findCourse(cou, cls, currSem.number, course);
				if (!found)
					cout << "Khong tim thay khoa hoc. Moi nhap lai: " << endl;
			} while (!found);
			viewStudents(course);
			break;
		}
		case 12:
			printProfileIn4(email);
			break;
		case 13:
			changePassword(fname, email);
			break;
		}
		++so_lan;
	} while (1 <= func <= 13);
	return no_good ? -1 : 0;
}

