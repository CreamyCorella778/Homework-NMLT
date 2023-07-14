#include "Header1.h"

int main()
{
	string fname = "22CTT2.txt"; int n = 0;
	Student* a = addStudentsFromCSV(fname, n);
	for (int i = 0; i < n; ++i)
	{
		cout << a[i].no << ". " << a[i].stuID << ", " << a[i].firstName << " " << a[i].lastName;
		if (a[i].gender)
			cout << ", nam, ";
		else
			cout << ", nu, ";
		cout << a[i].birth.day << "/" << a[i].birth.month << "/" << a[i].birth.year
			<< ", " << a[i].socialID << endl;

	}
	return 0;
}