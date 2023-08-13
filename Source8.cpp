#include "Header1.hpp"
#include "Header2.hpp"

float calculateSemGPA(Student &stu)
{
	stu.semGPA = 0.0;
	for (Node<Scoreboard>* i = stu.marks.head; i != nullptr; i = i->next)
		stu.semGPA += i->data.Total * float(i->data.course.credits);
	return stu.semGPA / float(countNodes(stu.marks.head));
}

LList<Course> findCoursesOfClass(Class cl, Semester sem)
{
	LList<Course> courseList; courseList.init();
	for (Node<Course>* i = systems.allCourse[sem.number - 1].head; i != nullptr; i = i->next)
		if (i->data.lop.isEqual(cl) && i->data.sem.isEqual(sem))
		{
			Node<Course>* node = new Node<Course>; node->init(i->data);
			addLast(courseList, node);
		}
	return courseList;
}

void viewGPAInSemester(Class cl, Semester sem) // watch out, something wrong here
{
	cout << "Diem trung binh hoc ki cua cac sinh vien lop " << cl.cls << ":" << endl;
	for (Node<Student>* i = cl.stuList.head; i != nullptr; i = i->next)
		cout << i->data.firstName << " " << i->data.lastName << ": " << calculateSemGPA(i->data);
	cout << endl << endl;
}

void countNoInStudentList(LList<Student> &l)
{
	int n = countNodes(l.head), index = 1;
	for (Node<Student>* i = l.head; i != nullptr && index <= n; i = i->next, ++index)
		i->data.no = index;
}

bool writeGPAofClassInSem(string fname, Class cl, Semester sem) // fname = gpa_classname_semnumber.txt (gpa is a literally a word)
{ //watch out, something went wrong here
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (!fp.is_open())
		return false;
	else
	{
		countNoInStudentList(cl.stuList);
		fp << "No,Student ID,Semester GPA" << endl;
		for (Node<Student>* i = cl.stuList.head; i != nullptr; i = i->next)
		{
			fp << i->data.no << ","
				<< i->data.stuID << ","
				<< calculateSemGPA(i->data);
			if (i != cl.stuList.tail)
				fp << "\n";
		}
		fp.close();
		return true;
	}
}

string generateFileName(Class cl, Semester sem)
{
	string res = "gpa";
	res += cl.cls;
	res += to_string(sem.number);
	res += sem.sy.schYr;
	res += ".txt";
	return res;
}

string* generateMoreFileNames(Class cl, Semester currentSem)
{
	int numberOfSem = (currentSem.sy.yStart - cl.year.yStart) * 3 + currentSem.number;
	string* fnameList = new string[numberOfSem]; 
	int index = 0;
	for (int year = cl.year.yStart; year != currentSem.sy.yEnd && index < numberOfSem; ++year)
		for (int i = 1; i < 4; ++i, ++index)
		{
			SchoolYear schy = createSchoolYear(year, year + 1);
			Semester a;
			a.sy = schy;
			a.number = i;
			fnameList[index] = generateFileName(cl, a);
		}
	return fnameList;
}

string* extractCl_sno_schy(string fname) // fname = gpa_classname_semnumber.txt (gpa is a literally a word)
{
	int j = 4; string* res = new string[2];
	for (int i = 0; i < 2; ++i)
		for (j; fname[j] - '_' == 0 || fname[j] - '.' == 0; ++j)
			res[i].push_back(fname[j]);
	return res;
}

Node<Student>* findStudent(string id, Class cl)
{ 
	for (Node<Student>* i = cl.stuList.head; i != nullptr; i = i->next)
		if (i->data.stuID.compare(id) == 0)
			return i;
	return nullptr;
}

Node<Student>* findStudent(string id)
{
	for (Node<Class>* cl = systems.allClass.head; cl != nullptr; cl = cl->next)
		for (Node<Student>* i = cl->data.stuList.head; i != nullptr; i = i->next)
			if (i->data.stuID.compare(id) == 0)
				return i;
	return nullptr;
}

Node<Class>* findCLass(string name)
{
	for (Node<Class>* i = systems.allClass.head; i != nullptr; i = i->next)
		if (i->data.cls.compare(name) == 0)
			return i;
	return nullptr;
}

