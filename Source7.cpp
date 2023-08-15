#include "Header1.hpp"
#include "Header2.hpp"

bool addStudentsToCourse(string fname, Course &cour)  // fname = courseid_classname_semnumber.txt
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (fp.is_open() == false)
		return false;
	else
	{
		string container = ""; getline(fp, container, '\n');
		while (fp.eof() == false)
		{
			Student stu;
			getline(fp, container, ','); stu.no = atoi(container.c_str());
			getline(fp, stu.stuID, ',');
			getline(fp, stu.firstName, ',');
			getline(fp, stu.lastName, ',');
			getline(fp, container, ',');
			if (stricmp("nam", container.c_str()) == 0)
				stu.gender = true;
			else
				stu.gender = false;
			getline(fp, container, ',');
			stu.birth = getNS(container);
			getline(fp, stu.socialID, ',');
			getline(fp, container, '\n');
			Node<Student>* node = new Node<Student>; node->init(stu);
			addLast(cour.stuList, node);
		}
		fp.close();
		return true;
	}
}

bool writeStudentsInCourse(string fname, Course cour) // fname = courseid_classname_semnumber.txt
{
	ofstream fp;
	fp.open(fname, ios::trunc); 
	if (fp.is_open() == false)
		return false;
	else
	{
		fp << "No,Student ID,First name,Last name,Gender,Date of Birth,SocialID,MidTerm,Final,Other,Total\n";
		if (cour.stuList.head == cour.stuList.tail && cour.stuList.head == nullptr)
		{
			fp.close();
			return false;
		}
		else
		{
			for (Node<Student>* i = cour.stuList.head; i != nullptr; i = i->next)
			{
				fp << i->data.no << ","
					<< i->data.stuID << ","
					<< i->data.firstName << ","
					<< i->data.lastName << ",";
				if (i->data.gender)
					fp << "nam,";
				else
					fp << "nu,";
				fp << i->data.birth.day << "/" << i->data.birth.month << "/" << i->data.birth.year << ","
					<< i->data.socialID;
				if (i->next != nullptr)
					fp << "\n";
			}
			fp.close();
			return true;
		}
	}
}

bool findCourse(string courseID, string className, int semNum, Course& found)
{
	for (Node<Course>* i = systems.allCourse[semNum - 1].head; i != nullptr; i = i->next)
		if (i->data.id.compare(courseID) == 0 && i->data.lop.cls.compare(className) == 0)
		{
			found = i->data;
			return true;
		}
	return false;
}

bool readScoreBoard(string fname) // fname = courseid_classname_semnumber.txt
{
	string* in4 = extractCId_cl_sno(fname); Course c;
	bool found = findCourse(in4[0], in4[1], atoi(in4[2].c_str()), c);
	if (!found)
		return false;
	c.score.init();
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string container = "";
		getline(fp, container, '\n');
		while (!fp.eof())
		{
			Scoreboard a; findCourse(in4[0], in4[1], atoi(in4[2].c_str()), a.course);
			getline(fp, container, ','); a.student.no = atoi(container.c_str());
			getline(fp, a.student.stuID, ',');
			getline(fp, a.student.firstName, ',');
			getline(fp, a.student.lastName, ',');
			getline(fp, container, ',');
			if (stricmp("nam", container.c_str()) == 0)
				a.student.gender = true;
			else
				a.student.gender = false;
			getline(fp, container, ',');
			a.student.birth = getNS(container);
			getline(fp, a.student.socialID, ',');
			getline(fp, container, ','); a.midTerm = atof(container.c_str());
			getline(fp, container, ','); a.Final = atof(container.c_str());
			getline(fp, container, ','); a.Other = atof(container.c_str());
			getline(fp, container, '\n'); a.Total = atof(container.c_str());
			Node<Scoreboard>* node = new Node<Scoreboard>; node->init(a);
			addLast(c.score, node);
		}
		fp.close();
		return true;
	}
}

void viewScoreBoard(Scoreboard a)
{
	cout << fixed << setprecision(3);
	cout << "Diem giua ky: " << a.midTerm << endl;
	cout << "Diem cuoi ky: " << a.Final << endl;
	cout << "Diem khac: " << a.Other << endl;
	cout << "Diem tong: " << a.Total << endl;
}

void viewScoreBoards(Course a)
{
	cout << "Bang diem cua hoc phan " << a.courseName << " cua lop " << a.lop.cls << ":" << endl;
	for (Node<Scoreboard>* i = a.score.head; i != nullptr; i = i->next)
	{
		cout << "Sinh vien " << i->data.student.firstName << " " << i->data.student.lastName 
			<< ", ma so " << i->data.student.stuID << ":" << endl;
		viewScoreBoard(i->data);
	}
	cout << endl << endl;
}

template <class T>
T* realloc(T* ptr, size_t old_size, size_t new_size) {
	if (ptr == nullptr) 
		return new T[new_size];
	if (new_size == 0) {
		delete[] ptr;
		return nullptr;
	}
	T* new_ptr = new T[new_size];
	if (new_ptr != nullptr) 
		memcpy(new_ptr, ptr, (new_size < old_size ? new_size : old_size) * sizeof(T));
	delete[] ptr;
	return new_ptr;
}

