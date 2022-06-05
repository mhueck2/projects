/*
Max Huecksteadt
CS 202
Program 2

app.cpp- This is the application class implementation. Application exists to build
	an interface for the user to play the game. Application has a menu based
	user interface, which gives the user different options of actions to take
	in each Civilization type (Forest, Farm, Mine).
*/

#include "app.h"

//app default constructor
app::app()
{
	List list;
	farm = new Farm;
	forest = new Forest;
	mine = new Mine;
}

//app destructor -this was causing a segfault but seems to leak no extra memory w/o 
/*app::~app()
{
	if (farm)
		delete farm;
	if (forest)
		delete forest;
	if (mine)
		delete mine; 
}
*/
//this function sets the initial values of the functions. It is separate from
//  the constructor because it was meant to take in user input to set the values for
//  each class. 
void app::init(List& list)
{
	string name;

	string s1 = "farm";
	string s2 = "mine";
	string s3 = "forest";			

 
	farm = list.insert_node(s1);	//insert nodes by type and get upcasted ptr 
	mine = list.insert_node(s2);
	forest = list.insert_node(s3);

//initialize farm values and get name from user 	
	farm->set_price(3);
	farm->set_resource_amt(5);
	farm->set_currency(30);
		
	cout << endl << "Welcome to Max's Civilizations!" << endl << endl 
	     << "Please enter a name for your Farm: " << endl; 
	getline(cin, name);
	farm->set_name(name);
	cout << endl;
	farm->display();
	cout << endl;

//initialize forest values and get name from user 
	name.clear();	
	forest->set_price(5);
	forest->set_resource_amt(3);
	forest->set_currency(30);
		
	cout << "Please enter a name for your Forest: " << endl; 
	getline(cin, name);
	forest->set_name(name);
	cout << endl;
	forest->display();
	cout << endl;
	
//initialize mine values and get name from user 
	name.clear();
	mine->set_price(10);
	mine->set_resource_amt(1);
	mine->set_currency(30);
		
	cout << "Please enter a name for your Mine: " << endl; 
	getline(cin, name);
	mine->set_name(name);
	cout << endl;
	mine->display();
	cout << endl;
}		

//this function is the main display for the application. It outputs the options for user
void app::display_menu()
{
	cout << "Please choose an action:" << endl << endl; 
	cout << "Forest options:" << endl; 
	cout << '\t' << "a: Harvest wood" << endl;
	cout << '\t' << "b: Sell wood for mushrooms (currency)" << endl; 
	cout << '\t' << "c: Buy ore with mushrooms" << endl; 
	cout << '\t' << "d: Buy food with mushrooms" << endl; 
	cout << '\t' << "e: Display current values for Forest" << endl;   
	cout << endl; 

	cout << "Farm options:" << endl; 
	cout << '\t' << "f: Harvest food" << endl;
	cout << '\t' << "g: Sell food for cheese (currency)" << endl; 
	cout << '\t' << "h: Buy ore with cheese" << endl; 
	cout << '\t' << "i: Buy wood with cheese" << endl; 
	cout << '\t' << "j: Display current values for Farm" << endl;   
	cout << endl;

	cout << "Mine options:" << endl; 
	cout << '\t' << "k: Harvest ore" << endl;
	cout << '\t' << "l: Sell ore for gold (currency)" << endl; 
	cout << '\t' << "m: Buy wood with ore" << endl; 
	cout << '\t' << "n: Buy food with ore" << endl; 
	cout << '\t' << "o: Build machine to reduce harvest time" << endl; 
	cout << '\t' << "p: Display current values for Mine" << endl << endl;   
	cout << '\t' << "q: Quit the program" << endl; 
}

//this is a helper function that gets the option the user has entered
char app::getOption()
{
		char option; 
		cin >> option;
		cin.ignore(MAX_CHAR, '\n');	
		return tolower(option);
}

//this function uses a switch statement and RTTI to determine what action to take from
//  the users input. 
void app::useOption(char option, List& list)
{
	float sell_amt = 0;
	float resource_amt = 0;	
	
	Forest * forest = dynamic_cast<Forest*>(this->forest);
	Mine * mine = dynamic_cast<Mine*>(this->mine);
	Farm * farm = dynamic_cast<Farm*>(this->farm);
	
	if (forest)
	{
		switch (option)  
		{
			case 'a': forest->harvest(); 
				break;

			case 'b': 
				cout << "Enter amount of wood to sell: ";
				cin >> sell_amt;
				forest->sell(sell_amt);
				cout << endl;
				sell_amt = 0;
				break;

			case 'c': 
				cout << "Enter amount of ore to buy: ";
				cin >> resource_amt;
				forest->buy_ore(resource_amt, mine->get_ore_price());	
				cout << endl; 
				resource_amt = 0;
				break;

			case 'd':
				cout << "Enter amount of food to buy: ";
				cin >> resource_amt;
				forest->buy_food(resource_amt, farm->get_food_price());	
				cout << endl; 
				resource_amt = 0;
				break; 	

			case 'e': forest->display(); 
				break;

		//	default: cout << "Please enter a valid command!" << endl; 
		//		break; 
		}
	}
	if (farm)
	{
		switch(option)
		{
			case 'f': farm->harvest(); 
				break;

			case 'g': 
				cout << "Enter amount of food to sell: ";
				cin >> sell_amt;
				farm->sell(sell_amt);
				cout << endl;
				sell_amt = 0;
				break;

			case 'h': 
				cout << "Enter amount of ore to buy: ";
				cin >> resource_amt;
				farm->buy_ore(resource_amt, mine->get_ore_price());	
				cout << endl; 
				resource_amt = 0;
				break;

			case 'i':
				cout << "Enter amount of wood to buy: ";
				cin >> resource_amt;
				farm->buy_wood(resource_amt, forest->get_wood_price());	
				cout << endl; 
				resource_amt = 0;
				break; 	

			case 'j': farm->display(); 
				break;

		//	default: cout << "Please enter a valid command!" << endl; 
		//		break; 
		}
	}
	if (mine)
	{
		switch (option)  
		{
			case 'k': mine->harvest(); 
				break;

			case 'l': 
				cout << "Enter amount of ore to sell: ";
				cin >> sell_amt;
				mine->sell(sell_amt);
				cout << endl;
				sell_amt = 0;
				break;

			case 'm': 
				cout << "Enter amount of wood to buy: ";
				cin >> resource_amt;
				mine->buy_wood(resource_amt, forest->get_wood_price());	
				cout << endl; 
				resource_amt = 0;
				break;

			case 'n':
				cout << "Enter amount of food to buy: ";
				cin >> resource_amt;
				mine->buy_food(resource_amt, farm->get_food_price());	
				cout << endl; 
				resource_amt = 0;
				break; 	

			case 'o': mine->build_machine();

			case 'p': mine->display(); 
				break;
			
			//default: cout << "Please enter a valid command!" << endl; 
			//	break; 
		}
	}
}

//this is a helper function used to clear the screen after input
void app::clear()
{
	for (int i=0; i<100; ++i)
	{
		cout << endl; 	
	}	


}

