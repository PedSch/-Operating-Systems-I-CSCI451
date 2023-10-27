#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <mutex>

using namespace std;


// Pedro Schmidt
// CSci 451
//Enhanced Second Chance - Clock" alorithm (ESC-C)
// to compile  g++ hw8-pedroschmidt.cpp -std=c++11 -lpthread

int temp;
int limit;
int fin;
ofstream outFile;
pthread_mutex_t balance = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t completed = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t nodeLock = PTHREAD_MUTEX_INITIALIZER;

struct dataStruct 
{
	string fileName;
	int identifier;
};

struct pageNode 
{
	int id;
	int rbit;
	int mbit;
	int counter;
	struct pageNode *next;
};

pageNode node1  = {-1,0,0,0,NULL};
pageNode node2  = {-1,0,0,0,NULL};
pageNode node3  = {-1,0,0,0,NULL};
pageNode node4  = {-1,0,0,0,NULL};
pageNode node5  = {-1,0,0,0,NULL};
pageNode node6  = {-1,0,0,0,NULL};
pageNode *head = &node1;

void *readFile(void* passedStruct) 
{
	string lineCharacter;
	ifstream openedFile;
   pageNode *current = head;
	struct dataStruct *threadData;
	threadData = (struct dataStruct *) passedStruct;
	
	string fileName = threadData->fileName;
	openedFile.open(fileName);
	
	int threadID = threadData->identifier;

	while(1)
	{
		pthread_mutex_lock(&nodeLock);
		if(current->id == -1)
		{
			current->id = threadID;
			current->rbit = 1;
			pthread_mutex_unlock(&nodeLock);			
			break;
		}
		else 
      {
			current = current->next;
		}
		pthread_mutex_unlock(&nodeLock);
	}	
	

	while(1) 
   {            
		    openedFile >> skipws >> lineCharacter;
		    if(openedFile.eof())
           {
		    	pthread_mutex_lock(&completed);
				fin++;
			 	pthread_mutex_unlock(&completed);
		    	break;
		    }
        if(lineCharacter == "C")  //r indicates the start of a critical section

        {
            pthread_mutex_lock(&balance); //where we aquire the balance

        }  
        else if(lineCharacter == "B") //w // end of the critical section where we write the account balance to a global storage 
    
        {
            cout << "Thread " << threadID << " balance: $" << limit << endl;
	    	pthread_mutex_lock(&nodeLock);
			current->counter = current->counter + 1;	
			
			if(current->counter == 4)
			{
				cout<< "Page fault in thread: " << threadID << endl;
				current->counter = 0;
				
			
				current = head;		
				bool foundNode = false;
				while(!foundNode)
            { 
					if(current->rbit == 0 && current -> mbit == 0 )
               {
							cout<< "Replaced with page: " << current -> id << " R: " << current -> rbit << " M: " << current -> mbit << endl;
							current->id = threadID;
							foundNode = true;
						}
					else
               {
						current = current->next;
						if(current == head)
							{
								break;
							}
						}
					}
					while(!foundNode)
               { 
					if(current -> rbit == 1 && current -> mbit == 0 )
               {
							cout<< "Replaced with page: " << current -> id << " R: " << current -> rbit << " M: " << current -> mbit << endl;
							current -> id = threadID;
							foundNode = true;
						}
					else
               {
						current = current->next;
						if(current == head)
							{
								break;
							}
						}
					}
					while(!foundNode)
               { 
					if(current -> rbit == 0 && current->mbit == 1 )
               {
							cout<< "Replaced with page: " << current -> id << " R: " << current -> rbit << " M: " << current -> mbit << endl;
							current->id = threadID;
							foundNode = true;
						}
					else
               {
						current = current -> next;
						if(current == head)
							{
								break;
							}
						}
					}
					while(!foundNode)
               { 
					if(current->rbit == 1 && current -> mbit == 1 )
               {
							cout<< "Replaced with page: " << current -> id << " R: " << current -> rbit << " M: " << current -> mbit << endl;
							current->id = threadID;
							foundNode = true;
						}
					}
			}
			
				if(limit < 0)
            {
					current->rbit = 1;
					current->mbit = 1;
				}
				
				if(limit > 0)
            {
						current->rbit = 1;
				}
			
			
			pthread_mutex_unlock(&nodeLock);

            pthread_mutex_unlock(&balance);
	   		sleep(.5);
		}    
        else
        {
            temp = stoi(lineCharacter);
            limit += temp;
        }
    }
    
}

int main() 
{
	
	limit = 0;
	fin = 0;
   
   outFile.open("Morticia.in"); //mom thread 

	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = &node1;
	
	pageNode *head = &node1;
	pageNode *current = head;
	
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
    pthread_t p4;
    pthread_t p5;
	
//dataStruct id1 = {"Morticia.in", 1}; //mom THREAD 	
	dataStruct id1 = {"Vlad.in", 1}; //2nd THREAD 
	dataStruct id2 = {"Frank.in", 2};  // 3rd THREAD 
	dataStruct id3 = {"Bigfoot.in", 3};  // 4th THREAD 
   dataStruct id4 = {"Gomez.in", 4};//th THREAD 
   dataStruct id5 = {"Casper.in", 5}; //5th THREAD     
		
	pthread_create(&p1, NULL, readFile, (void*)&id1);
	pthread_detach(p1);
	pthread_create(&p2, NULL, readFile, (void*)&id2);
	pthread_detach(p2);
	pthread_create(&p3, NULL, readFile, (void*)&id3);
	pthread_detach(p3);
    pthread_create(&p4, NULL, readFile, (void*)&id4);
	pthread_detach(p4);
    pthread_create(&p5, NULL, readFile, (void*)&id5);
	pthread_detach(p5);
    

	while(fin != 5) 
   {
		sleep(.3);
		pthread_mutex_lock(&nodeLock);
		node1.rbit = 0;
		node2.rbit = 0;
		node3.rbit = 0;
		node4.rbit = 0;
		node5.rbit = 0;
		node6.rbit = 0;
		pthread_mutex_unlock(&nodeLock);
	}
   
	outFile.close();
	cout << "FIN! " << endl;
	
	
	return 0;
}

