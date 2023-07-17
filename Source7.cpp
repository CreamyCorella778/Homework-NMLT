#include "Header1.h"
#include "Header2.h"

bool writeStudentsInCourse(string fname, Course cour)
{
	ofstream fp;
	fp.open(fname, ios::trunc); // fname = courseid_classname.txt
	if (fp.is_open() == false)
		return false;
	else
	{
		fp << "No,Student ID,First name,Last name,Gender,Date of Birth,SocialID\n";
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
					<< i->data.socialID << "\n";
			}
			fp.close();
			return true;
		}
	}
}