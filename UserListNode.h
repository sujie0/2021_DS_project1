#pragma once
#include <cstring>
#include "AccountBSTNode.h"
#include <iostream>
#include <fstream>
#pragma warning(disable: 4996)

class UserListNode
{
private:
	char* Name;
	int Age;
	int AccNum;
	UserListNode* pNext;
	AccountBSTNode* pHead;
	AccountBSTNode* Rear; //sujie
	UserListNode* Head; //sujie

public:
	UserListNode();
	~UserListNode();

	char* GetName();
	int GetAge();
	int GetAccNum() {return AccNum;}
	UserListNode* GetNext();
	AccountBSTNode* GetHead(); //sujie
	AccountBSTNode* GetRear(); //sujie
	
	void SetName(char* name);
	void SetAge(int age);
	void SetNext(UserListNode* node);
	void SetAccNum(int num); //sujie
	void SetHead(AccountBSTNode* head); //sujie
	void SetRear(AccountBSTNode* rear); //sujie
	
	AccountBSTNode* InsertAccount(UserListNode* Root, AccountBSTNode* node);
	AccountBSTNode* Insert_v2(UserListNode* Root, AccountBSTNode* node); //sujie
	void Print_Accounts();
	void Delete_Account(UserListNode* pNode, char* id);
};
