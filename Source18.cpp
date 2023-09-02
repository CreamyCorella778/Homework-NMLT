#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

// Xem ho so ca nhan & doi mat khau
int task1(string email)
{
	int func = 0;
	do
	{
		cout << "Chon so thu tu tuong ung voi chuc nang: " << endl
			<< "1. Xem ho so ca nhan" << endl
			<< "2. Doi mat khau" << endl
			<< "Cac so khac. Dang xuat: ";
		cin >> func;
		switch (func)
		{
		case 1:
		{
			printProfileIn4(email);
			break;
		}
		case 2:
		{
			cin.ignore();
			string fname = "login.csv.txt";
			changePassword(fname, email);
			break;
		}
		}
	} while (func == 1 || func == 2);
	return 0;
}

// tao hoc ki moi khi chua co
void task2()
{
	Semester curr;
	int no = 0;  SchoolYear sy; Date sd, ed;
	getSemesterIn4(no, sy, sd, ed);
	curr = createSemester(no, sy, sd, ed);
	cout << "Hoc ki vua them la: " << endl;
	viewSemester(curr);
	Node<Semester>* node = new Node<Semester>; node->init(curr);
	addLast(systems.allSemester, node);
	writeAllSemester("all_semester.txt");
}

// tao mot khoa hoc moi
bool task3(Semester currSem)
{
	Course cour; 
	getCourseIn4(cour, currSem);
	if (!cour.teacher.id.compare("not found"))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false; // neu ko tim dc giao vien -> khong tao dc khoa hoc
	}
	if (!addCoursetoSemester(cour, currSem))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false;
	}
	Node<Course>* nut = new Node<Course>; nut->init(cour);
	addLast(cour.teacher.courses, nut);
	cout << "Hoc ki vua them la: " << endl;
	viewCourse(cour);
	return true;
}

// tim kiem khoa hoc
Node<Course>* task3_5(Semester currSem)
{
	string cou = "", cls = ""; Node<Course>* course = new Node<Course>; int times = 5;
	do
	{
		cout << "Nhap ma khoa hoc: "; getline(cin, cou);
		cout << "Nhap ten lop: "; getline(cin, cls);
		course = findCourse(cou, cls, currSem.number);
		--times;
		if (!course)
			cout << "Khong tim thay khoa hoc. Moi nhap lai. Ban co " << times << " lan nhap: " << endl;
	} while (!course && times > 0);
	if (!course)
		cout << "Khong tim thay khoa hoc. Chuc ban may man lan sau." << endl;
	else
		cout << "Da tim thay khoa hoc." << endl;
	return course;
}

// nhap danh sach hoc sinh tu tep vao khoa hoc
bool task4(Semester currSem)
{
	string fname = ""; Node<Course>* course = task3_5(currSem);
	if (!course) return false;
	fname = course->data.id + "_" + course->data.lop.cls + "_" + to_string(course->data.sem.number) + ".txt";
	if (!addStudentsToCourse(fname, course->data))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false;
	}
	else
	{
		int option = 0;
		cout << "Them thanh cong. Ban co muon xem danh sach hoc sinh da them khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon:" << endl
		<< "1. Co                        2. Khong: ";
		cin >> option;
		if (option == 1)
			viewStudents(course->data);
		return true;
	}
}

// thay doi thong tin khoa hoc
bool task5(Semester currSem)
{
	string cou = "", cls = ""; int option = 0, so_lan = 5; bool done = false;
	do
	{
		getIn4toUpdateCourse(cou, cls, option);
		cin.ignore();
		Node<Course>* course = task3_5(currSem);
		if (!course)
		{
			done = false;
			break;
		}
		done = updateCourseIn4(course->data, option, getIn4toUpdateCourse(option));
		--so_lan;
		if (!done)
			cout << "Khong tim duoc khoa hoc, giao vien hoac lop. Moi nhap lai. Ban con: " << so_lan << "nhap." << endl;
	} while (!done && so_lan > 0);
	if (!done) // so_lan == 0
		return false;
	cout << "Cap nhat thanh cong. Ban co muon xem khoa hoc khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon: " << endl
		<< "1. Co                        2. Khong: ";
	cin >> option;
	if (option == 1)
		viewCourse(findCourse(cou, cls, currSem.number)->data);
	return true;
}

