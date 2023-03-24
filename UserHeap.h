#pragma once
#include "UserHeapNode.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class UserHeap
{
private:
	vector<UserHeapNode*> Heap;

public:
	UserHeap();
	~UserHeap();
	
	void lastswap(UserHeapNode* pNode);
	void swap(int i,int j);
	bool Insert(int agegroup);
	void Print();
	bool EMPTY();
};
