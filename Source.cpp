/* 
This program from Chada Tech is built for Corner Grocer. This program will allow the facility to find out the number
of sales of specific inventory during a specific time period, generally the same day. Options will include printing
out a full list of all the produce sold that day, requesting specific produce and sales for that day and presenting
the sales of produce as a histogram. This program was produced with C++ and Python. 
Author: Enrique Zarate
Date: 6/20/2021
*/

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
	PyObject* my_module = PyImport_ImportModule("myfirstprogram");
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
	pName = PyUnicode_FromString((char*)"myfirstprogram");
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
	pName = PyUnicode_FromString((char*)"myfirstprogram");
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


/*
Description:
	Function to print the histogram from the 'frequency.dat' file that was created by Python. 
*/
void histogramPrint() {
	ifstream inFS;
	inFS.open("frequency.dat");
	string product;
	int numberProducts;
	int i;
	int j;
	inFS >> product;
	inFS >> numberProducts;
	while (!inFS.eof()) {
		cout << product << " ";
		for (j = 0; j <= numberProducts; j++) {
			cout << "*";
		}
		cout << endl;
		inFS >> product;
		inFS >> numberProducts;
	}
	inFS.close();
}

void main()
{
	int userInput;
	userInput = -1;
	string searchItem;
		
		//Presenting Menu of Options for User. Menu Options describe Switch-Case Actions Below
		while (userInput != 4) {
			cout << "Please select from the numbers below:" << endl;
			cout << "1: Print list of all products purchased from the store today." << endl;
			cout << "2: Search for a specific product and get the quantity of that product sold today." << endl;
			cout << "3: Print a histogram of items sold today." << endl;
			cout << "4: Exit the Program" << endl << endl;
			cin >> userInput;

			// Validate User Input to verify it is a number. If this is not present, the program will loop infinitely.
			if (cin.fail()) { 
				cout << "You entered something other than a number. Taking you back to the beginning." << endl;
				cout << endl;
				cin.clear();
				cin.ignore();
				continue;
			}

			switch (userInput) {
			case 1: 
				CallProcedure("finalSalesList");
				cout << endl << endl;
				break;
			case 2:
				cout << "Which product are you interested in finding out sales for?" << endl;
				cout << "Note: All items are listed in their plural form." << endl;
				cin >> searchItem;
				// This loop handles the string in order to make it match the list when searching. 
				for (int i = 0; i < searchItem.length(); i++) {
					if (i == 0) {
						searchItem[i] = toupper(searchItem[i]);
					}
					else {
						searchItem[i] = tolower(searchItem[i]);
					}
				}
				cout << endl <<  callIntFunc("searchSalesList", searchItem) << endl;
				break;
			case 3:
				CallProcedure("histogramCreator");
				histogramPrint();
				cout << endl << endl;
				break;
			case 4:
				break;
			default:
				cout << endl << "Looks like you entered an invalid option. Please try again." << endl;
			}
			cout << endl;
	}

		cout << "Thanks for using our program. Program is now shutting down." << endl;
	


}