#include "UserList.h"
#include <cstring>
#include <fstream>
using namespace std;

UserList::UserList()
{
	Root=NULL;
	pNext=NULL;
}

UserList::~UserList()
{
	/*delete list*/
	UserListNode* target=Root;
	UserListNode* temp=target;
	while(target!=NULL)
	{
		temp=temp->GetNext();
		delete target;
		target=temp;
	}

	Root=NULL;
}

UserListNode* UserList::GetRoot()
{
   	return Root;
}

UserListNode* UserList::GetNext()
{
	return pNext;
}

void UserList::SetNext(UserListNode* node)
{
	this->pNext=node;
}

AccountBSTNode* UserList::Insert(AccountQueueNode* node)
{
	AccountBSTNode* BSTNode=new AccountBSTNode;
	BSTNode->SetId(node->GetId());
	BSTNode->SetName(node->GetName());

 	UserListNode* ListNode=new UserListNode;
	
	/*if there's  no Node in list*/
	if(!(Search(node->GetName())))
	{
		//case1. if list is empty
		if(Root==nullptr)
		{
			Root=pNext=new UserListNode;
			Root->SetName(node->GetName());
			Root->SetAge(node->GetAge());
			Root->InsertAccount(Root, BSTNode);
			Root->SetHead(BSTNode);
		}

		//case2. list is not empty
		else
		{
			pNext->SetNext(ListNode);
			pNext=ListNode;
			
			ListNode->SetName(node->GetName());
			ListNode->SetAge(node->GetAge());
			
			ListNode->InsertAccount(Root, BSTNode);
			ListNode->SetHead(BSTNode);
		}
	}
	
	/*if the Node is already in list*/
	else
	{	//Do not make list Node, just counting user id num
		ListNode->Insert_v2(Root,BSTNode);
	}
	return BSTNode;	
}

/*Search and no print*/
bool UserList::Search(char* name)
{
	UserListNode* currNode=Root;
	while(currNode!=NULL)
	{
		if(!strcasecmp(currNode->GetName(),name))
			return true;
		else
			currNode=currNode->GetNext();
	}
	return false;
}

/*Search and print*/
bool UserList::Search_user(char* name)
{
	ofstream flog("log.txt",ios::app);

	UserListNode* currNode=Root;
	while(currNode!=NULL)
	{
		if(!strcasecmp(currNode->GetName(),name))
		{
			flog<<"========SEARCH=========="<<endl;
			flog<<"User"<<endl;
			flog<<currNode->GetName()<<"/"
				<<currNode->GetAge()<<endl;
			currNode->Print_Accounts();
			flog<<"==========================="<<endl<<endl;
			return true;
		}
		else
			currNode=currNode->GetNext();
	}
	return false;
}

bool UserList::Delete_Account(char* name, char* id)
{
	UserListNode* currNode = Root;
	while(currNode!=NULL)
	{
		if(!strcasecmp(currNode->GetName(),name))
		{
			if(currNode->GetAccNum()==0)
			{
			}
			
			//user id number is not zero
			else
			{	//Reduce the number of accounts by one
				int num=currNode->GetAccNum();
				num--;
				currNode->SetAccNum(num);
				currNode->Delete_Account(currNode,id);

				/*if AccNum is 0, delete List Node*/
				if(num==0)
				{
					UserListNode* currNode = Root;
					if(!strcasecmp(currNode->GetName(),name))
					{
						Root=currNode->GetNext();
						delete currNode;
						return true;
					}
					while(currNode->GetNext()!=NULL)
					{
						if(!strcasecmp(currNode->GetNext()->GetName(),name))
						{
							UserListNode* deleteNode=currNode->GetNext();
							if(deleteNode->GetNext()!=NULL)
								currNode->SetNext(deleteNode->GetNext());
							else
								currNode->SetNext(NULL);
							delete deleteNode;
							return true;
						}
						currNode=currNode->GetNext();
					}
				}
			}
			return true;
		}
		else
			currNode=currNode->GetNext();
	}
   	return false;
}

void UserList::Print_L(UserListNode* node)
{	//print list
	ofstream flog("log.txt",ios::app);

    	UserListNode* currNode=node;
	while(currNode!=NULL)
	{
		flog<<currNode->GetName()<<"/"
			<<currNode->GetAge()<<"/"
			<<currNode->GetAccNum()<<endl;
		currNode=currNode->GetNext();
	}
}

bool UserList::EMPTY()
{
	if(Root==NULL)
		return true;
	else
		return false;
}
