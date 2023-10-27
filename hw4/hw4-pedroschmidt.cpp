#include <stdlib.h>
#include <string>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <mutex>
#include <condition_variable>

// Pedro Schmidt
// CSci 451 
// to compile g++ hw4-pedroschmidt.cpp -std=c++11 -pthread 
// to compile g++ hw4-pedroschmidt.cpp -std=c++11 -lpthread 
using namespace std;

ofstream outFile;
condition_variable c;
mutex m;
int value; 

struct dataStruct 
{
	string fileName;
	int id; // identifier 
};


void *readFile(void* passedStruct) 
{
	
	unique_lock<mutex>lock(m);
	struct dataStruct *threadData;
	threadData = (struct dataStruct *) passedStruct;
	
	if(threadData->id == 0) 
   {
		ifstream selectedFile;
		string lineChar;
	
		
		string fileName = threadData -> fileName;
		
		selectedFile.open(fileName);
		
		while(1) 
      {
		    selectedFile >> skipws >> lineChar;
		    
		    value = stoi(lineChar);
		    if(selectedFile.eof()) 
          {
		    	value = -2;
		    	break;
		    }
		    c.notify_all();
		    c.wait(lock);
		}
		c.notify_all();
		
	}
	
	if(value == -1) 
   {
		c.wait(lock);
	}
	
	if(threadData->id == 1) 
   {
		while(1) 
      {
			if(value == -2)
          {
				break;
			}
			int current = value;
			if(current % 2 == 0) 
         {
				outFile << current << "\n";
				outFile << current << "\n";
			} else 
         {
				outFile << current << "\n";
			}
			c.notify_all();
			c.wait(lock);
		
		}
	}
    
}

int main() 
{
	
	value = -1;
	
	pthread_t p1;
	pthread_t p2;

	outFile.open("hw4.out");
	
	dataStruct file1 = {"hw4.in", 0};
	dataStruct file2 = {"", 1};
	
	pthread_create(&p1, NULL, readFile, (void*)&file1);
	
	pthread_create(&p2, NULL, readFile, (void*)&file2);
	
	
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_exit;
	
	outFile.close();
	
	cout << "Done,Faneto!" << endl;
	
	
	return 0;
}

