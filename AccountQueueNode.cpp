#include "AccountQueueNode.h"

AccountQueueNode::AccountQueueNode()
{//dynamic memory allocation, initialization
	User_Name=new char;
	User_age=0;
	User_Id=new char;
	pNext=NULL;
}

AccountQueueNode::~AccountQueueNode()
{//delete queue

}

char* AccountQueueNode::GetName()
{
	return User_Name;
}

int AccountQueueNode::GetAge()
{
	return User_age;
}

char* AccountQueueNode::GetId()
{
	return User_Id;
}
AccountQueueNode* AccountQueueNode::GetNext()
{
	return pNext;
}
void AccountQueueNode::SetName(char* name)
{
	strcpy(User_Name,name);
}

void AccountQueueNode::SetAge(int age)
{
	this->User_age=age;
}

void AccountQueueNode::SetId(char* id)
{
	strcpy(User_Id,id);
}

void AccountQueueNode::SetNext(AccountQueueNode* node)
{
	this->pNext=node;
}
