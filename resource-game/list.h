/*
Max Huecksteadt
CS 202

list.h- this file contains the header files for the Node and List classes. List is a doubly 
 linked list, with pointers to the Node class. Node has a Civilization pointer, which is
 upcasted to point to any derived class so dynamic binding can occur. All repetitive 
 operations in List are recursive. 
*/

#pragma once
#include "civ.h"
using std::string;

class Node
{
	public: 
		Node();
		Node*& get_next();
		Node*& get_prev();
		string& get_type();
		Civilization *& get_data();
		
	private: 
		Node* next;
		Node* prev; 
		Civilization * data;
		string type; 
};


class List
{
	public: 
		List();
		~List();
		List(const List& source);
		
		Civilization*& insert_node(string& civ_type);
		bool remove_node(string& civ_type);
		void remove_all();
		void display(); 
//		void harvest(string type);
		Civilization*& find(string& civ_type);

	private: 
		Node* head;
//		Node* tail;  

		Civilization*& insert_node(Node *& head, string& civ_type);
		bool remove_node(Node *& head, string& civ_type);	
		void remove_all(Node *& head);
		void display(Node *head);
		void copy(Node *& head, Node* source);
		//Civilization*& find(string& civ_type, Node *& head);
};
