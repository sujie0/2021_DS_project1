#pragma once
#include <cstring>
using namespace std;

class UserHeapNode
{
private:
	int NumUser;
	int AgeGroup;

public:
	UserHeapNode();
	~UserHeapNode();

	int GetNumUser();
	int GetAgeGroup();

	void SetNumUser(int number);
	void SetAgeGroup(int agegroup);
};
