#include "Header1.hpp"
#include "Header2.hpp"

// beginning of SchoolYear
int testing5(string email, SchoolYear &sy)  
{
	int func = 0; bool no_good = false;
	do 
	{
		cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
			<< "1. Tao mot nam hoc moi" << endl
			<< "2. Tao danh sach cac lop moi" << endl
			<< "3. Them hoc sinh vao lop tu ban phim" << endl
			<< "4. Them hoc sinh vao lop tu tep tai len" << endl
			<< "5. Cac chuc nang khac" << endl
			<< "Cac so khac. Dang xuat: ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			int ys = 0, ye = 0;
			getYears(ys, ye);
			sy = createSchoolYear(ys, ye);
			cout << "Nam hoc moi tao la " << sy.schYr << endl;
			break;
		}
		case 2:
		{
			string eduProgram = ""; int start = 0, end = 0;
			getClassIn4(sy, eduProgram, start, end);
			Class* classes = createClasses(sy, eduProgram, start, end);
			cout << "Cac lop vua duoc tao la: " << endl;
			for (int i = 0; i < end - start + 1; ++i)
				cout << classes[i].cls << endl;
			break;
		}
		case 3:
		{
			Student stu;
			getStudentIn4(stu);
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
			no_good = !addStudentToClass(stu, lop);
			if (no_good)
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
			else
				cout << "Them thanh cong. " << endl;
			break;
		}
		case 4:
		{
			string fname = "";
			cout << "Nhap ten tep. Ten tep phai la ten lop: "; cin >> fname;
			no_good = !addStudentsToClass(fname);
			if (no_good)
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
			else
				cout << "Them thanh cong. " << endl;
			break;
		}
		case 5:
		{
			task1(email);
			break;
		}
		}
	} while (1 <= func && func <= 5);
	return no_good ? -1 : 0;
}