#include "Manager.h"

bool already_data_in_the_queue=false;

Manager::Manager()
{
	ds_queue=new AccountQueue;
	ds_bst=new AccountBST;
	ds_heap=new UserHeap;
	ds_list=new UserList;
}

Manager::~Manager()
{
	delete ds_queue;
//	delete ds_bst;
	delete ds_heap;
	delete ds_list;
}

void Manager::run(const char* command)
{
	fin.open("command.txt");
	flog.open("log.txt",ios::app);
	if(!fin)
	{
		flog<<"File Open Error"<<endl;
	}

	char cmd[32];

	while(!fin.eof())
	{
		fin.getline(cmd,32);
		char* tmp=strtok(cmd, " ");
		if(!strcmp(cmd,"QLOAD"))
		{
			if(QLOAD())
			{
				flog<<"=================="<<endl<<endl;
			}
			else
			{
				PrintErrorCode(100);
			}
		}

		else if(!strcmp(cmd, "QPOP"))
		{
			tmp=strtok(NULL," ");
			int num=atoi(tmp);
			
			//if queue is empty, print error code
			if(ds_queue->EMPTY())
				PrintErrorCode(300);
			
			//if pop size if bigger than queue size, print error code
			else if(ds_queue->SIZE()>=num)
			{
				flog<<"=======QPOP======="<<endl;
				bool success=false;

				for(int i=0;i<num;i++)
				{
					if(QPOP(num))
						success=true;
					else
						success=false;
				}
				if(success) {}
			
				else	//if the imformation in the data is incorrect
					flog<<"301"<<endl;
				flog<<"Success"<<endl;
				flog<<"=================="<<endl<<endl;
			}
			else
				PrintErrorCode(300);
		}

		else if(!strcmp(tmp,"ADD"))
		{
			tmp=strtok(NULL," ");
			if(tmp==NULL)
				PrintErrorCode(200);
			else
			{
				char* name=tmp;
				tmp=strtok(NULL," ");
				if(tmp==NULL)
					PrintErrorCode(200);
				else
				{
					int age=atoi(tmp);

					tmp=strtok(NULL," ");
					if(tmp==NULL)
						PrintErrorCode(200);
					else
					{
						char* id=tmp;
						ADD(name,age,id);
					}
				}
			}
		}

		else if(!strcmp(tmp,"PRINT"))
		{
			tmp=strtok(NULL," ");
			if(tmp==NULL) //command not enugh
				PrintErrorCode(500);
			else
			{
				if(!strcmp(tmp,"L"))
				{
					if(ds_list->EMPTY())
						PrintErrorCode(500);
					else
						PRINT(tmp);
				}
				else if(!strcmp(tmp,"B"))
				{
					tmp=strtok(NULL," ");
					if(tmp==NULL)//command is not enough
						PrintErrorCode(500);
					else
					{
						if(ds_bst->EMPTY())
							PrintErrorCode(500);
						else
						{
							if(!strcmp(tmp,"LEVEL"))
							{
								PRINT(tmp);
							}
							else if(!strcmp(tmp,"PRE"))
							{
								PRINT(tmp);
							}
							else if(!strcmp(tmp,"IN"))
							{
								PRINT(tmp);
							}
							else if(!strcmp(tmp,"POST"))
							{
								PRINT(tmp);
							}
							else
							{
								PrintErrorCode(800);
							}
						}
					}
				}
				else if(!strcmp(tmp,"H"))
				{
					if(ds_heap->EMPTY())
						PrintErrorCode(500);
					else
						PRINT(tmp);
				}
				else
					PrintErrorCode(800);
			}
		}

		else if(!strcmp(tmp,"SEARCH"))
		{
			tmp=strtok(NULL," ");
			
			//command is not enough
			if(tmp==NULL)
				PrintErrorCode(400);
			else
			{
				if(!strcmp(tmp,"id"))
				{
					tmp=strtok(NULL," ");

					//command is not enough
					if(tmp==NULL)
						PrintErrorCode(400);
					else
					{
						if(SEARCH_id(tmp))
						{
						}
						else
						{
							PrintErrorCode(400);
						}
					}
				}

				else if(!strcmp(tmp,"user"))
				{
					tmp=strtok(NULL," ");

					//command is not enough
					if(tmp==NULL)
						PrintErrorCode(400);
					else
					{
						if(SEARCH_user(tmp))
						{
						}
						else
						{
							PrintErrorCode(400);
						}
					}
				}
				else
				{
					PrintErrorCode(400);
				}
			}
		}

		else if(!strcmp(tmp,"DELETE"))
		{
			tmp=strtok(NULL," ");

			//command is not enough
			if(tmp==NULL)
				PrintErrorCode(600);
			else
			{
				if(DELETE(tmp))
				{
					PrintSuccess("DELETE");
				}
				else
				{
					PrintErrorCode(600);
				}
			}
		}

		else if(!strcmp(tmp,"HLOAD"))
		{
			if(HLOAD())
			{
				PrintSuccess("HLOAD");
			}
			else
			{
				PrintErrorCode(700);
			}
		}

		else if(!strcmp(tmp, "EXIT"))
		{
			PrintSuccess("EXIT");
			flog.close();
			break;
		}
		else
		{	//Wrong command
			PrintErrorCode(800);
		}
	}

	fin.close();
}

