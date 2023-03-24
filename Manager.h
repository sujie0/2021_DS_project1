#pragma once
#include "AccountBST.h"
#include "AccountQueue.h"
#include "UserHeap.h"
#include "UserList.h"
#include <cstring>
#include <string>
#pragma warning(disable: 4996)
using namespace std;

class Manager
{
private:
	AccountQueue* ds_queue;
	AccountBST* ds_bst;
	UserHeap* ds_heap;
	UserList* ds_list;
	ifstream fin;
	ofstream flog;

public:
	Manager();
	~Manager();

	void run(const char* command);
	bool QLOAD();
	bool ADD(char* name, int age, char* id);
	bool QPOP(int num);
	bool SEARCH_id(char* id);
	bool SEARCH_user(char* user);
	bool PRINT(char* command);
	bool DELETE(char* id);
	bool HLOAD();
	bool EXIT();

	void PrintErrorCode(int num);
	void PrintSuccess(string act);
};
