#include "UserListNode.h"
#include <fstream>
using namespace std;

UserListNode::UserListNode()
{
	Name=new char;
	Age=0;
	AccNum=0;
	pNext=NULL;
	pHead=NULL;
	Head=NULL;
	Rear=NULL;
}

UserListNode::~UserListNode()
{

}

char* UserListNode::GetName()
{
	return this->Name;
}

int UserListNode::GetAge()
{
	return this->Age;
}

UserListNode* UserListNode::GetNext()
{
	return this->pNext;
}

AccountBSTNode* UserListNode::GetHead()
{
	return this->pHead;
}

AccountBSTNode* UserListNode::GetRear()
{
	return this->Rear;
}

void UserListNode::SetName(char* name)
{
	strcpy(this->Name,name);
}

void UserListNode::SetAge(int age)
{
	this->Age=age;
}

void UserListNode::SetNext(UserListNode* node)
{
	this->pNext=node;
}

void UserListNode::SetHead(AccountBSTNode* head)
{
	this->pHead=head;
}
void UserListNode::SetRear(AccountBSTNode* rear)
{
	this->Rear=rear;
}

void UserListNode::SetAccNum(int num)
{
	this->AccNum=num;
}

AccountBSTNode* UserListNode::InsertAccount(UserListNode* Root, AccountBSTNode* node)
{	//case1. User is not exsist.
	AccNum++;
	Root->SetAccNum(1);
	return node;
}

AccountBSTNode* UserListNode::Insert_v2(UserListNode* Root, AccountBSTNode* node)
{
	ofstream flog("log.txt",ios::app);

	AccNum++;

	//case2. User already exsist.
	AccNum++;
	UserListNode* currNode=Root;

	/*Find this id's user name*/
	while(currNode!=NULL)
	{
		if(!strcasecmp(currNode->GetName(),node->GetName()))
			break;
		else
			currNode=currNode->GetNext();
	}
	
	/*AccNum < 3*/
	if((currNode->GetAccNum())==1)
	{
		AccountBSTNode* pNode=new AccountBSTNode;
		pHead=Rear=currNode->GetHead();
		currNode->SetAccNum(2);

		Rear->SetNext(pNode);
		currNode->SetRear(pNode);
		Rear=pNode;

		pNode->SetName(node->GetName());
		pNode->SetId(node->GetId());

		return pNode;
	}

	else if((currNode->GetAccNum())==2)
	{
		while(currNode!=NULL)
		{
			if(!strcmp(currNode->GetName(),node->GetName()))
			{
				AccountBSTNode* pNode=new AccountBSTNode;
				pHead=Rear=currNode->GetHead();
				currNode->SetAccNum(3);

				Rear->GetNext()->SetNext(pNode);

				currNode->GetNext()->SetRear(pNode);
				Rear=pNode;

				pNode->SetName(node->GetName());
				pNode->SetId(node->GetId());

				return pNode;
			}
			else
				currNode=currNode->GetNext();
		}
	}
	else
	{
		flog<<"=========ERROR=========="<<endl;
		flog<<"user id already 3"<<endl;
		flog<<"======================"<<endl;
	}
	return 0;
}

void UserListNode::Print_Accounts()
{
	ofstream flog("log.txt",ios::app);

	AccountBSTNode* currNode=pHead;
	
	//if account is not exsist, print error code
	if(pHead==nullptr)
	{
		flog<<"=========ERROR========"<<endl;
		flog<<"400"<<endl;
		flog<<"======================"<<endl;
		return;
	}
	
	//account is exsist.
	else
	{
		AccountBSTNode* current=pHead;

		while(current!=NULL)
		{
			flog<<current->GetId()<<endl;
			current=current->GetNext();
		}
	}

}

void UserListNode::Delete_Account(UserListNode* pNode, char* id)
{
	AccountBSTNode* currNode = pNode->GetHead();

	//case1) Delete node is Head
	if(!strcasecmp(currNode->GetId(),id))
	{
		pNode->SetHead(currNode->GetNext());
		delete currNode;
		return;
	}

	//case2) Delete node is not Head
	while(currNode->GetNext()!=NULL)
	{
		if(!strcasecmp(currNode->GetNext()->GetId(),id))
		{
			currNode->SetNext(currNode->GetNext()->GetNext());
			delete currNode->GetNext();
			break;
		}
		else
			currNode=currNode->GetNext();
	}
}
