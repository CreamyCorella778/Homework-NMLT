#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

float calculateSemGPA(Student &stu)
{
	stu.semGPA = 0.0; float sumCredit = 0.0;
	for (Node<Scoreboard>* i = stu.marks.head; i != nullptr; i = i->next)
	{
		stu.semGPA += i->data.Total * float(i->data.course.credits);
		sumCredit += float(i->data.course.credits);
	}
	if (!sumCredit)
		stu.semGPA == 0.0;
	else
		stu.semGPA /= sumCredit;
	return stu.semGPA;
}

LList<Course> findCoursesOfClass(Class cl, Semester sem)
{
	LList<Course> courseList; courseList.init();
	for (Node<Course>* i = systems.allCourse[sem.number - 1].head; i != nullptr; i = i->next)
		if (!i->data.lop.cls.compare(cl.cls) && i->data.sem.isEqual(sem))
		{
			Node<Course>* node = new Node<Course>; node->init(i->data);
			addLast(courseList, node);
		}
	return courseList;
}

void calculateSemGPAforClass(Class cl)
{
	for (Node<Student>* i = cl.stuList.head; i != nullptr; i = i->next)
		calculateSemGPA(i->data);
}

void viewGPAInSemester(Class cl, Semester sem) 
{
	cout << "Diem trung binh hoc ki " << sem.number << " cua cac sinh vien lop " << cl.cls << ":" << endl;
	for (Node<Student>* i = cl.stuList.head; i != nullptr; i = i->next)
		cout << i->data.firstName << " " << i->data.lastName << ": " << i->data.semGPA;
	cout << endl << endl;
}

void countNoInStudentList(LList<Student> &l)
{
	int n = countNodes(l.head), index = 1;
	for (Node<Student>* i = l.head; i != nullptr && index <= n; i = i->next, ++index)
		i->data.no = index;
}

// fname = gpa_classname_semnumber_schoolyear.txt (gpa is a literally a word)
bool writeGPAofClassInSem(string fname, Class cl, Semester sem) 
{ 
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
				<< i->data.semGPA;
			if (i->next)
				fp << "\n";
		}
		fp.close();
		return true;
	}
}

string generateFileName(Class cl, Semester sem)
{
	string res = "gpa_";
	res += cl.cls; res.push_back('_');
	res += to_string(sem.number); res.push_back('_');
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

// fname = gpa_classname_semnumber_schoolyear.txt (gpa is a literally a word)
string* extractCl_sno_schy(string fname) 
{
	int j = 4; string* res = new string[2];
	for (int i = 0; i < 2; ++i)
		for (; fname[j] != '_' && fname[j] != '.'; ++j)
			res[i].push_back(fname[j]);
	return res;
}

// fname = gpa_classname_semnumber_schoolyear.txt (gpa is a literally a word)
bool readGPAofClassInSem(string fname, LList<float>& semGPA) 
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
		if (!n0de)
		{
			fp.close();
			return false;
		}
		Node<Student>* node = n0de->data.stuList.head;
		getline(fp, container[0], '\n');
		while (getline(fp, container[0], ','))
		{
			float score = 0.0;
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
	stu.GPA = 0;
	for (int j = 0; j < numberOfSem; ++j)
		stu.GPA += findNodeByIndex(semGPA[j], stu.no - 1)->data;
	stu.GPA /= float(numberOfSem);
	delete[] semGPA;
	delete[] fnameList;
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
	{
		overallGPA[i] = 0.0;
		for (int j = 0; j < numberOfSem; ++j)
			overallGPA[i] += findNodeByIndex(semGPA[j], i)->data;
	}
	Node<Student>* node = cl.stuList.head;
	for (int i = 0; i < numberOfStu && node != nullptr; ++i, node = node->next)
	{
		overallGPA[i] /= float(numberOfSem);
		node->data.GPA = overallGPA[i];
	}
	delete[] fnameList;
	delete[] semGPA;
	return overallGPA;
}