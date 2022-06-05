/*
Max Huecksteadt	
CS 202
Program 2

This class simply exists to bundle a derived class' resources in one place. It 
 is used in buying and selling resources, to adjust the amounts 
*/

#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <time.h>
#include <vector>

class resources
{
	public: 
		resources();
		void add_wood(float amount);
		void sell_wood(float amount);
		void add_food(float amount);	
		void sell_food(float amount);
		void add_ore(float amount);	
		void sell_ore(float amount);
		void display_wood();
		void display_food();
		void display_ore();
		bool compare_wood(float amount);
		bool compare_food(float amount);
		bool compare_ore(float amount);


	protected: 
		float wood_amt; 
		float food_amt; 
		float ore_amt;

};
