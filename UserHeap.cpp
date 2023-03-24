#include "UserHeap.h"
#include <fstream>
using namespace std;

UserHeap::UserHeap()
{ //save any value at the front
	Heap.push_back(0);
}

UserHeap::~UserHeap()
{ //delete Heap
	Heap.clear();
	vector<UserHeapNode*>().swap(Heap);
}

void UserHeap::swap(int i,int j)
{
	UserHeapNode* temp=Heap[i];
	Heap[i]=Heap[j];
	Heap[j]=temp;
}

bool UserHeap::Insert(int agegroup)
{
    //HLOAD
    UserHeapNode* pNode=new UserHeapNode;
    int group=(agegroup/10)*10;

    int size=Heap.size();
    int usernum=1;
    int temp=0;
	
    //if Heap size==0, save any value at the front
    if(size==0)
    {
	    Heap.push_back(0);
    }
    size=Heap.size();

    //insert heap
    for(int i=1;i<size;i++)
    {
	    if(Heap.at(i)->GetAgeGroup()==group)
	    {
		    temp=i;
		    usernum=Heap.at(i)->GetNumUser();
		    usernum++;
	    }
    }

    //if this age group already exsist, resort
    if(usernum!=1)
    {
	    Heap.at(temp)->SetNumUser(usernum);
	    lastswap(Heap.at(temp));
	    return true;
    }
    else
    {
	    pNode->SetAgeGroup(group);
	    pNode->SetNumUser(usernum);
	    Heap.push_back(pNode);
	    return true;
    }
    return false;
}

void UserHeap::lastswap(UserHeapNode* pNode)
{ //sort the Heap
	int child=0;
	int size=Heap.size();

	for(int i=1;i<size;i++)
	{
		if(Heap.at(i)->GetAgeGroup()==pNode->GetAgeGroup())
			child=i;
	}

	int parent=child/2;

	while(child!=1&&Heap[child]->GetNumUser()>Heap[parent]->GetNumUser())
	{
		swap(child,parent);
		child=parent;
		parent=child/2;
	}
}

void UserHeap::Print()
{
    //PRINT H
    ofstream flog("log.txt",ios::app);

    int size=Heap.size();

    for(int i=1;i<size;i++)
    {
	    flog<<(Heap.at(i))->GetNumUser()<<"/"
		    <<(Heap.at(i))->GetAgeGroup()<<endl;
    }
}

bool UserHeap::EMPTY()
{
	int size=Heap.size();
	if(size==1||size==0)
		return true;
	else
		return false;
}
