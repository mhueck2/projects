/*
Max Huecksteadt
CS 202
Program 2

app.h- This is the application header file. The application manages the user 
	interface for the game, as well as calling the functions from the various
	classes (types of civilizations). The application allows the user to build 
	3 different types of societies and buy and sell products. 
*/

#include "list.h"

class app
{
	public:
		app();
		//~app();
		void init(List& list);	
		void display_menu();
		char getOption();
		void useOption(char option, List& list);
		void clear();

	protected: 
		List list;  
		const char MAX_CHAR = 99;
		Civilization * farm;
		Civilization * forest;
		Civilization * mine;
		
};	