void getUpdateScbIn4(int*& option, float*& in4, int& n)
{
	option = new int[4]; in4 = new float[4]; n = 0; int temp = 0; bool yamete_kudasai = false; 
	do
	{
		cout << "Ban muon cap nhat diem nao cua sinh vien? Chon so thu tu tuong ung: " << endl;
		cout << "1. Diem giua ki" << endl;
		cout << "2. Diem cuoi ki" << endl;
		cout << "3. Diem khac" << endl;
		cout << "4. Diem tong: ";
		cin >> option[n];
		cout << "Nhap diem moi: "; cin >> in4[n]; ++n;
		if (n == 4)
			break;
		cout << "Ban chi co toi da 4 lan cap nhat. So lan ban da dung la " << n << endl;
		cout << "Ban co muon tiep tuc cap nhat nua khong? Chon so tuong ung: " <<
			"1. Co                            2. Khong: ";
		cin >> temp;
		yamete_kudasai = temp == 2 ? false : true;
	} while (yamete_kudasai);
	if (n < 4)
	{
		option = realloc(option, 4, n);
		in4 = realloc(in4, 4, n);
	}
}

bool updateScoreBoard_aStudent(Student& stu, Course cour, int* option, float* in4, int n)
{
	Node<Scoreboard>* node = stu.marks.head;
	for (node; node != nullptr; node = node->next)
		if (node->data.course.id == cour.id)
			break;
	if (node == nullptr)
		return false;
	for (int i = 0; i < n; i++)
		switch (option[i])
		{
		case 1:
			node->data.midTerm = in4[i];
			break;
		case 2:
			node->data.Final = in4[i];
			break;
		case 3:
			node->data.Other = in4[i];
			break;
		case 4:
			node->data.Total = in4[i];
			break;
		}
	return true;
}

bool updateScoreBoard_aCourse(Student& stu, Course& cour, int* option, float* in4, int n)
{
	Node<Scoreboard>* node = cour.score.head;
	for (node; node != nullptr; node = node->next)
		if (node->data.student.stuID == stu.stuID)
			break;
	if (node == nullptr)
		return false;
	for (int i = 0; i < n; i++)
		switch (option[i])
		{
		case 1:
			node->data.midTerm = in4[i];
			break;
		case 2:
			node->data.Final = in4[i];
			break;
		case 3:
			node->data.Other = in4[i];
			break;
		case 4:
			node->data.Total = in4[i];
			break;
		}
	return true;
}

bool updateScoreBoard_aStaff(Student& stu, Course& cour, int* option, float* in4, int n)
{
	Node<Course>* n0de = cour.teacher.courses.head;
	for (; n0de != nullptr; n0de = n0de->next)
		if (n0de->data.id == cour.id)
			return updateScoreBoard_aCourse(stu, n0de->data, option, in4, n);
	if (n0de == nullptr)
		return false;
}

bool updateScoreBoard(Student& stu, Course& cour, Semester currSem, int* option, float* in4, int n) // Watch out this one, change the course scb too
{
	// cap nhat bang diem cua mot hoc sinh
	if (!updateScoreBoard_aStudent(stu, cour, option, in4, n))
		return false;
	// cap nhat bang diem trong lop trong he thong
	if (!updateScoreBoard_aStudent(findStudent(stu.stuID)->data, cour, option, in4, n))
		return false;
	// cap nhat bang diem cua khoa hoc trong he thong
	if (!updateScoreBoard_aCourse(stu, cour, option, in4, n))
		return false;
	// cap nhat bang diem cua khoa hoc trong tep
	if (!writeStudentsInCourse(generateFileName(cour, stu.cl, currSem), cour))
		return false;
	// cap nhat semGPA cua hoc sinh
	stu.semGPA = calculateSemGPA(stu);
	// cap nhat semGPA cua ca lop trong he thong
	findStudent(stu.stuID)->data.semGPA = calculateSemGPA(stu);
	// cap nhat semGPA cua ca lop trong tep
	if(!writeGPAofClassInSem(generateFileName(stu.cl, currSem), stu.cl, currSem))
		return false;
	// cap nhat gpa cua hoc sinh
	if (calculateOverallGPA(stu, currSem) < 0)
		return false;
	// cap nhat gpa cua ca lop trong tep
	if (calculateOverallGPA(findStudent(stu.stuID)->data, currSem) < 0)
		return false;
	// cap nhat bang diem cua khoa hoc cua giao vien day
	if (!updateScoreBoard_aStaff(stu, cour, option, in4, n))
		return false;
	// cap nhat bang diem cua hoc sinh trong tep
	return writeAllCoursesOfStudent(stu.stuID + ".txt");
}

void viewScoreboards(Student a)
{
	cout << "Bang diem cua sinh vien " << a.firstName << " " << a.lastName << ", ma so " << a.stuID << ":" << endl;
	for (Node<Scoreboard>* i = a.marks.head; i != nullptr; i = i->next)
	{
		cout << "Hoc phan " << i->data.course.courseName << ":" << endl;
		viewScoreBoard(i->data);
	}
}