// them mot hoc sinh vao khoa hoc
bool task6(Semester currSem)
{
	cout << "Phan lay thong tin hoc sinh can them: " << endl;
	Student stu;
	getStudentIn4(stu);
	cout << "Phan lay thong tin cua khoa hoc can nhan them hoc sinh: " << endl;
	Node<Course>* course = task3_5(currSem);
	if (!course) return false;
	if (!addStudentToCourse(stu, course->data))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false;
	}
	else
	{
		int option = 0;
		cout << "Them thanh cong. Ban co muon xem hoc sinh moi them khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon: " << endl
		<< "1. Co                        2. Khong: ";
		cin >> option;
		if (option == 1)
			viewStudent(stu);
		return true;
	}
}

// tim hoc sinh trong khoa hoc 
Node<Student>* task6_5(Course course)
{
	string id = "";
	cout << "Nhap ma so hoc sinh cua hoc sinh can duoi: "; cin >> id;
	for (Node<Student>* i = course.stuList.head; i; i = i->next)
		if (!i->data.stuID.compare(id))
		{
			cout << "Da tim thay hoc sinh." << endl;
			return i;
		}
	cout << "Khong tim thay hoc sinh. Chuc ban may man lan sau." << endl;
	return nullptr;
}

// duoi mot hoc snh ra khoi khoa hoc
bool task7(Semester currSem)
{
	cout << "Phan lay thong tin cua khoa hoc can duoi hoc sinh: " << endl;
	Node<Course>* course = task3_5(currSem);
	if (!course) return false;
	cout << "Phan lay thong tin hoc sinh can duoi: " << endl;
	Node<Student>* node = task6_5(course->data);
	if (!node) return false;
	Student student = node->data;
	if (!removeStudentFromCourse(student, course->data))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false;
	}
	else
	{
		int option = 0;
		cout << "Duoi thanh cong. Ban co muon xem hoc sinh bi duoi khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon: " << endl
		<< "1. Co                        2. Khong: ";
		cin >> option;
		if (option == 1)
			viewStudent(student);
		return true;
	}
}

// xoa mot khoa hoc
bool task8(Semester currSem)
{
	cout << "Phan lay thong tin cua khoa hoc can xoa: " << endl;
	Node<Course>* course = task3_5(currSem);
	if (!course) return false;
	Course deleted = course->data;
	if (!removeCourse(course->data, currSem))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false;
	}
	else
	{
		int option = 0;
		cout << "Xoa thanh cong. Ban co muon xem khoa hoc vua xoa khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon: " << endl
		<< "1. Co                        2. Khong: ";
		cin >> option;
		if (option == 1)
			viewCourse(deleted);
		return true;
	}
}

// xem danh sach hoc sinh trong lop
bool task9()
{
	string cls = "";
	cout << "Nhap ten lop: "; cin >> cls;
	Node<Class>* node = findCLass(cls);
	if (!node)
	{
		int option = 0;
		cout << "Ban co muon tao lop moi voi ten vua roi khong? Chon so thu tu tuong ung voi lua chon: " << endl
			 << "1. Co                                                                       2. Khong: "; 
		cin >> option;
		if (option == 1)
		{
			node = new Node<Class>;
			node->init(createClass(cls));
			cout << "Tao thanh cong. Ban co muon xem lop moi tao khong?" << endl
			<< "Chon so thu tu tuong ung voi lua chon:" << endl
			<< "1. Co                        2. Khong: ";
			cin >> option;
			if (option == 1)
				cout << "Lop moi them la: " << node->data.cls;
			node->data.stuList.init();
			return true;
		}
		else
		{
			cout << "Loi he thong. Chuc ban may man lan sau." << endl;
			return false;
		}
	}
	cout << "Danh sach cac hoc sinh cua lop " << node->data.cls << ":\n";
	viewStudents(node->data);
	return true;
}

//xem danh sach hoc sinh trong khoa hoc
bool task10(Semester currSem)
{
	cout << "Phan lay thong tin cua khoa hoc can xem: " << endl;
	Node<Course>* course = task3_5(currSem);
	if (!course) return false;
	viewStudents(course->data);
	return true;
}

// tao mot nam hoc moi
void task11(SchoolYear &sy)
{
	int ys = 0, ye = 0;
	getYears(ys, ye);
	sy = createSchoolYear(ys, ye);
	cout << "Nam hoc moi tao la " << sy.schYr << endl;
}

