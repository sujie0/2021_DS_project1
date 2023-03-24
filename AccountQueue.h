#pragma once
#include "AccountQueueNode.h"
#include <fstream>
#include <iostream>

using namespace std;

class AccountQueue
{
private:
	int queue_size;
	AccountQueueNode* Front;	//queue'first
	AccountQueueNode* Rear;		//queue'last

public:
	AccountQueue();
	~AccountQueue();

	bool PUSH(AccountQueueNode* node);
	AccountQueueNode* POP();
	bool EMPTY();
	int SIZE();
	void PRINT();
};
