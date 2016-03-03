// Sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ElementTest.h"
#include "StructureTest01.h"
#include "MatixTest.h"
#include <iostream>

using namespace std;

int main()
{
	int i;

	do
	{
		cout << "Press 1 for element test" << endl;
		cout << "Press 2 for structure test 01" << endl;
		cout << "Press 3 for matix test 01" << endl;
		cout << endl;
		cout << "Press 0 to exit" << endl;

		// User input
		cin >> i;

		// Element test
		if (i == 1)
		{
			ElementTest et;
			et.EdofTest();
		}
		else if (i == 2)
		{
			StructureTest01 st;
			st.RunTest();
		}
		else if (i == 3)
		{
			MatixTest mt;
		}
	} while (i != 0);

    return 0;
}


