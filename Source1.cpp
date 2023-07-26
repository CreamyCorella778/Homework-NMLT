#include "Header1.h"
#include "Header2.h"

int countLinesInCSV(string fname)
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (fp.is_open() == false)
		return -1;
	else
	{
		int count = 0; string a;
		while (getline(fp, a))
			count++;
		fp.close();
		return count;
	}
}

bool readLoginIn4(string fname, string** &container, int& col, int& row)
{
	row = countLinesInCSV(fname); col = 2;
	ifstream fp;
	fp.open(fname, ios::in);
	if (fp.is_open() == false)
		return false;
	else
	{
		container = new string * [row];
		for (int i = 0; i < row; ++i)
		{
			container[i] = new string[col];
			getline(fp, container[i][0], ',');
			getline(fp, container[i][1], '\n');
		}
		fp.close();
		return true;
	}
}

int checkExistEmail(string** container, int row, string email)
{
	for (int i = 0; i < row; ++i)
		if (container[i][0].compare(email) == 0)
			return i;
	return -1;
}

bool loginSystem(string fname, string &email)
{
	string** loginData; int row = 0, col = 0;
	bool doc = readLoginIn4(fname, loginData, col, row);
	if (doc == false)
	{
		cout << "Su co he thong. Chuc ban may man lan sau. " << endl;
		return false;
	}
	else
	{
		string pass;
		int email_exist, count = 0;
		do
		{
			cout << "So lan da dang nhap: " << count << ". Ban chi co 5 lan thu. Nhap email: "; getline(cin, email, '\n');
			email_exist = checkExistEmail(loginData, row, email);
			count++;
		} while (email_exist == -1 && count != 5);
		if (email_exist != -1)
		{
			count = 0;
			do
			{
				cout << "So lan co dang nhap: " << count << ". Ban chi co 5 lan thu. Nhap mat khau: "; getline(cin, pass, '\n');
				count++;
			} while (pass.compare(loginData[email_exist][1]) != 0 && count != 5);
			if (pass.compare(loginData[email_exist][1]) == 0)
			{
				cout << "Dang nhap thanh cong. " << endl;
				return true;
			}
			else if (count == 5)
			{
				cout << "Ban da het so lan dang nhap. Chuc ban may man lan sau. ";
				return false;
			}
		}
		else if (count == 5)
		{
			cout << "Ban da het so lan dang nhap. Chuc ban may man lan sau. ";
			return false;
		}
	}
}

void changePassword(string fname, string email)
{
	string pass, pass_again; int count = 0;
	cout << "Nhap mat khau moi: "; cin >> pass;
	do
	{
		cout << "Ban co " << 5 - count << " lan nhap. Nhap lai mat khau moi : "; cin >> pass_again;
		count++;
	} 
	while (pass.compare(pass_again) != 0 && count != 5);
	if (pass.compare(pass_again) == 0)
	{
		string** container; int row = 0, col = 0;
		readLoginIn4(fname, container, col, row);
		int i = 0;
		for (i; container[i][0].compare(email) != 0; ++i);
		container[i][1] = pass_again;
		ofstream fp;
		fp.open(fname, ios::trunc);
		if (fp.is_open() == false)
		{
			cout << "Mo tep that bai. Chuc ban may man lan sau. ";
			return;
		}
		else
		{
			for (i = 0; i < row; ++i)
			{
				fp << container[i][0];
				fp << ",";
				fp << container[i][1];
				fp << "\n";
			}
			fp.close();
			cout << "Doi mat khau thanh cong." << endl;
			return;
		}
	}
	else if (count == 5)
	{
		cout << "Ban da het so lan nhap. Chuc ban may man lan sau. " << endl;
		return;
	}
}


Student extractStudentFromEnail(string email)
{
	string id;
	for (int i = 0; email[i] - '@' != 0; ++i)
		id.push_back(email[i]);
	for (Node<Class>* i = systems.allClass.head; i != nullptr; i = i->next)
		for (Node<Student>* j = i->data.stuList.head; j != nullptr; j = j->next)
			if (j->data.stuID.compare(id) == 0)
				return j->data;
}

Staff extractStaffFromEnail(string email)
{
	string id;
	for (int i = 0; email[i] - '@' != 0; ++i)
		id.push_back(email[i]);
	for (Node<Staff>* i = systems.allStaff.head; i != nullptr; i = i->next)
		if (j->data.id.compare(id) == 0)
			return j->data;
}

bool identifyUserType(string email) // student = true, teacher/staff == false
{
	string temp;
	for (int i = email.find_first_of('@') + 1; email[i] - '.' != 0; ++i)
		temp.push_back(email[i]);
	if (temp.compare("student") == 0)
		return true;
	else if (temp.compare("teacher") == 0)
		return false;
}

string generateEmail(Student stu)
{
	return stu.stuID + "@student.hcmuf.edu.vn";
}

string generateEmail(Staff sta)
{
	return sta.id + "@teacher.hcmuf.edu.vn";
}

void printProfileIn4(string email)
{
	if (identifyUserType(email))
		viewStudent(extractStudentFromEnail(email));
	else
		viewStaff(extractStaffFromEnail(email));
}

void logout() // skip for now cuz of no idea and main func dependance.
{

}

int testing1()
{
	string fname = "login.csv.txt";
	string email;
	if (loginSystem(fname, email) == true)
		changePassword(fname, email);
	else
		cout << "Khong doi mat khau duoc.";
	return 0;
}