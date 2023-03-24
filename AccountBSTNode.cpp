#include "AccountBSTNode.h"

AccountBSTNode::AccountBSTNode()
{
	Name=new char;
	Id=new char;
	pNext=NULL;
	pRight=NULL;
	pLeft=NULL;
	pParent=NULL;
}

AccountBSTNode::~AccountBSTNode()
{

}

char* AccountBSTNode::GetName()
{
	return Name;
}

char* AccountBSTNode::GetId()
{
	return Id;
}

AccountBSTNode* AccountBSTNode::GetLeft()
{
	return pLeft;
}

AccountBSTNode* AccountBSTNode::GetRight()
{
	return pRight;
}

AccountBSTNode* AccountBSTNode::GetNext()
{
	return pNext;
}

AccountBSTNode* AccountBSTNode::GetParent()
{
	return pParent;
}

void AccountBSTNode::SetName(char* name)
{
	strcpy(this->Name,name);
}

void AccountBSTNode::SetId(char* disease)
{
	strcpy(this->Id,disease);
}

void AccountBSTNode::SetLeft(AccountBSTNode* node)
{
	this->pLeft=node;
}

void AccountBSTNode::SetRight(AccountBSTNode* node)
{
	this->pRight=node;
}
void AccountBSTNode::SetNext(AccountBSTNode* node)
{
	this->pNext=node;
}

void AccountBSTNode::SetParent(AccountBSTNode* node)
{
	this->pParent=node;
}
