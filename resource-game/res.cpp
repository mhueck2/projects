/*
Max Huecksteadt
CS 202
Program 2

Resource class implementation. Resource is simply a class to hold the amounts of 
 the various amounts of each resource in each civilization type. The functions 
 exist merely to update the amount of resources while buying and selling. 
*/

#include "res.h"
using namespace std; 

//The resources default constructor sets all resources to zero. 
resources::resources(): wood_amt(0.0), food_amt(0.0), ore_amt(0.0)
{
}

//This function adds the amount of wood bought to the wood amount data member 
void resources::add_wood(float amount)
{
	wood_amt += amount;  
}

//This function subtracts the amount of wood bought to the amount data member 
void resources::sell_wood(float amount)
{
	wood_amt -= amount;  
}

//This function adds the amount bought to food 
void resources::add_food(float amount)
{
	food_amt += amount;  
}

//This function updates the amount of food once it is sold 
void resources::sell_food(float amount)
{
	food_amt -= amount;  
}

//this function updates the amount of ore once it is bought 
void resources::add_ore(float amount)
{
	ore_amt += amount;  
}

//this function updates the amount of ore once it is sold 
void resources::sell_ore(float amount)
{
	ore_amt -= amount;  
}

//this function displays the wood amount 
void resources::display_wood()
{
	cout << wood_amt;
}

//this function displays the food amount 
void resources::display_food()
{
	cout << food_amt;
}

//this function displays the ore amount 
void resources::display_ore()
{
	cout << ore_amt;
}


bool resources::compare_ore(float amount)
{
	if (ore_amt >= amount)
		return true;
	else 
		return false; 
}	


bool resources::compare_wood(float amount)
{
	if (wood_amt >= amount)
		return true; 
	else 
		return false; 
}

bool resources::compare_food(float amount)
{
	if (food_amt >= amount)
		return true; 
	else 
		return false; 
}