bool Manager::QLOAD()
{

	/*if the queue already has data, print error code*/
	if(already_data_in_the_queue)
		return false;

	bool isEmpty;
	ifstream read;

	isEmpty=read.peek()==EOF;
	read.open("data.txt");

	if(read.good())	//read successful of data.txt
	{
		already_data_in_the_queue=true;

		char line[200];

		flog<<"=========QLOAD======="<<endl;

		while(read.getline(line, sizeof(line)))
		{
			if(line==NULL)	//if File is empty, print error code
				PrintErrorCode(100);
			else
			{
				AccountQueueNode* pNode=new AccountQueueNode;

				char* name=strtok(line," ");
				if(name==NULL)	//in the case of insufficient name  information in data.txt
					flog<<"100"<<endl;
				else
				{
					pNode->SetName(name);	//Set new Node's name
	
					char* Age=strtok(NULL," ");
					if(Age==NULL)	//in the case of insufficient age information in data.txt
						flog<<"100"<<endl;
					else
					{
						int age=atoi(Age);
						pNode->SetAge(age);	//Set new Node's age

						char* id=strtok(NULL," ");
						if(id==NULL)	//in the case of insufficient id information in data.txt
							flog<<"100"<<endl;
						else
						{
							pNode->SetId(id);	//Set nes Node's id
							ds_queue->PUSH(pNode);	//push node in queue
							flog<<name<<"/"<<Age<<"/"<<id<<endl;	//if information in data.txt is correct, print information.
						}
					}
				}
			}
		}
		return true;
	} //read failed of data.txt
	else
		return false;
}

bool Manager::ADD(char*name, int age, char*id)
{
	AccountQueueNode* pNode=new AccountQueueNode;
	/*Set new Node's information*/
	pNode->SetName(name);
	pNode->SetAge(age);
	pNode->SetId(id);

	ds_queue->PUSH(pNode);	//push node in queue

	/*print add*/
	flog<<"==========ADD==========="<<endl;
	flog<<pNode->GetName()<<"/"<<pNode->GetAge()<<"/"<<pNode->GetId()<<endl;
	flog<<"========================"<<endl<<endl;
	return true;
}

bool Manager::QPOP(int num)
{
	//if list is empty
	if(ds_list->EMPTY())
	{
		ds_bst->Insert(ds_list->Insert(ds_queue->POP()));
		return true;
	}

	else
	{
		AccountQueueNode* pNode=ds_queue->POP();

		if(!ds_list->EMPTY())
		{	
			if(pNode!=NULL)
			{
				//if bst already have this id, print error code
				if(!ds_bst->Search_Id(pNode->GetId()))
					flog<<"301"<<endl;
				else
				{
					UserListNode* currNode = ds_list->GetRoot();
						
					while(currNode!=NULL)
					{
						if(!strcasecmp(currNode->GetName(),pNode->GetName()))
						{
							//if user alredy have 3 Account, print error code
							if(currNode->GetAccNum()>=3)
								return false;
					
							else
							{	//insert list and bst
								ds_bst->Insert(ds_list->Insert(pNode));
								return true;
							}
							break;
						}
						else
							currNode=currNode->GetNext();

					}
				
					//insert bst and list
					ds_bst->Insert(ds_list->Insert(pNode));
					return true;
				}
			}
			else
				return false;
		}
	}
}

bool Manager::SEARCH_id(char* id)
{	//search id
	if(ds_bst->Search_Id_and_print(id))
		return true;
	else
		return false;
}

bool Manager::SEARCH_user(char* user)
{	//search user
	if(ds_list->Search_user(user))
		return true;
	else
		return false;
}

bool Manager::PRINT(char* command)
{
	flog<<"==========PRINT=========="<<endl;

	if(!strcmp(command,"LEVEL"))
	{
		flog<<"BST LEVEL"<<endl;
		ds_bst->Print_LEVEL();
	}
	else if(!strcmp(command, "PRE"))
	{
		flog<<"BST PRE"<<endl;
		ds_bst->Print_PRE(ds_bst->GetRoot());
	}
	else if(!strcmp(command,"IN"))
	{
		flog<<"BST IN"<<endl;
		ds_bst->Print_IN(ds_bst->GetRoot());
	}
	else if(!strcmp(command, "POST"))
	{
		flog<<"BST POST"<<endl;
		ds_bst->Print_POST(ds_bst->GetRoot());
	}
	else if(!strcmp(command, "L"))
	{
		flog<<"LIST"<<endl;
		ds_list->Print_L(ds_list->GetRoot());
	}
	else if(!strcmp(command,"H"))
	{
		flog<<"Heap"<<endl;
		ds_heap->Print();
	}
	flog<<"=========================="<<endl<<endl;
	return true;
}

bool Manager::DELETE(char* id)
{
	/*if not exists delete Node in bst*/
	if(ds_bst->Search_Id(id))
		return false;

	/*delete Node exists in bst*/
	else
	{
		char* name=new char;
		strcpy(name, ds_bst->return_name(id));

		if(ds_bst->Delete(id))
		{
			ds_list->Delete_Account(name,id);
			return true;
		}
		else
			return false;
	}
}

bool Manager::HLOAD()
{	//if already exsits heap, delete heap
	if(ds_heap!=NULL)
		ds_heap->~UserHeap();

	UserListNode* Root=new UserListNode;

	//is bst is empty, print error code
	if(ds_bst->GetRoot()==NULL)
		return false;

	Root=ds_list->GetRoot();

	//Insert Node in heap
	while(Root!=NULL)
	{
		ds_heap->Insert(Root->GetAge());
		Root=Root->GetNext();
	}
	return true;
}

bool Manager::EXIT()
{
	ds_queue->~AccountQueue();
	ds_list->~UserList();
	ds_heap->~UserHeap();
	return true;
}

void Manager::PrintErrorCode(int num)
{
	flog<<"============ERROR=========="<<endl;
	flog<<num<<endl;
	flog<<"==========================="<<endl<<endl;
}

void Manager::PrintSuccess(string act)
{
	flog<<"============"<<act<<"========"<<endl;
	flog<<"Success"<<endl;
	flog<<"============================="<<endl<<endl;
}

