#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

bool addStudentsToCourse(string fname, Course &cour)  // fname = courseid_classname_semnumber.txt
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string container = ""; getline(fp, container, '\n');
		cour.stuList.init();
		Node<Course>* course = new Node<Course>; course->init(cour);
		while (getline(fp, container, ','))
		{
			Student stu;
			stu.no = atoi(container.c_str());
			getline(fp, stu.stuID, ',');
			getline(fp, stu.firstName, ',');
			getline(fp, stu.lastName, ',');
			getline(fp, container, ',');
			if (!_stricmp("nam", container.c_str()))
				stu.gender = true;
			else
				stu.gender = false;
			getline(fp, container, ',');
			stu.birth = getNS(container);
			getline(fp, stu.socialID, ',');
			getline(fp, container, '\n');
			stu.courses.init(); addLast(stu.courses, course);
			Node<Student>* node = new Node<Student>; node->init(stu);
			addLast(cour.stuList, node);
			node->data.marks.init();
		}
		fp.close();
		return true;
	}
}

bool writeStudentsInCourse(string fname, Course cour) // fname = courseid_classname_semnumber.txt
{
	if (cour.stuList.head == cour.stuList.tail && !cour.stuList.head)
		return false;
	ofstream fp;
	fp.open(fname, ios::trunc); 
	if (!fp.is_open())
		return false;
	else
	{
		fp << "No,Student ID,First name,Last name,Gender,Date of Birth,SocialID,MidTerm,Final,Other,Total\n";
		for (Node<Student>* i = cour.stuList.head; i; i = i->next)
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
				<< i->data.socialID << ",0,0,0,0";
			if (i->next)
				fp << "\n";
		}
		fp.close();
		return true;
	}
}

bool readScoreBoard(string fname) // fname = courseid_classname_semnumber.txt
{
	string* in4 = extractCId_cl_sno(fname);
	Node<Course>* c = findCourse(in4[0], in4[1], atoi(in4[2].c_str()));
	if (!c)
		return false;
	c->data.score.init();
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string container = "";
		getline(fp, container, '\n');
		while (getline(fp, container, ','))
		{
			Scoreboard a;
			a.course = c->data;
			getline(fp, a.student.stuID, ',');
			Node<Student>* n0de = c->data.stuList.head;
			for (; n0de && n0de->data.stuID.compare(a.student.stuID); n0de = n0de->next);
			if (!n0de)
			{
				fp.close();
				return false;
			}
			else
				a.student = n0de->data;
			for (int i = 0; i < 5; ++i)
				getline(fp, container, ',');
			getline(fp, container, ','); a.midTerm = atof(container.c_str());
			getline(fp, container, ','); a.Final = atof(container.c_str());
			getline(fp, container, ','); a.Other = atof(container.c_str());
			getline(fp, container, '\n'); a.Total = atof(container.c_str());
			Node<Scoreboard>* node = new Node<Scoreboard>; node->init(a);
			addLast(c->data.score, node);
			Node<Scoreboard>* noDe = n0de->data.marks.head;
			for (; noDe && noDe->data.course.id.compare(c->data.id); noDe = noDe->next)
				continue;
			if (!noDe)
			{
				noDe = new Node<Scoreboard>; noDe->init(a);
				addLast(n0de->data.marks, noDe);
			}
			else
				noDe->data = a;
		}
		fp.close();
		return true;
	}
}

bool writeScoreBoard(string fname, Course cour) // fname = courseid_classname_semnumber.txt
{
	if (cour.stuList.head == cour.stuList.tail && !cour.stuList.head)
		return false;
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (!fp.is_open())
		return false;
	else
	{
		fp << "No,Student ID,First name,Last name,Gender,Date of Birth,SocialID,MidTerm,Final,Other,Total\n";
		for (Node<Student>* i = cour.stuList.head; i; i = i->next)
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
			Node<Scoreboard>* scb = findScoreboard(i->data, cour);
			if (!scb)
			{
				fp.close();
				return false;
			}
			fp << "," << scb->data.midTerm << "," << scb->data.Final << ","
				<< scb->data.Other << "," << scb->data.Total;
			if (i->next)
				fp << "\n";
		}
		fp.close();
		return true;
	}
}

template <class T>
T* realloc(T* ptr, size_t old_size, size_t new_size) {
	if (ptr == nullptr) 
		return new T[new_size];
	if (!new_size) {
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
		cout << "Ban muon cap nhat diem nao cua sinh vien? Chon so thu tu tuong ung voi lua chon: " << endl;
		cout << "1. Diem giua ki" << endl;
		cout << "2. Diem cuoi ki" << endl;
		cout << "3. Diem khac" << endl;
		cout << "4. Diem tong: ";
		cin >> option[n];
		cout << "Nhap diem moi: "; cin >> in4[n]; ++n;
		if (n == 4)
			break;
		cout << "Ban chi co the cap nhat toi da 4 truong. So lan ban da dung la " << n << endl;
		cout << "Ban co muon tiep tuc cap nhat nua khong? Chon so thu tu tuong ung voi lua chon:" << endl <<
			    "1. Co                                                                 2. Khong: ";
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
	for (; node && node->data.course.id.compare(cour.id); node = node->next)
		continue;
	if (!node)
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
	for (; node && node->data.student.stuID.compare(stu.stuID); node = node->next)
		continue;
	if (!node)
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
	for (Node<Course>* n0de = cour.teacher.courses.head; n0de; n0de = n0de->next)
		if (!n0de->data.id.compare(cour.id))
			return updateScoreBoard_aCourse(stu, n0de->data, option, in4, n);
	return false;
}

bool updateScoreBoard(Student& stu, Course& cour, Semester currSem, int* option, float* in4, int n)
{
	// tim kiem hoc sinh trong he thong bang ma so 
	Node<Student>* node = findStudent(stu.stuID);
	if (!node)
		return false;
	bool isEqual = node->data.isEqual(stu) ? true : false;
	// cap nhat bang diem cua mot hoc sinh
	if (!updateScoreBoard_aStudent(stu, cour, option, in4, n))
		return false;
	// cap nhat bang diem trong lop trong he thong
	if (!isEqual)
		if (!updateScoreBoard_aStudent(node->data, cour, option, in4, n))
			return false;
	// cap nhat bang diem cua khoa hoc trong he thong
	if (!updateScoreBoard_aCourse(stu, cour, option, in4, n))
		return false;
	// cap nhat bang diem cua khoa hoc trong tep
	if (!writeScoreBoard(generateFileName(cour, stu.cl, currSem), cour))
		return false;
	// cap nhat semGPA cua hoc sinh
	stu.semGPA = calculateSemGPA(stu);
	// cap nhat semGPA cua ca lop trong he thong
	if (!isEqual)
		node->data.semGPA = calculateSemGPA(stu);
	// cap nhat semGPA cua ca lop trong tep
	if(!writeGPAofClassInSem(generateFileName(stu.cl, currSem), stu.cl, currSem))
		return false;
	// cap nhat gpa cua hoc sinh
	if (calculateOverallGPA(stu, currSem) < 0 || calculateOverallGPA(stu, currSem) > 10)
		return false;
	// cap nhat gpa cua ca lop trong tep
	if (!isEqual)
		if (calculateOverallGPA(node->data, currSem) < 0 || calculateOverallGPA(node->data, currSem) > 10)
			return false;
	// cap nhat bang diem cua khoa hoc cua giao vien day
	if (!updateScoreBoard_aStaff(stu, cour, option, in4, n))
		return false;
	// cap nhat bang diem cua hoc sinh trong tep
	return writeAllCoursesOfStudent(stu.stuID + ".txt");
}

