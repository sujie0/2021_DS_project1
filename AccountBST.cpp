#include "AccountBST.h"
#include <cstring>
#include <fstream>


AccountBST::AccountBST()
{ //initialization
	Root=NULL;
}

AccountBST::~AccountBST()
{ //Delete BST

}

AccountBSTNode* AccountBST::GetRoot()
{
	return Root;
}

bool AccountBST::Insert(AccountBSTNode* node)
{
	ofstream flog("log.txt",ios::app);

	AccountBSTNode* pNew=new AccountBSTNode;
	AccountBSTNode* tmpRoot=NULL;
	
	/*set new node's information*/
	pNew->SetId(node->GetId());
	pNew->SetName(node->GetName());
	
	//if new node's id is not already exists, insert in the BST
	if(Search_Id(node->GetId()))
	{
		if(Root==NULL)
		{
			Root=pNew;
			return false;
		}
		else
		{
			AccountBSTNode* ptr=Root;

			while(ptr!=NULL)
			{ //Compare without distinction between upper and lower case letters
				int num=strcasecmp(pNew->GetId(),ptr->GetId());
				
				//Set left Node or Right Node
				if(num<0)
				{	
					tmpRoot=ptr;
					ptr=ptr->GetLeft();
				}
				else
				{
					tmpRoot=ptr;
					ptr=ptr->GetRight();
				}
			}
			int num=strcasecmp(pNew->GetId(),tmpRoot->GetId());
		
			//Set left Node or Right Node
			if(num<0)
			{
				pNew->SetParent(tmpRoot);
				tmpRoot->SetLeft(pNew);
			}
			else
			{
				pNew->SetParent(tmpRoot);
				tmpRoot->SetRight(pNew);
			}

			return true;
		}
	}
	else	//If this id is already exists, do not input data in BST
	{
		flog<<"301"<<endl;
		return false;
	}

}

//If id is exists in BST, return false
bool AccountBST::Search_Id(char* id)
{
	AccountBSTNode* ptr=Root;
	AccountBSTNode* tmpRoot=nullptr;

	while(ptr!=nullptr)
	{ //Compare without distinction between upper and lower case letters
		if(!strcasecmp(ptr->GetId(),id))
		{
			return false;
		}
		else if(strcasecmp(ptr->GetId(),id)>0)
			ptr=ptr->GetLeft();
		else
			ptr=ptr->GetRight();
	}
	return true;
}

//Search id and print it
bool AccountBST::Search_Id_and_print(char* id) //Search id and print
{
	ofstream flog("log.txt",ios::app);

	AccountBSTNode* ptr=Root;
	AccountBSTNode* tmpRoot=nullptr;
	
	while(ptr!=nullptr)
	{ //Compare without distinction between upper and lower case letters
		if(!strcasecmp(ptr->GetId(),id))
		{	//print Search id
			flog<<"=========SEARCH========="<<endl;
			flog<<"ID"<<endl;
			flog<<ptr->GetId()<<"/"<<ptr->GetName()<<endl;
			flog<<"========================"<<endl<<endl;
		
			return true;
		}
		else if(strcasecmp(ptr->GetId(),id)>0)
			ptr=ptr->GetLeft();
		else
			ptr=ptr->GetRight();
	}
	
	return false;	
}

//Find right subtree's minimum Node
AccountBSTNode* AccountBST::SearchMinNode(AccountBSTNode* pNode)
{
	if(pNode==NULL)
		return NULL;
	if(pNode->GetLeft()==nullptr)
		return pNode;
	else
		return SearchMinNode(pNode->GetLeft());
}

