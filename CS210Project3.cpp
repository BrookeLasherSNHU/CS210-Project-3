#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

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
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
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

void printFrequencyHistogram()
{
	ifstream frequencyFile;
	frequencyFile.open("frequency.dat");
	string line;
	// Reads each line from the frequency file.
	while (getline(frequencyFile, line)) {
		if (line.length() > 0) {
			// Reads the item and the count from each line, separated by a space.
			string item = line.substr(0, line.find(' '));
			int count = stoi(line.substr(line.find(' ') + 1));
			// Outputs the item name, followed by an amount of asterisks equal to the item's count.
			cout << item + string(16 - item.length(), ' ') + string(count, '*') << endl;
		}
	}
}

int showMenu()
{
	cout << "1: Count All Items" << endl;
	cout << "2: Count Specific Item" << endl;
	cout << "3: Create Histogram" << endl;
	cout << "4: Exit" << endl;
	int choice;
	cin >> choice;
	return choice;
}

void main()
{
	while (true) {
		int menuChoice = showMenu();
		while (menuChoice <= 0 || menuChoice > 4) {
			// Makes the user choose again if they choose an invalid choice in the menu.
			cout << "Please choose option 1, 2, 3, or 4." << endl;
			menuChoice = showMenu();
		}
		if (menuChoice == 1) {
			// Calls python function to count all items, then print the result.
			CallProcedure("CountAllItems");
			continue;

		}
		else if (menuChoice == 2) {
			// Calls a python function to count a specific item, then uses C++ to print the result.
			cout << "Enter an item to count." << endl;
			string counted_item;
			cin >> counted_item;
			cout << counted_item << ": " << callIntFunc("CountOneItem", counted_item) << endl;
			continue;
		}
		else if (menuChoice == 3) {
			// Counts all items, writing them to frequency.dat
			CallProcedure("CountAllItemsToFile");
			// Reads frequency.dat, printing a histogram.
			printFrequencyHistogram();
		}
		else if (menuChoice == 4) {
			// Simply ends the main loop, exiting the program.
			cout << "Exiting...";
			break;
		}
	}

}