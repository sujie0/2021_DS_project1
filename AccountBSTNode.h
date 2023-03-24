#pragma once
#include <cstring>
#pragma warning(disable: 4996)
class AccountBSTNode
{
private:
	char* Name;
	char* Id;

	AccountBSTNode* pLeft;
	AccountBSTNode* pRight;
	AccountBSTNode* pNext;
	AccountBSTNode* pParent;
	
public:
	AccountBSTNode();
	~AccountBSTNode();

	char* GetName();
	char* GetId();
	AccountBSTNode* GetLeft();
	AccountBSTNode* GetRight();
	AccountBSTNode* GetNext();
	AccountBSTNode* GetParent();


	void SetName(char* name);
	void SetId(char* id);
	void SetNext(AccountBSTNode* node);
	void SetLeft(AccountBSTNode* node);
	void SetRight(AccountBSTNode* node);
	void SetParent(AccountBSTNode* node);
};
