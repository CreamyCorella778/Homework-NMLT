#include "Header1.hpp"
#include "Header2.hpp"

// part 2
int testing7(string email, Semester currSem)
{
    int func = 0; bool no_good = false;
	do
	{
		cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
			<< "1. Xem danh sach khoa hoc trong hoc ki" << endl
			<< "2. Xem danh sach cac lop nam nhat" << endl
			<< "3. Xem danh sach cac hoc sinh trong lop" << endl
			<< "4. Xem danh sach cac hoc sinh trong khoa hoc" << endl
			<< "5. Cac chuc nang khac" << endl
			<< "Cac so khac. Dang xuat: ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			viewCourses(currSem);
			break;
		}
		case 2:
		{
			cout << "Danh sach cac lop nam nay: " << endl;
			viewClasses();
			break;
		}
		case 3:
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
		case 4:
		{
			cout << "Phan lay thong tin cua khoa hoc can xem: " << endl;
			string course = "", cls = "", fname = ""; int so_lan = 5; Node<Course>* cour = new Node<Course>;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, course);
				cout << "Nhap ten lop cua khoa hoc dang day: "; getline(cin, cls);
				fname = course + cls + to_string(currSem.number) + ".txt";
				cour = findCourse(course, cls, currSem.number);
				--so_lan;
				if (!cour)
					cout << "Khong tim thay khoa hoc. Hay nhap lai. Ban con " << so_lan << " nhap." << endl;
			} while (!cour && so_lan > 0);
			if (!cour)
			{
				cout << "Khoa hoc khong ton tai! Chuc ban may man lan sau." << endl; no_good = false; break;
			}
			viewStudents(cour->data);
			break;
		}
		case 5:
			task1(email);
			break;
		}
	} while (1 <= func && func <= 5);
	return no_good ? -1 : 0; // return 0 if user wants to exit the program and -1 when program has issues
}