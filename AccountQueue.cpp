#include "AccountQueue.h"
#include <fstream>
using namespace std;



AccountQueue::AccountQueue()
{//initialization
	queue_size=0;
	Front=NULL;
	Rear=NULL;
}

AccountQueue::~AccountQueue()
{	//delete queue
	AccountQueueNode* deleteNode=Front;
	while(deleteNode!=nullptr)
	{
		Front=deleteNode->GetNext();
		delete deleteNode;
		deleteNode=Front;
	}
	
	delete Front;
}

AccountQueueNode* AccountQueue::POP()
{
	AccountQueueNode* popNode=Front;	//pop queue's first node
	Front=Front->GetNext();
	queue_size--;

	return popNode;
	delete popNode;	//delete pop Node
}

bool AccountQueue::PUSH(AccountQueueNode* node)
{
	if(EMPTY()) //if queue is empty
	{ //insert to the first node of Queue
		Front=Rear=new AccountQueueNode;
		Front->SetName(node->GetName());
		Front->SetAge(node->GetAge());
		Front->SetId(node->GetId());

		queue_size++;
	}
	else //if queue is not empty
	{ //insert to the node of Queue
		AccountQueueNode* pNode=new AccountQueueNode;
		Rear->SetNext(pNode);
		Rear=pNode;
		pNode->SetName(node->GetName());
		pNode->SetAge(node->GetAge());
		pNode->SetId(node->GetId());

		queue_size++;
	}
	return true;
}

bool AccountQueue::EMPTY()
{ //if Queue is empty, return true. else, return false
	if(Front==NULL)
		return true;
	else
		return false;
}

int AccountQueue::SIZE()
{
	return queue_size;
}

void AccountQueue::PRINT()
{
	ofstream flog("log.txt",ios::app);

	if(EMPTY())
	{ //if Queue is empty, print error code
		flog<<"==========ERROR========="<<endl;
		flog<<"100"<<endl;
		flog<<"========================"<<endl;
		return;
	}
	else
	{ //print all Queue nodes
		AccountQueueNode*current=Front;
		flog<<"==========QLOAD=========="<<endl;
		while(current!=NULL)
		{
			flog<<current->GetName()<<"/"<<current->GetAge()<<"/"
				<<current->GetId()<<endl;
			current=current->GetNext();
		}
		flog<<"========================"<<endl<<endl;
	
	}
}
