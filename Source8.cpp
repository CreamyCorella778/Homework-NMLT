#include "Header1.h"
#include "Header2.h"

float calculateGPA(LList<Scoreboard> a)
{
	float gpa = 0.0;
	for (Node<Scoreboard>* i = a.head; i != nullptr; i = i->next)
		gpa += i->data.Total * float(i->data.course.credits);
	return gpa / float(countNodes(a.head));
}

LList<Course> findCourseInClass(Class cl, Semester sem)
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

void viewScoreBoards(Class cl, Semester sem)
{
	cout << "Bang diem cac hoc phan trong lop " << cl.cls << ":" << endl;
	LList<Course> courseList = findCourseInClass(cl, sem);
	for (Node<Course>* i = courseList.head; i != nullptr; i = i->next)
		viewScoreBoards(i->data);
	cout << endl << endl;
}

void viewGPAInSemester(Class cl, Semester sem)
{
	cout << "Diem trung binh hoc ki cua cac sinh vien lop " << cl.cls << ":" << endl;
	for (Node<Student>* i = cl.stuList.head; i != nullptr; i = i->next)
		cout << i->data.firstName << " " << i->data.lastName << ": " << calculateGPA(i->data.marks);
	cout << endl << endl;
}

void countNoInStudentList(LList<Student> &l)
{
	int n = countNodes(l.head);
	for (Node<Student>* i = l.head, int index = 1; i != nullptr && index <= n; i = i->next, ++index)
		i->data.no = index;
}

bool writeGPAofClassInSem(string fname, Class cl, Semester sem) // fname = gpa_classname_semnumber_schoolyear.txt (gpa is a literally a word)
{
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (!fp.is_open())
		return false;
	else
	{
		countNoInStudentList(cl.stuList);
		fp << "No,Student ID,GPA" << endl;
		for (Node<Student>* i = cl.stuList.head; i != nullptr; i = i->next)
		{
			fp << i->data.no << ","
				<< i->data.stuID << ","
				<< calculateGPA(i->data.marks);
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
	res += string(sem.number);
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

string* extractCl_sno_schy(string fname) // fname = gpa_classname_semnumber_schoolyear.txt (gpa is a literally a word)
{
	int j = 4; string* res = new string[3];
	for (int i = 0; i < 3; ++i)
		for (j; fname[j] - '_' == 0 || fname[j] - '.' == 0; ++j)
			res[i].push_back(fname[j]);
	return res;
}

Node<Student>* findStudent(string id, Class cl)
{ 
	for (Node<Student>* i = cl.stuList.head; i != nullptr; i = i->next)
		if (i->data.stuID.compare(id) == 0)
		{
			Node<Student>* res = new Node<Student>;
			res->init(i->data);
			return res;
		}
	return nullptr;
}

Node<Student>* findStudent(string id)
{
	for (Node<Class>* cl = systems.allClass.head; cl != nullptr; cl = cl->next)
		for (Node<Student>* i = cl->data.stuList.head; i != nullptr; i = i->next)
			if (i->data.stuID.compare(id) == 0)
			{
				Node<Student>* res = new Node<Student>;
				res->init(i->data);
				return res;
			}
	return nullptr;
}

Node<Class>* findCLass(string name)
{
	for (Node<Class>* i = systems.allClass.head; i != nullptr; i = i->next)
		if (i->data.cls.compare(name) == 0)
			return i;
	return nullptr;
}

bool readGPAofClassInSem(string fname, LList<float>& gpas)
{
	ifstream fp;
	fp.open(fname, ios::text | ios::in);
	if (!fp.is_open())
		return false;
	else
	{
		string* container = new string[2];
		string className = extractCl_sno_schy(fname)[0];
		countNoInStudentList(findCLass(className)->data.stuList);
		gpas.init();
		while (!fp.eof())
		{
			float score = 0.0;
			getline(fp, container[0], ',');
			getline(fp, container[1], ',');
			getline(fp, container[0], '\n'); score = atof(container[0]);
			Node<float>* node = new Node<float>; node->init(score);
			addLast(gpas, node);
		}
		fp.close();
		return true;
	}
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
			semGPA = fnameList = nullptr;
			return;
		}
	int numberOfStu = countNodes(semGPA[0].head);
	float* overallGPA = new float[numberOfStu];
	for (int i = 0; i < numberOfStu; ++i)
		for (int j = 0; j < numberOfSem; ++j)
			overallGPA[i] = findNode(semGPA[j], i)->data;
	for (int i = 0; i < numberOfStu; ++i)
		overallGPA[i] /= numberOfSem;
	return overallGPA;
}

void viewOverallGPAInClass(Class cl, Semester currentSem)
{
	float* overallGPA = countOverallGPAInClass(cl, currentSem);
	int numberOfStu = countNodes(cl.stuList.head);
	cout << "Diem trung binh tich luy cua cac sinh vien trong lop " << cl.cls << ":" << endl;
	for (int index = 0, Node<Student>* i = cl.stuList.head; index < numberOfStu; ++index, i = i->next)
		cout << index + 1 << ". " << i->data.firstName << " "
		<< i->data.lastName << ": " << overallGPA[index];
	cout << endl << endl;
}