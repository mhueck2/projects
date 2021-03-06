/*
Max Huecksteadt
CS 202
Program 2 

civ.cpp- this file contains the implementation for the civ.h file. This includes the classes Forest,
 Farm, Mine, and Civilization, the base class for the prior three derived classes. These are the 
 classes in the game, and this file does not contain any data structure implementations. 
*/

#include "civ.h"

//This is the Civilization class default constructor
Civilization::Civilization():civ_name(0)
{
}

//This is the Civilization class destructor. 
Civilization::~Civilization()
{
	if (civ_name)
		delete civ_name; 
}

//This is the Civilization class copy constructor
Civilization::Civilization(const Civilization& source)
{
	if (source.civ_name)
	{
		civ_name = new char[strlen(source.civ_name) + 1];
		strcpy(civ_name, source.civ_name);  
	}
}


//This sets the civilization base class name. This would be useful if the user 		to create more than one set of derived classes  
void Civilization::set_civ_name(char* civ)
{
	if (civ_name)
		delete civ_name; 
	civ_name = new char [strlen(civ) + 1];
	strcpy(civ_name, civ);
}

//this function calls the rand() function to randomly generate a harvest time. 
int Civilization::set_harvest_time()	
{
	int harvest_time;

	srand((time(NULL)));	

	harvest_time = rand() %10 + 1;
	return harvest_time; 
}

void Civilization::display_name()
{
	cout << civ_name << endl;  
	return; 
}




//*****************************************************
//Forest implementation: Forest is a derived class from Civilization, and has wood
// as a resource, and mushrooms as a currency. 
// The forest resources are stored in a class called resources (res)  
Forest::Forest(): name(""), wood_price(0), mushrooms(0)
{
	res = new resources; 
}

//This is the forest destructor, it deallocates and deletes the res * ptr in Forest
Forest::~Forest()
{
	if (res)
		delete res; 
	res = NULL;
}

//The harvest function compares a random number generated by 'set_harvest_time' with
// a number to determine whether the harvest can be carried out.
// If the number returned by set_harvest_time is greater than the constant number,
// the class will collect 1 unit of Wood. Otherwise the function must be run again. 
bool Forest::harvest()
{
	int time = 5; 
	if (time < set_harvest_time())
	{
		cout << "1x unit of wood harvested." << endl << endl;  
		res->add_wood(1);
		display(); 
		return true; 
	}
	else 
	{
		cout << "Not possible to harvest yet! Try again." << endl << endl; 
		return false; 
	}
} 	

//This function sells wood from the Forest class for mushrooms, the Forest class currrency. This is only possible if there is sufficient Wood, otherwise an error message prints prompting the user to harvest more. The function ends by displaying current information 
void Forest::sell(float amount)	
{
	if (res->compare_wood(amount))
	{
		res->sell_wood(amount);
		mushrooms += (amount * wood_price); 
		cout << amount << " units of wood sold at " << wood_price <<
			" mushroom each!" << endl << endl; 
	}
	else 
		cout << "Not enough wood to sell - must harvest more!" << endl << endl;
 	display();
	cout << endl; 
}

//This function sets the wood price to the passed in price. It is used at the start of the game to determine how much the wood costs per unit. 
void Forest::set_price(float resources)
{
	wood_price = resources; 
}


//This function buys ore for mushrooms, from the Mine class, adds to inventory arr. 
void Forest::buy_ore(float ore_amt, float cost)
{
	if (mushrooms >= (ore_amt*cost))
	{
		mushrooms -= (ore_amt*cost); 
		cout << ore_amt << " ore units bought at " << cost << " per unit!"
	             << endl; 	
		
		res->add_ore(ore_amt);
	}
	else 
		cout << "Not enough mushrooms to buy that much ore!" << endl; 
}


//this function buys food for mushrooms, adds bought food to inventory array  
void Forest::buy_food(float food_amt, float cost)
{
	if (mushrooms >= (food_amt*cost))
	{
		mushrooms -= (food_amt*cost);
		cout << food_amt << " food units bought at " << cost 
		     << " per unit!" << endl;
		res->add_food(food_amt);
	}
	else 
		cout << "Not enough mushrooms to buy that much food!" << endl; 
} 	

//this function must be implemented but does nothing in this class:
void Forest::buy_wood(float wood_amt, float cost)
{
}

