/*
Max Huecksteadt
CS 202

list.cpp- This file contains the implementation for the List and Node classes. 
  List is a doubly linked list that contains a pointers to a Node class, which 
contains pointers to the previous and next Nodes in the list, as well as a pointer
to the indirect base class Civilization. 
  The client code will use this base pointer to point to the derived classes
through dynamic binding, to make function calls. The list is designed to hold
three Nodes (one for each derived class), but can hold an indefinite amount. 

  The list implements the following functions: insert, remove, display, and 
remove all. 
*/

#include "list.h"


//**************************
//This is the Node implementation 

//this is the Node default constructor. It initializes the pointers in Node to null.  
Node::Node():next(0), prev(0), data(0), type("") 
{
}


//this is the get_next function- it gets (and can set) the next pointer.
Node*& Node::get_next()
{
	return next;
}


//this is the get_prev function- it gets (and can set) the previous pointer. 
Node *& Node::get_prev()
{
	return prev;
}



string& Node::get_type()
{
	return type;
}


Civilization*& Node::get_data()
{
	return data;
}




//****************************
//This is the implementation for the List class:

//This is the default constructor, it sets the head and tail pointers to null. 
List::List():head(0)
{
}	

//this is the list destructor, it calls the remove all function to destroy the list. 
List::~List()
{
	remove_all(head);
}

//This is the list copy constructor. It copies the List into a new list   
List::List(const List& source)
{
	copy(head, source.head);
}	



//this is a copy function to be used in the copy constructor (private helper)
void List::copy(Node*& head, Node*  source)
{
	if (head)
		delete head;

	if (!source)
	{
		head = NULL;
		return;
	}		
	
	head = new Node; 	
	Forest * forest = new Forest;
	Farm * farm = new Farm;
	Mine * mine = new Mine;

	forest  = dynamic_cast<Forest*>(source->get_data());
	if (forest)
		head->get_data() = new Forest;	
	else 
	{
		farm = dynamic_cast<Farm*>(source->get_data());
		if (farm)
			head->get_data() = new Farm;
		else
		{
			mine = dynamic_cast<Mine*>(source->get_data());
			if (mine)
				head->get_data() = new Mine;
		}
	}		
	copy(head->get_next(), source->get_next()); 
}


//this function inserts a node at the beginning of the list
Civilization*& List::insert_node(string& civ_type)
{	
	return insert_node(head, civ_type);
}


//this function inserts a node at the start of the list. (private helper function)
Civilization*& List::insert_node(Node *& head, string& civ_type)
{
	if (!head)	//list doesn't exist, so create a node 
	{
		head = new Node;	
		head->get_prev() = NULL;
		head->get_next() = NULL;
		head->get_type() = civ_type;
		
		if (head->get_type() == "farm")	//upcast node here for return 
		{
			head->get_data() = new Farm; 
			return head->get_data();
		}
		if (head->get_type() == "forest")
		{
			head->get_data() = new Forest;
			return head->get_data();
		}
		if (head->get_type() == "mine")
		{
			head->get_data() = new Mine;
			return head->get_data();
		}
	}
	if (head)	//insert at beginning of list 
	{
		Node * temp = head;
		temp = new Node;
		temp->get_next() = head;
		temp->get_prev() = NULL;
		head->get_prev() = temp;
		head = temp;
		head->get_type() = civ_type;

		if (head->get_type() == "farm")	//upcast node here for return
		{
			head->get_data() = new Farm; 
			return head->get_data();
		}
		if (head->get_type() == "forest")
		{
			head->get_data() = new Forest;
			return head->get_data();
		}
		if (head->get_type() == "mine")
		{
			head->get_data() = new Mine;
			return head->get_data();
		}
	}	
}


//this function is a wrapper for the private recursive remove  
bool List::remove_node(string& civ_type)
{
	if (head)
		return remove_node(head, civ_type);
	else 
		return false; 
}

//this function removes a node by value recursively
bool List::remove_node(Node*& head, string& civ_type)
{
	if (head->get_type() == civ_type)
	{
		if (!head->get_prev())
		{
			Node * temp = head; 
			head = head->get_next();	
			delete temp;
			head->get_prev() = NULL;
			return true;
		}
		if (head->get_next())
		{
			head->get_next()->get_prev() = head->get_prev();
			head->get_prev()->get_next() = head->get_next();
			delete head; 
			return true; 
		}	
		else
		{
			head->get_prev()->get_next() = NULL;
			delete head;
			return true; 
		}
	}
	remove_node(head->get_next(), civ_type);
	
	return false; 	
}


//this function removes all the nodes in the list. It is called in the destructor also
void List::remove_all()
{
	remove_all(head);
}

//this is the private helper function version of remove_all
void List::remove_all(Node*& head)
{
	if (!head)
		return;
	remove_all(head->get_next());	
	delete head->get_data();
	delete head;
}


//this function is a wrapper for the protected recursive display 
void List::display()
{
	if (head)
		display(head);	
	else 
		return;
}

//this function displays the list nodes recursively
void List::display(Node * head)
{
	if (!head)
		return;
	cout << head->get_type() << endl;
	display(head->get_next());
}
