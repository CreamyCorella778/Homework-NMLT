#include "Header1.h"
#include "Header2.h"

int testing4(string& email)
{
	bool userType = false;  string fname = "login.csv.txt";
	int res_testing1 = testing1(userType, email);
	if (res_testing1 == 3)
	{
		int func = 0;
		Date today = getTodayIn4();
		Semester curr = identifySemesterByToday(today)->data;
		if (!userType)
		{
			int part = whenInSemester(curr, today);
			if (part < 1)
			{
				cout << "Loi he thong. Chuc ban may man lan sau" << endl;
				return -1;
			}
			else if (part == 3)
			{

			}
		}
	}
}