// tao danh sach cac lop moi
void task12(SchoolYear &sy)
{
	string eduProgram = ""; int start = 0, end = 0;
	getClassIn4(sy, eduProgram, start, end);
	Class* classes = createClasses(sy, eduProgram, start, end);
	if (!classes)
	{
		cout << "Tao lop that bai do sai chuong trinh hoc. Chuc ban may man lan sau." << endl;
		return;
	}
	int option = 0;
	cout << "Tao thanh cong. Ban co muon xem cac lop moi tao khong?" << endl
	<< "Chon so thu tu tuong ung voi lua chon:" << endl
	<< "1. Co                        2. Khong: ";
	cin >> option;
	if (option == 1)
	{
		cout << "Cac lop vua duoc tao la: " << endl;
		for (int i = 0; i < end - start + 1; ++i)
		{
			cout << classes[i].cls << endl;
			classes[i].stuList.init();
		}
	}
}

// them hoc sinh vao lop tu ban phim
bool task13()
{
	Student stu;
	getStudentIn4(stu);
	string cls = "";  int option = 0;
	cout << "Nhap ten lop cua hoc sinh: "; getline(cin, cls);
	Node<Class>* node = findCLass(cls);
	if (!node)
	{
		cout << "Ban co muon tao lop moi voi ten vua roi khong? Chon so thu tu tuong ung voi lua chon: " << endl
			<< "1. Co                                                                        2. Khong: "; 
		cin >> option;
		if (option == 1)
		{
			node = new Node<Class>;
			node->init(createClass(cls));
			cout << "Tao thanh cong. Ban co muon xem lop moi tao khong?" << endl
			<< "Chon so thu tu tuong ung voi lua chon:" << endl
			<< "1. Co                        2. Khong: ";
			cin >> option;
			if (option == 1)
				cout << "Lop moi them la: " << node->data.cls;
			node->data.stuList.init();
			return true;
		}
		else
		{
			cout << "Loi he thong. Chuc ban may man lan sau." << endl;
			return false;
		}
	}
	if (!addStudentToClass(stu, node->data))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false;
	}
	else
	{
		cout << "Them thanh cong. Ban co muon xem hoc sinh da them khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon:" << endl
		<< "1. Co                        2. Khong: ";
		cin >> option;
		if (option == 1)
			viewStudent(stu);
		return true;
	}
}

// them danh sach hoc sinh trong lop tu tep
bool task14()
{
	string fname = "";
	cout << "Nhap ten tep. Ten tep phai la ten lop: "; cin >> fname;
	if (!addStudentsToClass(fname))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false;
	}
	else
	{
		int option = 0;
		cout << "Them thanh cong. Ban co muon xem danh sach hoc sinh moi them khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon: " << endl
		<< "1. Co                        2. Khong: ";
		cin >> option;
		if (option == 1)
		{
			Class cls = findCLass(createCLass(fname).cls)->data;
			cout << "Danh sach cac hoc sinh cua lop " << cls.cls << ":\n";
			viewStudents(cls);
		}
		return true;
	}
}

// ghi danh sach hoc sinh cua khoa hoc vao tep
bool task15(Semester currSem)
{
	cout << "Phan lay thong tin cua khoa hoc: " << endl;
	Node<Course>* course = task3_5(currSem);
	string fname = course->data.id + "_" + course->data.lop.cls + "_" + to_string(currSem.number) + ".txt"; 
	//string fname = ""; cout << "Nhap ten tep can xuat: "; getline(cin, fname); 
	if (!course) return false;
	if (!writeStudentsInCourse(fname, course->data))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false;
	}
	else
	{
		cout << "Xuat thanh cong. Kiem tra tep " << fname << " trong thu muc nay." << endl;
		return true;
	}
}

// Nhap bang diem cua mot khoa hoc tu tep
bool task16()
{
	string fname = "";
	cout << "Nhap ten tep. Ten tep phai co dang makhoahoc_tenlop_hockimay.txt: "; cin >> fname;
	if (!readScoreBoard(fname))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		return false;
	}
	else
	{
		int option = 0;
		cout << "Nhap thanh cong. Ban co muon xem bang diem cua khoa hoc nay khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon:" << endl
		<< "1. Co                        2. Khong: ";
		cin >> option;
		if (option == 1)
		{
			string* in4 = extractCId_cl_sno(fname);
			Node<Course>* c = findCourse(in4[0], in4[1], atoi(in4[2].c_str()));
			if (!c)
				return false;
			viewScoreBoards(c->data);
		}
		return true;
	}
}