bool AccountBST::Delete(char* id)
{
	AccountBSTNode* currNode=Root;
	int num=strcasecmp(currNode->GetId(),id);

	if(currNode==nullptr) return false;

	/*Find delete Node*/
	while(currNode!=nullptr)
	{
		num=strcasecmp(currNode->GetId(),id);
		if(num==0)	//Find delete Node
			break;
		else if(num>0)	//currNode is bigger than delete Node
			currNode=currNode->GetLeft();
		else if(num<0)	//currNode if smaller than delete Node
			currNode=currNode->GetRight();
	}
	
	/*case1. No child*/
	if(currNode->GetRight()==nullptr&&currNode->GetLeft()==nullptr)
	{
		//case 1-1. delete Node is Root Node
		if(currNode==Root)
		{
			delete currNode;
			Root=NULL;
			return true;
		}
		//case 1-2. delete Node is not Root Node
		else
		{
			if(currNode==currNode->GetParent()->GetLeft())
				currNode->GetParent()->SetLeft(NULL);
			else if(currNode==currNode->GetParent()->GetRight())
				currNode->GetParent()->SetRight(NULL);

			delete currNode;
			return true;
		}
	}

	/*case2. Have only left child*/
	else if(currNode->GetRight()==nullptr)
	{
		//case 2-1. delete Node is Root Node
		if(currNode==Root)
		{
			Root=currNode->GetLeft();
			currNode->SetParent(NULL);
		}
		//case 2-2. delete Node is not Root Node
		else if(currNode==currNode->GetParent()->GetLeft())
			currNode->GetParent()->SetLeft(currNode->GetLeft());
		else if(currNode==currNode->GetParent()->GetRight())
			currNode->GetParent()->SetRight(currNode->GetLeft());

		currNode->GetLeft()->SetParent(currNode->GetParent());
		
		delete currNode;
		return true;
	}

	/*case3. Have only right child*/
	else if(currNode->GetLeft()==nullptr)
	{
		//case 3-1. delete Node is Root Node
		if(currNode==Root)
		{
			currNode->SetRight(Root);
			currNode->GetRight()->SetParent(NULL);
		}

		//case 3-2. delete Nods is not Root Node
		else if(currNode==currNode->GetParent()->GetLeft())
			currNode->GetParent()->SetLeft(currNode->GetRight());
		else if(currNode==currNode->GetParent()->GetRight())
			currNode->GetParent()->SetRight(currNode->GetRight());

		currNode->GetRight()->SetParent(currNode->GetParent());

		delete currNode;
		return true;
	}

	/*case4. Have two child*/
	else
	{
		AccountBSTNode* MinNode=new AccountBSTNode;

		//case 4-1. Min Node is right child
		if(currNode->GetRight()->GetLeft()==nullptr)
		{
			MinNode=currNode->GetRight();
			currNode->GetLeft()->SetParent(MinNode);
			MinNode->SetLeft(currNode->GetLeft());

			//case 4-1-1. delete Node is not Root Node
			if(currNode!=Root)
			{
				if(currNode==currNode->GetParent()->GetLeft())
					currNode->GetParent()->SetLeft(MinNode);
				else if(currNode==currNode->GetParent()->GetRight())
					currNode->GetParent()->SetRight(MinNode);

				MinNode->SetParent(currNode->GetParent());
			}

			//case 4-1-2. delete Node is Root Node
			if(currNode==Root)
			{
				Root->SetLeft(NULL);
				Root->SetRight(NULL);
				MinNode->SetParent(NULL);
				Root=MinNode;
			}

			delete currNode;
			return true;
		}

		//case 4-2. MinNode is left child
		else
		{
			AccountBSTNode* MinNode=SearchMinNode(currNode->GetRight());
			//case 4-2-1. MinNode do not have child
			if(MinNode->GetRight()==nullptr)
				MinNode->GetParent()->SetLeft(NULL);

			//case 4-2-2. MinNode have Right child
			else
			{
				MinNode->GetParent()->SetLeft(MinNode->GetRight());
				MinNode->GetRight()->SetParent(MinNode->GetParent());
			}

			MinNode->SetLeft(currNode->GetLeft());
			MinNode->SetRight(currNode->GetRight());
			MinNode->GetLeft()->SetParent(MinNode);
			MinNode->GetRight()->SetParent(MinNode);

			//case 4-2-3. delete Node is Root Node
			if(currNode==Root)
				Root=MinNode;
			else if(currNode==currNode->GetParent()->GetRight())
			{
				currNode->GetParent()->SetRight(MinNode);
				MinNode->SetParent(currNode->GetParent());
			}
			else if(currNode==currNode->GetParent()->GetLeft())
			{
				currNode->GetParent()->SetLeft(MinNode);
				MinNode->SetParent(currNode->GetParent());
			}

			delete currNode;
			return true;
		}
	}

	return false;
}

void AccountBST::Print_PRE(AccountBSTNode* node)
{
	ofstream flog("log.txt",ios::app);

	if(node!=NULL)
	{
		flog<<node->GetId()<<"/"<<node->GetName()<<endl;
		Print_PRE(node->GetLeft());
		Print_PRE(node->GetRight());
	}
	else
		return;
}

void AccountBST::Print_IN(AccountBSTNode* node)
{
	ofstream flog("log.txt",ios::app);

	if(node!=NULL)
	{
		Print_IN(node->GetLeft());
		flog<<node->GetId()<<"/"<<node->GetName()<<endl;
		Print_IN(node->GetRight());
	}
	else
		return;
}

void AccountBST::Print_POST(AccountBSTNode* node)
{
	ofstream flog("log.txt",ios::app);

	if(node!=NULL)
	{
		Print_POST(node->GetLeft());
		Print_POST(node->GetRight());
		flog<<node->GetId()<<"/"<<node->GetName()<<endl;
	}
	else
		return;
}

void AccountBST::Print_LEVEL()
{
	ofstream flog("log.txt",ios::app);

	queue<AccountBSTNode*> Q;
	Q.push(Root);
	Q.push(NULL);
	while(!Q.empty())
	{ //Queue is not empty, print BST to level order
		AccountBSTNode* pNode=Q.front();
		Q.pop();

		if(pNode==NULL)
		{
			if(!Q.empty())
				Q.push(NULL);
		}
		else
		{
			flog<<pNode->GetId()<<"/"<<pNode->GetName()<<endl;
			if((pNode->GetLeft())!=NULL)
				Q.push(pNode->GetLeft());
			if((pNode->GetRight())!=NULL)
				Q.push(pNode->GetRight());
		}
	}
}

/*Find and return the name of the user with that id*/
char* AccountBST::return_name(char* id)
{
	AccountBSTNode* ptr=Root;
	while(ptr!=nullptr)
	{	/*Compare without distinction between upper and lower case letters*/
		if(!strcasecmp(ptr->GetId(),id))
			return ptr->GetName();
		else if(strcasecmp(ptr->GetId(),id)>0)
			ptr=ptr->GetLeft();
		else
			ptr=ptr->GetRight();
	}
	return NULL;
}

/*if BST is empty, return true*/
bool AccountBST::EMPTY()
{
	if(Root==NULL)
		return true;
	else
		return false;
}
