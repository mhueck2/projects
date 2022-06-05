/*
Max Huecksteadt
CS 202 
Program 2

main.cpp- this is the implementation of main, which calls the application class in order to run the
 program. 
*/

using namespace std; 
#include "main.h"


int main()
{
	char option;
	app app;
	List list;
	app.init(list);
	while (option != 'q')
	{
		app.useOption(option, list);
		app.display_menu();		
		option = app.getOption();
		app.clear();
	}

	return 0; 
}