float Forest::get_wood_price()
{
	return wood_price;
}	

//this function prints all of the information for the Forest class 
void Forest::display()
{
	cout << "Forest name: " << name << endl; 
	cout << "Current wood price: " << wood_price << endl; 	
	cout << "Current mushrooms (currency): " << mushrooms << endl; 
	cout << "Current wood amount: "; 
	res->display_wood();
	cout << endl; 
	cout << "Current ore amount: ";
	res->display_ore();
	cout << endl; 
	cout << "Current food amount: ";  
	res->display_food();
	cout << endl;
}


//this function sets the name of the Forest class
void Forest::set_name(string name)
{
	this->name = name; 
}


//this function sets the initial currency amount (to buy resources at start)
void Forest::set_currency(float curr)
{
	mushrooms = curr;
}


//this function sets the initial resource amount, so the starting Wood amount
void Forest::set_resource_amt(float amount)
{
	res->add_wood(amount);
}	 




//*******************************
//This is the implementation for the Farm class. Farm is a derived class from 
// Civilization, and has food as a resource, and cheese as a currency. 
// Farm has a pointer to the resources class to store food, wood, and ore 
Farm::Farm(): name(""), food_price(0), cheese(0) 
{
	res = new resources; 
}


//This is the Farm destructor, it deallocates and resets the resource class ptr. 
Farm::~Farm()
{
	if (res)
		delete res; 
	res = NULL;
}
//This function harvests Food for the farm class. It compares the set_harvest_time 
// returned with a value such that the chance of harvest is ~50%. It returns a true 
// if it is successful along with a message, or returns false with a message. 
bool Farm::harvest()
{
	int time = 5; 
	if (time < set_harvest_time())
	{
		cout << "1x unit of food harvested." << endl << endl;  
		res->add_food(1);
		display();
		cout << endl;  
		return true;
	}
	else 
	{
		cout << "Not possible to harvest yet! Try again." << endl; 
		return false; 
	}
}


//this function sells whatever amount of food that is passed in, if that is possible. 
// if not possible the function returns an error message 
void Farm::sell(float amount)
{
	if (res->compare_food(amount))
	{
		res->sell_food(amount);
		cheese += (amount * food_price); 
		cout << amount << " units of food sold at " << food_price 
		     << " cheese each"  << endl << endl; 
	}
	else 
		cout << "Not enough food to sell - must harvest more!" << endl << endl;
 	display();
	cout << endl; 
}

float Farm::get_food_price()
{
	return food_price;
}

//this function sets the price of food to the passed in price. Used at the beginning
// of a game to set values to the users specs
void Farm::set_price(float resources)
{
	food_price = resources;
}


//this function buys ore from the Mine class in exchange for cheese 
void Farm::buy_ore(float ore_amt, float cost)
{
	if (cheese >= (ore_amt*cost))
	{
		cheese -= (ore_amt*cost); 
		cout << ore_amt << " ore units bought at " 
		     << cost << " per unit!" << endl; 	
		res->add_ore(ore_amt);
	}
	else 
		cout << "Not enough cheese to buy that much ore!" << endl; 
}


//this function buys wood from the Forest class in exchange for cheese 
void Farm::buy_wood(float wood_amt, float cost)
{
	if (cheese >= (wood_amt*cost))
	{
		cheese -= (wood_amt*cost); 
		cout << wood_amt << " wood units bought at " 
		     << cost << " per unit!" << endl; 	
		res->add_wood(wood_amt);
	}
	else 
		cout << "Not enough cheese to buy that much wood!" << endl; 
}

//this function does nothing but must be implemented 
void Farm::buy_food(float food_amt, float cost)
{
}

//This function prints all the information of the Farm class
void Farm::display()
{
	cout << "Farm name: " << name << endl; 
	cout << "Current food price: " << food_price << endl; 	
	cout << "Current cheese (currency): " << cheese << endl; 
	cout << "Current food amount: ";  
	res->display_food();
	cout << endl << "Current wood amount: ";
	res->display_wood();
	cout << endl << "Current ore amount: ";  
	res->display_ore();
	cout << endl; 
}


//this function sets the Farm name to the passed in argument 
void Farm::set_name(string name)
{
	this->name = name; 
}