// xem bang diem cua mot khoa hoc
bool task17(Semester currSem)
{
	cout << "Phan lay thong tin cua khoa hoc can xem bang diem: " << endl;
	Node<Course>* course = task3_5(currSem);
	string fname = course->data.id + "_" + course->data.lop.cls + "_" + to_string(currSem.number) + ".txt";
	if (!course) return false;
	cout << "Bang diem cua khoa hoc: " << endl;
	viewScoreBoards(course->data);
	return true;
}

// tim kiem hoc sinh trong khoa hoc
Node<Student>* task17_5()
{
	Node<Student>* node = new Node<Student>; 
	int so_lan = 5; string id = "";
	do
	{
		cout << "Nhap ma so hoc sinh: "; getline(cin, id);
		node = findStudent(id);
		--so_lan;
		if (!node)
			cout << "Khong tim thay hoc sinh. Hay nhap lai. Ban con " << so_lan << " nhap." << endl;
	} while (!node && so_lan);
	if (!node)
		cout << "Khong tim thay hoc sinh. Chuc ban may man lan sau." << endl;
	else
		cout << "Da tim thay hoc sinh." << endl;
	return node;
}

// ho tro cho phan cuoi task18: xem cac loai bang diem
void task17_75(int option, Course course, Student student, Semester currSem)
{
	switch(option)
	{
	case 1:
	{
		viewScoreboards(student);
		break;
	}
	case 2:
	{
		viewScoreBoards(course);
		break;
	}
	case 3:
	{
		for (Node<Scoreboard>* scb = student.marks.head; scb; scb = scb->next)
			if (!scb->data.course.id.compare(course.id))
				viewScoreBoard(scb->data);
		break;
	}
	case 4:
	{
		viewScoreBoards(student.cl, currSem);
		break;
	}
	case 5:
	{
		cout << "Bang diem cua cac hoc sinh hoc khoa hoc " << course.courseName << " trong lop " << student.cl.cls << ":" << endl;
		for (Node<Student>* i = student.cl.stuList.head; i; i = i->next)
			for (Node<Scoreboard>* scb = i->data.marks.head; scb; scb = scb->next)
				if (!scb->data.course.id.compare(course.id))
				{
					cout << "Hoc sinh " << i->data.firstName << " " << i->data.lastName << ", ma so " << i->data.stuID << ":" << endl;
					viewScoreBoard(scb->data);
				}
		break;
	}
	default:
		return;
	}
}

void task18_5(Class cls, Semester currSem); void task18_75(Class cls, Semester currSem);

// cap nhat bang diem cua mot hoc sinh trong khoa hoc
bool task18(Semester currSem)
{
	cout << "Phan tim kiem khoa hoc can cap nhat: " << endl;
	Node<Course>* course = task3_5(currSem);
	cout << "Phan tim kiem hoc sinh co bang diem can cap nhat:" << endl;
	Node<Student>* student = task17_5();
	if (!course || !student)
		return false;
	Node<Class>* node = findCLass(student->data.cl.cls);
	//task18_5(node->data, currSem);
	task18_75(node->data, currSem);
	countOverallGPAInClass(node->data, currSem);
	addCoursesToStaff(course->data.teacher);
 
	float* in4 = new float[4]; int* options = new int[4]; int n = 0;
	cout << "Phan nhap thong tin bang diem can cap nhat: " << endl;
	getUpdateScbIn4(options, in4, n);
	if (!updateScoreBoard(student->data, course->data, currSem, options, in4, n))
	{
		cout << "Loi he thong. Chuc ban may man lan sau." << endl;
		delete[]in4; in4 = nullptr;
		delete[]options; options = nullptr;
		return false;
	}
	else
	{
		delete[]in4; in4 = nullptr;
		delete[]options; options = nullptr;
		int option = 0;
		cout << "Cap nhat thanh cong. Ban co muon xem bang diem khong?" << endl
		<< "Chon so thu tu tuong ung voi lua chon: " << endl
		<< "1. Xem bang diem cua hoc sinh do" << endl
		<< "2. Xem bang diem cua khoa hoc do" << endl
		<< "3. Xem bang diem khoa hoc do cua hoc sinh do" << endl
		<< "4. Xem bang diem cua lop cua hoc sinh do" << endl
		<< "5. Xem bang diem khoa hoc do cua lop cua hoc sinh do" << endl
		<< "Cac so khac. Khong xem gi het: "; cin >> option;
		task17_75(option, course->data, student->data, currSem);
		return true;
	}
}