bool readGPAofClassInSem(string fname, LList<float>& semGPA) // fname = gpa_classname_semnumber.txt (gpa is a literally a word)
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string* container = new string[2];
		string className = extractCl_sno_schy(fname)[0];
		Node<Class>* n0de = findCLass(className); semGPA.init();
		if (n0de == nullptr)
		{
			fp.close();
			return false;
		}
		Node<Student>* node = n0de->data.stuList.head;
		while (!fp.eof())
		{
			float score = 0.0;
			getline(fp, container[0], ',');
			getline(fp, container[1], ',');
			getline(fp, container[0], '\n'); score = atof(container[0].c_str());
			node->data.semGPA = score;
			node = node->next;
			Node<float>* i = new Node<float>; i->init(score);
			addLast(semGPA, i);
		}
		fp.close();
		return true;
	}
}

float calculateOverallGPA(Student &stu, Semester currentSem)
{
	string* fnameList = generateMoreFileNames(stu.cl, currentSem);
	int numberOfSem = (currentSem.sy.yStart - stu.cl.year.yStart) * 3 + currentSem.number;
	LList<float>* semGPA = new LList<float>[numberOfSem];
	for (int i = 0; i < numberOfSem; ++i)
		if (!readGPAofClassInSem(fnameList[i], semGPA[i]))
		{
			delete[] fnameList;
			delete[] semGPA;
			semGPA = nullptr;
			fnameList = nullptr;
			return -1.0;
		}
	for (int j = 0; j < numberOfSem; ++j)
		stu.GPA += findNodeByIndex(semGPA[j], stu.no)->data;
	stu.GPA /= float(numberOfSem);
	delete[] semGPA;
	return stu.GPA;
}

float* countOverallGPAInClass(Class cl, Semester currentSem)
{
	string* fnameList = generateMoreFileNames(cl, currentSem); 
	int numberOfSem = (currentSem.sy.yStart - cl.year.yStart) * 3 + currentSem.number;
	LList<float>* semGPA = new LList<float>[numberOfSem];
	for (int i = 0; i < numberOfSem; ++i)
		if (!readGPAofClassInSem(fnameList[i], semGPA[i]))
		{
			delete[] fnameList;
			delete[] semGPA;
			semGPA = nullptr;
			fnameList = nullptr;
			return nullptr;
		}
	int numberOfStu = countNodes(semGPA[0].head);
	float* overallGPA = new float[numberOfStu];
	for (int i = 0; i < numberOfStu; ++i)
		for (int j = 0; j < numberOfSem; ++j)
			overallGPA[i] += findNodeByIndex(semGPA[j], i)->data;
	Node<Student>* node = cl.stuList.head;
	for (int i = 0; i < numberOfStu && node != nullptr; ++i, node = node->next)
	{
		overallGPA[i] /= float(numberOfSem);
		node->data.GPA = overallGPA[i];
	}
	return overallGPA;
}

void viewOverallGPAInClass(Class cl, Semester currentSem)
{
	float* overallGPA = countOverallGPAInClass(cl, currentSem);
	int numberOfStu = countNodes(cl.stuList.head); int index = 0;
	cout << "Diem trung binh tich luy cua cac sinh vien trong lop " << cl.cls << ":" << endl;
	for (Node<Student>* i = cl.stuList.head; numberOfStu > index; ++index, i = i->next)
		cout << index + 1 << ". " << i->data.firstName << " "
		<< i->data.lastName << ": " << overallGPA[index];
	cout << endl << endl;
}

void viewScoreBoards(Class cl, Semester sem)
{
	cout << "Bang diem cua lop " << cl.cls << ": " << endl;
	for (int i = 0; i < 40; ++i)
		cout << " ";

	LList<Course> courseList = findCoursesOfClass(cl, sem);
	for (Node<Course>* i = courseList.head; i != nullptr; ++i)
		cout << setw(50) << setfill('-') << left << i->data.courseName;
	cout << setw(30) << setfill('-') << left << "Semester GPA";
	cout << setw(30) << setfill('-') << left << "Overall GPA" << endl;

	for (Node<Student>* index1 = cl.stuList.head; index1 != nullptr; index1 = index1->next)
	{
		cout << setw(40) << index1->data.firstName << " " << index1->data.lastName;
		for (Node<Course>* index2 = courseList.head; index2 != nullptr; index2 = index2->next)
		{
			Node<Scoreboard>* node = index1->data.marks.head;
			for (node; node->data.course.id.compare(index2->data.id) != 0; node = node->next)
				continue;
			cout << setw(50) << left << node->data.Final;
		}
		cout << setw(30) << left << index1->data.semGPA;
		cout << setw(30) << left << index1->data.GPA;
		if (index1->next != nullptr)
			cout << endl;
	}
	cout << endl << endl;
}