#include "Header1.h"

int countLinesInCSV(string fname)
{
	ofstream fp;
	fp.open(fname, ios::in);
	if (fp.is_open() == false)
		return -1;
	else
	{
		int count = 0; char a;
		while(!fp.eof())
		{
			fp << a;
			if (a - '\n' == 0)
				count++;
		}
		fp.close();
		return count + 1;
	}
}

bool readLoginIn4(string fname, string** &container, int& col, int& row)
{
	ifstream fp;
	fp.open(fname, ios::in);
	if (fp.is_open() == false)
		return false;
	else
	{
		row = countLinesInCSV(fname), col = 2;
		container = new string * [row];
		for (int i = 0; i < row; ++i)
		{
			container[i] = new string[col];
			fp.ignore();
			fp.getline(container[i][0], 40, ',');
			fp.getline(container[i][1], 40, '\n');
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

bool loginSystem(string fname)
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
		string email, pass;
		int email_exist, count = 0;
		do
		{
			cout << "So lan co dang nhap: " << count << ". Ban chi co 5 lan thu. Nhap email: "; cin.getline(email, 40);
			email_exist = checkExistEmail(loginData, row, email);
			count++;
		} while (email_exist == -1 && count != 5);
		if (count == 5)
		{
			cout << "Ban da het so lan dang nhap. Chuc ban may man lan sau. ";
			return false;
		}
		else if (email_exist != 1)
		{
			count = 0;
			do
			{
				cout << "So lan co dang nhap: " << count << ". Ban chi co 5 lan thu. Nhap mat khau: "; cin.getline(pass, 40);
				count++;
			} while (pass.compare(loginData[email_exist][1]) != 0 && count != 5);
		}
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
}

void changePassword()
{

}

void printProfileInfo()
{

}

void logout()
{

}