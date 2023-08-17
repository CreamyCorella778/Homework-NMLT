#include "Header1.hpp"
#include "Header2.hpp"

// part 3
int testing6(string email, Semester currSem)
{
	int so_lan = 0, func = 0; bool no_good = false;
	do
	{
		cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
			<< "1. Xuat danh sach hoc sinh trong khoa hoc" << endl
			<< "2. Nhap bang diem cua mot khoa hoc" << endl
			<< "3. Xem bang diem cua mot khoa hoc" << endl
			<< "4. Cap nhat diem cua hoc sinh trong khoa hoc" << endl
			<< "5. Xem bang diem cua lop" << endl
			<< "6. Xem danh sach khoa hoc trong hoc ki" << endl
			<< "7. Xem danh sach cac lop nam nhat" << endl
			<< "8. Xem danh sach cac hoc sinh trong lop" << endl
			<< "9. Xem danh sach cac hoc sinh trong khoa hoc" << endl
			<< "10. Cac chuc nang khac" << endl
			<< "Cac so khac. Dang xuat: ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			string course = "", cls = "", fname = ""; so_lan = 5; Node<Course>* cour = new Node<Course>;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, course);
				cout << "Nhap ma lop cua khoa hoc dang day: "; getline(cin, cls);
				fname = course + cls + to_string(currSem.number) + ".txt";
				cour = findCourse(course, cls, currSem.number);
				--so_lan;
				if (!cour)
					cout << "Khong tim thay khoa hoc. Hay nhap lai. Ban con " << so_lan << " nhap." << endl;
			} while (!cour && so_lan > 0);
			if (!cour)
			{
				cout << "Khong tim thay khoa hoc. Chuc ban may man lan sau. " << endl;
				no_good = true;
				break;
			}
			no_good = !writeStudentsInCourse(fname, cour->data);
			if (no_good)
			{
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
				break;
			}
			else
			{
				cout << "Xuat thanh cong. Kiem tra tep " << fname << " trong thu muc nay." << endl;
				break;
			}
		}
		case 2:
		{
			string fname = "";
			cout << "Nhap ten tep. Ten tep phai co dang makhoahoc_tenlop_hockimay.txt: "; cin >> fname;
			no_good = !readScoreBoard(fname);
			if (no_good)
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
			else
				cout << "Nhap thanh cong. " << endl;
			break;
		}
		case 3:
		{
			string course = "", cls = "", fname = ""; so_lan = 5; Node<Course>* cour = new Node<Course>;
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
				cout << "Khong tim thay khoa hoc. Chuc ban may man lan sau. " << endl;
				no_good = true;
				break;
			}
			viewScoreBoards(cour->data);
			break;
		}
		case 4:
		{
			Node<Student>* node = new Node<Student>; 
			string course = "", cls = "", fname = ""; so_lan = 5; Node<Course>* cour = new Node<Course>;
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
				cout << "Khong tim thay khoa hoc. Chuc ban may man lan sau. " << endl;
				return -1;
			}
			so_lan = 5;
			do
			{
				cout << "Nhap ma so hoc sinh: "; getline(cin, course);
				node = findStudent(course);
				--so_lan;
				if (node == nullptr)
					cout << "Khong tim thay hoc sinh. Hay nhap lai. Ban con " << so_lan << " nhap." << endl;
			} while (node == nullptr && so_lan > 0);
			if (no_good)
			{
				cout << "Khong tim thay hoc sinh. Chuc ban may man lan sau. " << endl;
				return -1;
			}
			float* in4 = new float[4]; int* option = new int[4]; int n = 0;
			getUpdateScbIn4(option, in4, n);
			no_good = !updateScoreBoard(node->data, cour->data, currSem, option, in4, n);
			if (no_good)
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
			else
				cout << "Cap nhat thanh cong" << endl;
			break;
		}
		case 5:
		{
			string cls = ""; so_lan = 5; Node<Class>* node = new Node<Class>;
			do
			{
				cout << "Nhap ten lop: "; getline(cin, cls);
				node = findCLass(cls);
				--so_lan;
				if (node == nullptr)
					cout << "Khong tim thay lop. Hay nhap lai. Ban con " << so_lan << " nhap." << endl;
			} while (node == nullptr && so_lan > 0);
			if (node == nullptr)
			{
				cout << "Khong tim thay lop. Chuc ban may man lan sau. " << endl;
				return -1;
			}
			viewScoreBoards(node->data, currSem);
			break;
		}
		case 6:
		{
			viewCourses(currSem);
			break;
		}
		case 7:
		{
			cout << "Danh sach cac lop nam nay: " << endl;
			viewClasses();
			break;
		}
		case 8:
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
		case 9:
		{
			cout << "Phan lay thong tin cua khoa hoc can xem: " << endl;
			string course = "", cls = "", fname = ""; so_lan = 5; Node<Course>* cour = new Node<Course>;
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
					cout << "Khong tim thay khoa hoc. Moi nhap lai: " << endl;
			viewStudents(cour->data);
			break;
		}
		case 10:
			task1(email);
			break;
		}
	} while (1 <= func && func <= 10);
	return no_good ? -1 : 0; // return 0 if user wants to exit the program and -1 when program has issues
}