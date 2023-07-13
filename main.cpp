#include "Header1.h"

int main()
{
	string fname = "login.csv.txt";
	string email;
	if (loginSystem(fname, email) == true)
	 	changePassword(fname, email);
	else
		cout << "Khong doi mat khau duoc.";
	return 0;
}