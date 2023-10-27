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
//vlad , frank, bigfoot, casper, gomez, morticia mom thread
// to compile  g++ hw7-pedroschmidt.cpp -std=c++11 -lpthread
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
		if(lineString == "C")  //r indicates the start of a critical section
      {
			pthread_mutex_lock(&balance); //where we aquire the balance
         
		} 
      else if(lineString == "B")  //w // end of the critical section where we write the account balance to a global storage 
      {
	cout << "Account balance after thread! " << id << " is $" << limit << endl; //AFTER EVERY NEW THREAD THIS WILL BE ITERATED 
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
	
	outFile.open("Morticia.in"); //mom thread 

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
		
	}

	cout << "Final balance: $"<< limit << endl;
	cout << "FIN! " << endl;
	
	
	return 0;
}

