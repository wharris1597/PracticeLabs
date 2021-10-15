#include "Inventory.h"
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


int main()
{
	char cont;
	SalesTracker day1;
	day1.DisplayMenu();
	int choice = day1.MenuSelection();
	while (choice != 4) {
		cout << "Press y to return to the menu, any other key to exit: ";
		cin >> cont;
		if (cont == 'y') {
			day1.DisplayMenu();
			day1.MenuSelection();
		}
		else break;
	}


	return 0;
};

