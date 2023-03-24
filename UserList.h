#pragma once
#include "UserListNode.h"
#include "AccountQueueNode.h"
#include <fstream>
#include <iostream>

using namespace std;

class UserList
{
private:
	UserListNode* Root;
	UserListNode* pNext;

public:
	UserList();
	~UserList();

	UserListNode* GetRoot();
	UserListNode* GetNext();
	void SetNext(UserListNode* node);
	AccountBSTNode* Insert(AccountQueueNode* node);
	bool Search(char* name); //search
	bool Search_user(char* name);	//search and print
	bool Delete_Account(char* name, char* id);
	void Print_L(UserListNode* node);
	bool EMPTY();
	
};