//this function sets the amount of cheese to the passed in amount 
void Farm::set_currency(float curr)
{
	cheese = curr;
}


//this function sets the amount of Food for the Farm class. 
void Farm::set_resource_amt(float amount)
{
	res->add_food(amount);
}











//***************************
//This is the implementation for the Mine class. Mine harvests ore and sells it to gain
// 	gold, its currency. Mine has a special non-virtual function called build machine
//	which increases the chance of a harvest. This is only possible once Mine has 
//	enough gold, which is 10x whatever the price of ore sells for (user set).  

//This is the Mine default constructor, Mine has an int vector to store the resources
//	it has bought from other classes. It stores food in 0 and wood in 1.
Mine::Mine():name(""), ore_price(0), gold(0), time(5)
{
	res = new resources;
}

//This is the Mine destructor 
Mine::~Mine()
{
	if (res)
		delete res; 
	res = NULL;
}



//This function harvests ore for the mine class. It compares the set_harvest_time 
// returned with a value such that the chance of harvest is ~50%. It returns a true 
// if it is successful along with a message, or returns false with a message. 
bool Mine::harvest()
{
	if (time < set_harvest_time())
	{
		cout << "1x unit of ore harvested." << endl << endl;  
		res->add_ore(1);
		display(); 
		cout << endl;
		return true;
	}
	else 
	{
		cout << "Not possible to harvest yet! Try again." << endl; 
		return false; 
	}
}

float Mine::get_ore_price()
{
	return ore_price;
}
//this function sells whatever amount of ore that is passed in, if that is possible. 
// if not possible the function returns an error message 
void Mine::sell(float amount)
{
	if (res->compare_ore(amount))
	{
		res->sell_ore(amount); 
		gold += (amount * ore_price); 
		cout << amount << " units of ore sold at " 
		     << ore_price << " gold per unit!" << endl << endl; 
	}
	else 
	    cout << "Not enough ore to sell - must harvest more!" << endl <<endl;
 	display();
	cout << endl; 
}


//this function sets the price of ore to the passed in price. Used at the beginning
// of a game to set values to the users specs
void Mine::set_price(float resources)
{
	ore_price = resources;
}


//this function buys food from the Farm class in exchange for gold 
void Mine::buy_food(float food_amt, float cost)
{
	if (gold >= (food_amt*cost))
	{
		gold -= (food_amt*cost); 
		cout << food_amt << " food units bought at " 
		     << cost << " per unit!" << endl; 	
		res->add_food(food_amt);
	}
	else 
		cout << "Not enough gold to buy that much food!" << endl; 
}


//this function buys wood from the Forest class in exchange for gold 
void Mine::buy_wood(float wood_amt, float cost)
{
	if (gold >= (wood_amt*cost))
	{
		gold -= (wood_amt*cost); 
		cout << wood_amt << " wood units bought at " 
		     << cost << " per unit!" << endl; //**might need deref	
		res->add_wood(wood_amt); 
	}
	else 
		cout << "Not enough gold to buy that much wood!" << endl; 
}


//this function does nothing in this class but must be implemented: 
void Mine::buy_ore(float ore, float cost)
{
}

//This function prints all the information of the Mine class
void Mine::display()
{
	cout << "Mine name: " << name << endl; 
	cout << "Current ore price: " << ore_price << endl; 	
	cout << "Current gold (currency): " << gold << endl; 
	cout << "Current ore amount: ";  
	res->display_ore();
	cout << endl; 
	cout << "Current wood amount: "; 
	res->display_wood();
	cout  << endl;
	cout << "Current food amount: ";  
	res->display_food();
	cout << endl;
}


//this function sets the Mine name to the passed in argument 
void Mine::set_name(string name)
{
	this->name = name; 
}


//this function sets the amount of gold to the passed in amount 
void Mine::set_currency(float curr)
{
	gold = curr;
}


//this function sets the amount of Food for the Mine class. 
void Mine::set_resource_amt(float amount)
{
	res->add_ore(amount);
}


//this function is the special RTTI function. It increases the change of a harvest by
//	increasing the probability the harvest function will return true. 
void Mine::build_machine()
{
	if (time >= 1)
	{
		--time;
		cout << "Machine built. Harvest time reduced!" << endl; 
	}
	else 
		cout << "Cannot harvest any faster!" << endl; 
}
