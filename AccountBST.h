#pragma once
#include "AccountBSTNode.h"
#include <queue>
#include <fstream>
#include <iostream>
using namespace std;

class AccountBST
{
private:
	AccountBSTNode* Root;

public:
	AccountBST();
	~AccountBST();

	AccountBSTNode* GetRoot();
	bool Insert(AccountBSTNode* node);
	bool Search_Id(char* id);	//Search id 
	bool Search_Id_and_print(char* id);		//Search id and print
	char* return_name(char* id);
	AccountBSTNode* SearchMinNode(AccountBSTNode* pNode);	//Search Minimum Node
	bool Delete(char* id);	//Delete a specific Node
	void Print_PRE(AccountBSTNode* node);
	void Print_IN(AccountBSTNode* node);
	void Print_POST(AccountBSTNode* node);
	void Print_LEVEL();
	bool EMPTY();	//To check if the bst is empty
};
