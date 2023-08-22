#include "Header1.hpp"
#include "Header2.hpp"
#include "Header3.hpp"

int countLinesInCSV(string fname)
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (fp.is_open() == false)
		return -1;
	else
	{
		int count = 0; string a = "";
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
	return -1; // not found!
}

bool loginSystem(string fname, string &email)
{
	string** loginData = new string*; int row = 0, col = 2;
	if (!readLoginIn4(fname, loginData, col, row))
	{
		cout << "Su co he thong. Chuc ban may man lan sau. " << endl;
		return false;
	}
	else
	{
		string pass = ""; int isExistEmail = -1, count = 5;
		do
		{
			cout << "Nhap email: "; getline(cin, email, '\n');
			isExistEmail = checkExistEmail(loginData, row, email);
			--count;
			if (isExistEmail & (1 << 31)) // isExistEmail < 0
				cout << "Ban con " << count << " lan dang nhap. ";
		} while ((isExistEmail & (1 << 31)) && count);
		if (isExistEmail != -1)
		{
			count = 5; int isExistPass = 0;
			do
			{
				cout << "Nhap mat khau : "; getline(cin, pass, '\n');
				isExistPass = pass.compare(loginData[isExistEmail][1]);
				--count;
				if (isExistPass) // isExistPass != 0
					cout << "Ban con " << count << " lan dang nhap. ";
			} while (isExistPass && count);
			if (!isExistPass) // isExistPass == 0
			{
				cout << "Dang nhap thanh cong. " << endl;
				return true;
			}
		}
		else if (count == 5)
		{
			cout << "Ban da het so lan dang nhap. Chuc ban may man lan sau. ";
			return false;
		}
		delete[] *loginData; 
		return false;
	}
}

bool changePassword(string fname, string email)
{
	string pass = "", secondPass = ""; int count = 5, isValid = 0;
	cout << "Nhap mat khau moi: "; getline(cin, pass);
	do
	{
		cout << "Nhap lai mat khau moi : "; getline(cin, secondPass);
		isValid = pass.compare(secondPass);
		count++;
		if (isValid) 
			cout << "Ban con " << count << " lan nhap. ";
	} 
	while (isValid && count != 5);
	if (!isValid)
	{
		string** container = new string*; int row = 0, col = 2, i = 0;
		if (!readLoginIn4(fname, container, col, row))
			return false;
		for (; container[i][0].compare(email) != 0; ++i)
			continue;
		container[i][1] = secondPass;
		ofstream fp;
		fp.open(fname, ios::trunc);
		if (!fp.is_open())
		{
			cout << "Loi he thong. Chuc ban may man lan sau.";
			for (int index = 0; index < row; ++index)
				delete[]container[index];
			delete[]container;
			return false;
		}
		else
		{
			for (i = 0; i < row; ++i)
				fp << container[i][0]
					<< ","
					<< container[i][1]
					<< "\n";
			fp.close();
			cout << "Doi mat khau thanh cong." << endl;
			for (int index = 0; index < row; ++index)
				delete[]container[index];
			delete[]container;
			return true;
		}
	}
	else if (count == 5)
	{
		cout << "Ban da het so lan nhap. Chuc ban may man lan sau." << endl;
		return false;
	}
	else
		return false;
}


Node<Student>* extractStudentFromEmail(string email)
{
	string id = "";
	for (int i = 0; email[i] != '@'; ++i)
		id.push_back(email[i]);
	return findStudent(id);
}

Node<Staff>* extractStaffFromEmail(string email)
{
	string id = "";
	for (int i = 0; email[i] != '@'; ++i)
		id.push_back(email[i]);
	return findStaff(id);
}

int identifyUserType(string email) // student = 1, teacher/staff == 0
{
	string temp = "";
	for (int i = email.find_first_of('@') + 1; email[i] != '.'; ++i)
		temp.push_back(email[i]);
	if (temp.compare("student") == 0)
		return 1;
	else if (temp.compare("teacher") == 0)
		return 0;
	else
		return -1;
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
	int userType = identifyUserType(email);
	if (userType == 1)
	{
		Node<Student>* node = extractStudentFromEmail(email);
		if (!node)
			cout << "Loi email khong hop le." << endl;
		else
			viewStudent(node->data);
	}
	else if (!userType) // userType == 0
	{
		Node<Staff>* node = extractStaffFromEmail(email);
		if (!node)
			cout << "Loi email khong hop le." << endl;
		else
			viewStaff(node->data);
	}
	else
		cout << "Loi email khong hop le." << endl;
}

void logout() // skip for now cuz of no idea and main func dependance.
{

}

// login & manage profile
int testing1(int &userType, string &email)
{
	string fname = "login.csv.txt";
	if (loginSystem(fname, email))
	{
		userType = identifyUserType(email);
		return task1(email);
	}
	else
	{
		cout << endl << "Dang nhap that bai! Chuc ban may man lan sau." << endl;
		return -1;
	}
}

void main1()
{
	string email = ""; int userType = 0;
	cout << readStaffList("all_staffs.txt") << endl;
	cout << testing1(userType, email);
}