// gop 2 danh sach lien ket khoa hoc va xoa bo phan tu trung lap
void task18_15(LList<Course> &list1, LList<Course> &list2)
{
	if (list1.head == list1.tail && !list1.head)
	{
		list1 = list2;
		return;
	}
	if (list2.head == list2.tail && !list2.head)
	{
		list2 = list1;
		return;
	}
	for (Node<Course>* i = list2.head; i; i = i->next)
		if (!findCourse(i->data.id, i->data.lop.cls, i->data.sem.number, list1))
		{
			Node<Course>* node = new Node<Course>; node->init(i->data);
			addLast(list1, node);
		}
	Node<Course>* i = list2.head;
	for (Node<Course>* j = i; i; i = j)
	{
		j = j->next;
		delete i;
	}
	list2 = list1;
}

// gop 2 danh sach lien ket bang diem va xoa bo phan tu trung lap
void task18_15(LList<Scoreboard>& list1, LList<Scoreboard>& list2)
{
	if (list1.head == list1.tail && !list1.head)
	{
		list1 = list2;
		return;
	}
	if (list2.head == list2.tail && !list2.head)
	{
		list2 = list1;
		return;
	}
	for (Node<Scoreboard>* i = list2.head; i; i = i->next)
		if (!findScoreboard(i->data.student.stuID, i->data.course, list1))
		{
			Node<Scoreboard>* node = new Node<Scoreboard>; node->init(i->data);
			addLast(list1, node);
		}
		else
		{
			Node<Scoreboard>* node = findScoreboard(i->data.student.stuID, i->data.course, list1);
			if (node->data.Total <= 0) // not yet init-ed or just init-ed with full 0s
			{
				node->data.midTerm = i->data.midTerm;
				node->data.Total = i->data.Total;
				node->data.Final = i->data.Final;
				node->data.Other = i->data.Other;
			}
		}
	Node<Scoreboard>* i = list2.head;
	for (Node<Scoreboard>* j = i; i; i = j)
	{
		j = j->next;
		delete i;
	}
	list2 = list1;
}

// chuyen du lieu tu cac hoc sinh trong khoa hoc sang cac hoc sinh trong lop
void task18_5(Class cls, Semester currSem)
{
	for (Node<Course>* k = findCoursesOfClass(cls, currSem).head; k; k = k->next)
		for (Node<Student>* i = k->data.stuList.head; i; i = i->next)
		{
			Node<Student>* j = findStudent(i->data.stuID, cls);
			if (!j)
				continue;
			else
			{
				task18_15(i->data.courses, j->data.courses);
				task18_15(i->data.marks, j->data.marks);
			}
		}
	countNoInStudentList(cls.stuList);
}

// tinh semGPA hang loat
void task18_75(Class cls, Semester currSem)
{
	for (Node<Student>* i = cls.stuList.head; i; i = i->next)
		calculateSemGPA(i->data);
	writeGPAofClassInSem("gpa_22CTT2_3_2022-2023.txt", cls, currSem);
}

// xem bang diem cua mot lop
bool task19(Semester currSem)
{
	string cls = ""; int option = 0;
	cout << "Nhap ten lop: "; cin >> cls;
	Node<Class>* node = findCLass(cls);
	if (!node)
	{
		cout << "Ban co muon tao lop moi voi ten vua roi khong? Chon so thu tu tuong ung voi lua chon: " << endl
			<< "1. Co                                          2. Khong: "; 
		cin >> option;
		if (option == 1)
		{
			node = new Node<Class>;
			node->init(createClass(cls));
			cout << "Tao thanh cong. Ban co muon xem lop moi tao khong?" << endl
			<< "Chon so thu tu tuong ung voi lua chon:" << endl
			<< "1. Co                        2. Khong: ";
			cin >> option;
			if (option == 1)
				cout << "Lop moi them la: " << node->data.cls;
			return true;
		}
		else
		{
			cout << "Loi he thong. Chuc ban may man lan sau." << endl;
			return false;
		}
	}
	//task18_5(node->data, currSem);
	//task18_75(node->data, currSem);
	//countOverallGPAInClass(node->data, currSem);
	viewScoreBoards(node->data, currSem);
	return true;
}

// cac chuc nang khac cho testing5, vì dau nam hoc cung la dau hoc ki 1
bool task20(string email)
{
	int option = 0;
	cout << "Chon so thu tu tuong ung voi chuc nang:" << endl
	<< "0. Tao mot hoc ky moi." << endl
	<< "Cac so khac. Da tao hoc ki san nen chon hoc ki hien tai: "; cin >> option;
	if (!option) 
		task2();
	return !testing4(email, systems.allSemester.tail->data) ? true : false;
}