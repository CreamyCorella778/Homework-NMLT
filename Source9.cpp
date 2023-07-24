#include "Header1.h"
#include "Header2.h"

bool writeStaffList(string fname) // fname = staff_list.txt
{
	ofstream fp;
	fp.open(fname, ios::trunc);
	if (fp.is_open() == false)
		return false;
	else
	{
		fp << "No,Staff ID,First name,Last name\n";
		if (systems.allStaff.head == systems.allStaff.tail && systems.allStaff.head == nullptr)
		{
			fp.close();
			return false;
		}
		else
		{
			int j = 1;
			for (Node<Staff>* i = systems.allStaff.head; i != nullptr; i = i->next, ++j)
				fp << j << ","
					<< i->data.id << ","
					<< i->data.firstName << ","
					<< i->data.lastName << ",";
			fp.close();
			return true;
		}
	}
}

bool readStaffList(string fname) 
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (!fp.is_open())
		return false;
	else
	{	
		char* container = new char[100];
		fp.getline(container, '\n');
		systems.allStaff.init();
		while(!fp.eof())
		{
			Staff a;
			fp.getline(container, ',');
			getline(fp, a.id, ',');
			getline(fp, a.firstName, ',');
			getline(fp, a.lastName, '\n');
			Node<Staff>* node = new Node<Staff>; node->init(a);
			addLast(systems.allStaff, node);
		}
		fp.close();
		return true;
	}
}

