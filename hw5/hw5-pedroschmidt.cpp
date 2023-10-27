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
// to compile  g++ hw5-pedroschmidt.cpp -std=c++11 -lpthread
mutex m;
int limit; //
int fin;  // 
ofstream outFile;
pthread_mutex_t balance = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t completed = PTHREAD_MUTEX_INITIALIZER;


struct dataStruct
 {
	string fileName;
	int identifier;
};


void *readFile(void* passedStruct)
 {
	ifstream selectedFile;
	struct dataStruct *threadData;
	threadData = (struct dataStruct *) passedStruct;
	
	int id = threadData->identifier;
	string fileName = threadData -> fileName;
	selectedFile.open(fileName);
	string lineString;
	
	
	while(1)
    {
		selectedFile >> skipws >> lineString;
		if(selectedFile.eof()) 
      {
			pthread_mutex_lock(&completed);
			fin++;
			pthread_mutex_unlock(&completed);
			break;
		}
		//cout << lineString << endl;
		if(lineString == "C")  //r
      {
			pthread_mutex_lock(&balance);
         
		} 
      else if(lineString == "B")  //w
      {
	cout << "balance after thread! " << id << " is $" << limit << endl; //AFTER EVERY NEW THREAD THIS WILL BE ITERATED 
	pthread_mutex_unlock(&balance);
	sleep(.3);
      }
     else 
      {
	limit += stoi(lineString);
	}
	}
    
}

int main() 
{
	
	limit = 0;
	fin = 0;
	
	outFile.open("hw5.out");

	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
		
	dataStruct id1 = {"hw5-1.in", 1}; //FIRST THREAD 
	dataStruct id2 = {"hw5-2.in", 2};  // 2ND THREAD 
	dataStruct id3 = {"hw5-3.in", 3};  // 3RD THREAD 
		
	pthread_create(&p1, NULL, readFile, (void*)&id1);
	pthread_detach(p1);
	pthread_create(&p2, NULL, readFile, (void*)&id2);
	pthread_detach(p2);
	pthread_create(&p3, NULL, readFile, (void*)&id3);
	pthread_detach(p3);

	while(fin != 3)   
	{
		
	}

	outFile.close();
	cout << "Final balance: $"<< limit << endl;
	cout << "FIN! " << endl;
	
	
	return 0;
}

