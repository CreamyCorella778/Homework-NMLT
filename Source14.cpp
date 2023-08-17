#include "Header1.hpp"
#include "Header2.hpp"

// part 1
int testing4(Semester currSem, string email) 
{
	int func = 0; bool no_good = false;
	string fname = "";
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
			no_good = !task3();
			break;
		}
		case 3:
		{
			no_good = !task4();
			break;
		}
		case 4:
		{
			
			break;
		}
		case 5:
		{
			cout << "Phan lay thong tin hoc sinh can them: " << endl;
			Student stu;
			getStudentIn4(stu);
			cout << "Phan lay thong tin cua khoa hoc can nhan them hoc sinh: " << endl;
			string cou = "", cls = ""; bool found = false; Node<Course>* course = new Node<Course>;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, cou);
				cout << "Nhap ten lop: "; getline(cin, cls);
				course = findCourse(cou, cls, currSem.number);
			} while (!course);
			no_good = !addStudentToCourse(stu, course->data);
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
			string cou = "", cls = ""; bool found = false; Node<Course>* course = new Node<Course>;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, cou);
				cout << "Nhap ten lop: "; getline(cin, cls);
				course = findCourse(cou, cls, currSem.number);
			} while (!course);
			no_good = !addStudentToCourse(stu, course->data);
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
			string cou = "", cls = ""; bool found = false; Node<Course>* course = new Node<Course>;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, cou);
				cout << "Nhap ten lop: "; getline(cin, cls);
				course = findCourse(cou, cls, currSem.number);
			} while (!course);
			no_good = !removeCourse(course->data, currSem);
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
			if (!node)
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
			string cou = "", cls = ""; bool found = false; Node<Course>* course = new Node<Course>;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, cou);
				cout << "Nhap ten lop: "; getline(cin, cls);
				course = findCourse(cou, cls, currSem.number);
			} while (!course);
			if (!course)
			{
				cout << "Khong tim thay khoa hoc. Chuc ban may man lan sau" << endl;
				no_good = true;
			}
			viewStudents(course->data);
			break;
		}
		case 12:
			task1(email);
			break;
		}
	} while (1 <= func && func < 13);
	return no_good ? -1 : 0; // return 0 if user wants to exit the program and -1 when program has issues
}

