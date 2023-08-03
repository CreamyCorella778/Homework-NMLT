#include "Header1.h"
#include "Header2.h"

Date getTodayIn4()
{
	string temp = "";
	cout << "Nhap ngay hom nay: "; cin >> temp;
	return getNS(temp);
}

int testing2(string &email)
{
	bool userType = false;  string fname = "login.csv.txt";
	int res_testing1 = testing1(userType, email);
	if (res_testing1 == 3)
	{
		int func = 0;
		Date today = getTodayIn4();
		if (userType)
		{
			Node<Semester>* node = identifySemesterByToday(today);
			if (node == nullptr)
			{
				cout << "Loi he thong. Chuc ban may man lan sau." << endl;
				return -1;
			}
			Semester curr = node->data;
			Student stu = extractStudentFromEmail(email);
			cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
				<< "1. Xem danh sach khoa hoc dang theo" << endl
				<< "2. Xem bang diem cac khoa hoc: ";
			cin >> func;
			switch (func)
			{
			case 1:
				viewCourses(stu, curr);
				break;
			case 2:
				viewScoreboards(stu);
				break;
			}
			do
			{
				cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
					<< "1. Xem danh sach khoa hoc dang theo" << endl
					<< "2. Xem bang diem cac khoa hoc" << endl
					<< "3. Xem ho so ca nhan" << endl
					<< "4. Doi mat khau" << endl
					<< "Cac so khac. Dang xuat" << endl;
				cin >> func;
				switch (func)
				{
				case 1:
					viewCourses(stu, curr);
					break;
				case 2:
					viewScoreboards(stu);
					break;
				case 3:
					printProfileIn4(email);
					break;
				case 4:
					changePassword(fname, email);
					break;
				}
			} while (1 <= func <= 4);
			return 0;
		}
	}
}

int testing6(string email, Semester currSem) // part 3
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
			<< "9. Xem danh sach cac hoc sinh trong khoa hoc";
		if (so_lan > 0)
			cout << "10. Xem ho so ca nhan" << endl
			<< "11. Doi mat khau" << endl
			<< "Cac so khac. Dang xuat: ";
		else
			cout << ": ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			string course = "", cls = "", fname = ""; int so_lan = 5; Course cour;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, course);
				cout << "Nhap ma lop cua khoa hoc dang day: "; getline(cin, cls);
				fname = course + cls + to_string(currSem.number) + ".txt";
				no_good = !findCourse(course, cls, currSem.number, cour);
				--so_lan;
				if (no_good)
					cout << "Khong tim thay khoa hoc. Hay nhap lai. Ban con " << so_lan << " nhap." << endl;
			} while (no_good && so_lan > 0);
			if (no_good)
			{
				cout << "Khong tim thay khoa hoc. Chuc ban may man lan sau. " << endl;
				return -1;
			}
			no_good = !writeStudentsInCourse(fname, cour);
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
			string course = "", cls = "", fname = ""; int so_lan = 5; Course cour;
			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, course);
				cout << "Nhap ten lop cua khoa hoc dang day: "; getline(cin, cls);
				fname = course + cls + to_string(currSem.number) + ".txt";
				no_good = !findCourse(course, cls, currSem.number, cour);
				--so_lan;
				if (no_good)
					cout << "Khong tim thay khoa hoc. Hay nhap lai. Ban con " << so_lan << " nhap." << endl;
			} while (no_good && so_lan > 0);
			if (no_good)
			{
				cout << "Khong tim thay khoa hoc. Chuc ban may man lan sau. " << endl;
				return -1;
			}
			viewScoreBoards(cour);
			break;
		}
		case 4:
		{
			Node<Student>* node = new Node<Student>; 
			string course = "", cls = "", fname = ""; int so_lan = 5; Course cour;

			do
			{
				cout << "Nhap ma khoa hoc: "; getline(cin, course);
				cout << "Nhap ma lop cua khoa hoc dang day: "; getline(cin, cls);
				no_good = !findCourse(course, cls, currSem.number, cour);
				--so_lan;
				if (no_good)
					cout << "Khong tim thay khoa hoc. Hay nhap lai. Ban con " << so_lan << " nhap." << endl;
			} while (no_good && so_lan > 0);
			if (no_good)
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
			getUpdateScbIn4(node->data, cour, option, in4, n, currSem.number);
			no_good = !updateScoreBoard(node->data, cour, option, in4, n);
			if (no_good)
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
			else
				cout << "Cap nhat thanh cong" << endl;
			break;
		}
		case 5:
		{
			string cls = ""; int so_lan = 5; Node<Class>* node = new Node<Class>;
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

			break;
		}
		case 7:
		{

			break;
		}
		case 8:
		{

			break;
		}
		case 9:
		{

			break;
		}
		case 10:
			printProfileIn4(email);
			break;
		case 11:
			string fname = "login.csv.txt";
			changePassword(fname, email);
			break;
		}

	} while (1 <= func <= 11);
	return no_good ? -1 : 0;
}