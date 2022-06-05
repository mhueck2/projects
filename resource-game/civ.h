/*
Max Huecksteadt
CS 202

civ.h- This is the header file for the civilization class, and its derived classes, Forest,
 Farm, and Mine. Civilization is an Abstract Base class, and has the prototypes for the 
 functions common to Forest, Farm, and Mine, in addition to its own setters and methods. 

*/

#pragma once
#include "res.h"

using namespace std;

class Civilization
{
	public:
		Civilization();
		virtual ~Civilization(); //virutal destructor for delayed invocation
		Civilization(const Civilization& source);
		void set_civ_name(char* civ);
		int set_harvest_time();	 	
		void display_name();		
	
		virtual bool harvest() = 0;
		virtual void sell(float amount) = 0; 
		virtual void set_price(float resource) = 0; 
		virtual void display() = 0;
		virtual void set_name(string name) = 0;
		virtual void set_resource_amt(float amount) = 0; 
		virtual void set_currency(float curr) = 0;
		virtual void buy_ore(float ore_amt, float cost) = 0;
		virtual void buy_food(float food_amt, float cost) = 0;
		virtual void buy_wood(float wood_amt, float cost) = 0;
				
	protected: 
		char* civ_name;
};


class Forest:public Civilization
{
	public: 
		Forest();
		~Forest();

		//virtual functions:
		bool harvest();
		void sell(float amount);
		void set_price(float resources);
		void buy_ore(float ore_amt, float cost);
		void buy_food(float food_amt, float cost);
		void buy_wood(float wood_amt, float cost); 
		void display();
		void set_name(string name); 
		void set_currency(float curr);
		void set_resource_amt(float amount);	//used for init values 
		float get_wood_price();
	
			
	protected: 
		string name; 
		float wood_price; 
		float mushrooms;
		resources * res;
};

class Farm:public Civilization
{
	public: 
		Farm();
		~Farm();		

		//virtual functions: 
		bool harvest();
		void sell(float amount);
		void set_price(float resources); 
		void buy_ore(float ore_amt, float cost);
		void buy_food(float food_amt, float cost);	
		void buy_wood(float wood_amt, float cost);
		void display(); 
		void set_name(string name);
		void set_currency(float curr);
		void set_resource_amt(float amount); 
		float get_food_price();
	
	protected:
		string name; 
		float food_price; 
		float cheese; 	
		resources * res; 
};

class Mine:public Civilization
{
	public: 
		Mine();
		~Mine();
		void build_machine(); //RTTI function- reduces ore harvest time 	
		//virtual functions:
		bool harvest();
		void sell(float amount);
		void set_price(float resources);
		void buy_ore(float ore, float cost);
		void buy_food(float food_amt, float cost);
		void buy_wood(float wood_amt, float cost); 
		void display();
		void set_name(string name);
		void set_currency(float curr);
		void set_resource_amt(float amount);
		float get_ore_price();

	protected: 
		string name; 
		float ore_price; 
		float gold;	
		int time; 
		resources * res; 
};	
