#include <iostream>
#include <limits>


using std::cout;
using std::cin;

using namespace std;


short int menu();
	


short int menu()
{
	cout << "Menu\n" << "Select menu item\n";
	cout << "1 - add pipeline\n";
	cout << "2 - pipelines\n";
	cout << "3 - add CS\n";
	cout << "4 - CSs\n";
	cout << "5 - save in file\n";
	cout << "6 - download from file\n";
	cout << "7 - all objects\n";
	cout << "8 - delete pipe\n";
	cout << "9 - delete cs\n";
	cout << "10 - filter pipes by name\n";
	cout << "11 - filter pipes by rapair\n";
	cout << "12 - change pipes\n";
	cout << "13 - change cs\n";
	cout << "0 - exit\n";
	cout << "14 - filter cs by name\n";
	cout << "--------------------------------------------------------------------\n";

	short int menu_choice;

	while (!(cin >> menu_choice)  || (cin.peek() != '\n') || (menu_choice < 0 || menu_choice > 14)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "" << "Select correct item from menu:\n";
	};

	return menu_choice;
};
