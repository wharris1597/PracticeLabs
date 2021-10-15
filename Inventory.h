#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace std;

class SalesTracker
{
	string item;

public:
	void DisplayMenu() {//displays the menu
		cout << "Hello! What would you like to view today? Please enter a number from the menu below!" << endl;
		cout << endl;
		cout << "1: Today's Purchase History" << endl;
		cout << "2: Today's Purchase History for a Specific Item" << endl;
		cout << "3: VIsual Representation of Today's Purchase History" << endl;
		cout << "4: Exit Program" << endl;
		cout << endl;
		cout << "Choice: ";
	};
	int MenuSelection() {
		int x;
		int numSold;
		string searched_item;
		cin >> x;
		switch (x) {//switch case for menu options
		case 1: cout << "Getting Today's Purchase Data... " << endl;
			CallProcedure("ItemsSoldToday"); break;//print total purchase data for that day
		case 2: cout << "Getting data for item... " << endl;
			searched_item = GetSearchItem();
			numSold = callIntFunc("ItemLookup", searched_item);
			cout << "We sold " << numSold << " " << searched_item << endl; break;//print number of items sold that day for item user entered
		case 3: cout << "Getting data for histogram..." << endl; CallProcedure("HistogramData"); PrintHistogram(); break;
		case 4: cout << "Thank you. Bye!" << endl; break;//exit program
		default: cout << "Invalid. Enter a number from the menu: " << endl;
			cin.clear();//clear cin 
			cin.ignore(100, '\n'); MenuSelection(); break;

		}
		return x;
	};
	/*
	Description:
		To call this function, simply pass the function name in Python that you wish to call.
	Example:
		callProcedure("printsomething");
	Output:
		Python will print on the screen: Hello from python!
	Return:
		None
	*/
	void CallProcedure(string pName)
	{

		char* procname = new char[pName.length() + 1];
		std::strcpy(procname, pName.c_str());

		Py_Initialize();
		PyObject* my_module = PyImport_ImportModule("PythonCode");
		PyErr_Print();
		PyObject* my_function = PyObject_GetAttrString(my_module, procname);
		PyObject* my_result = PyObject_CallObject(my_function, NULL);
		Py_Finalize();

		delete[] procname;
	}
	/*
	Description:
		To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
	Example:
		int x = callIntFunc("PrintMe","Test");
	Output:
		Python will print on the screen:
			You sent me: Test
	Return:
		100 is returned to the C++
	*/
	int callIntFunc(string proc, string param)
	{
		char* procname = new char[proc.length() + 1];
		std::strcpy(procname, proc.c_str());

		char* paramval = new char[param.length() + 1];
		std::strcpy(paramval, param.c_str());


		PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
		// Initialize the Python Interpreter
		Py_Initialize();
		// Build the name object
		pName = PyUnicode_FromString((char*)"PythonCode");
		// Load the module object
		pModule = PyImport_Import(pName);
		// pDict is a borrowed reference 
		pDict = PyModule_GetDict(pModule);
		// pFunc is also a borrowed reference 
		pFunc = PyDict_GetItemString(pDict, procname);
		if (PyCallable_Check(pFunc))
		{
			pValue = Py_BuildValue("(z)", paramval);
			PyErr_Print();
			presult = PyObject_CallObject(pFunc, pValue);
			PyErr_Print();
		}
		else
		{
			PyErr_Print();
		}
		//printf("Result is %d\n", _PyLong_AsInt(presult));
		Py_DECREF(pValue);
		// Clean up
		Py_DECREF(pModule);
		Py_DECREF(pName);
		// Finish the Python Interpreter
		Py_Finalize();

		// clean 
		delete[] procname;
		delete[] paramval;


		return _PyLong_AsInt(presult);
	}
	/*
	Description:
		To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
	Example:
		int x = callIntFunc("doublevalue",5);
	Return:
		25 is returned to the C++
	*/
	int callIntFunc(string proc, int param)
	{
		char* procname = new char[proc.length() + 1];
		std::strcpy(procname, proc.c_str());

		PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
		// Initialize the Python Interpreter
		Py_Initialize();
		// Build the name object
		pName = PyUnicode_FromString((char*)"PythonCode");
		// Load the module object
		pModule = PyImport_Import(pName);
		// pDict is a borrowed reference 
		pDict = PyModule_GetDict(pModule);
		// pFunc is also a borrowed reference 
		pFunc = PyDict_GetItemString(pDict, procname);
		if (PyCallable_Check(pFunc))
		{
			pValue = Py_BuildValue("(i)", param);
			PyErr_Print();
			presult = PyObject_CallObject(pFunc, pValue);
			PyErr_Print();
		}
		else
		{
			PyErr_Print();
		}
		//printf("Result is %d\n", _PyLong_AsInt(presult));
		Py_DECREF(pValue);
		// Clean up
		Py_DECREF(pModule);
		Py_DECREF(pName);
		// Finish the Python Interpreter
		Py_Finalize();

		// clean 
		delete[] procname;

		return _PyLong_AsInt(presult);
	}
	string GetSearchItem() {
		string x;
		cout << "Enter the item you would like to search for: ";
		cin >> x;
		return x;
	};
	void PrintHistogram() {
		int numStars;
		ifstream f;
		f.open("frequency.dat");
		if (f.is_open()) {
			cout << "frequency.dat file opened successfully." << endl;
			cout << endl;
			cout << "            Today's Purchase Data           " << endl;
			cout << "               (* = 1 item)                   " << endl;
			cout << endl;
			while (f.good()) {
				f >> item;
				if (!f.good())
					continue;
				f >> numStars;
				numStars = int(numStars);

				cout << left << setw(15) << item;
				while (numStars > 0) {
					cout << '*';
					numStars = numStars - 1;
				}
				cout << endl;
			}
			cout << endl;
		}
		else
			cout << "Error opening frequency.dat file.";


	}
};

