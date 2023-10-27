#include <stdlib.h>
#include <string>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <mutex>
#include <condition_variable>

//Pedro Schmidt
//flag 
//to compile -std=c++11 g++ hw3-pedroschmidt.cpp -lpthread
using namespace std;


string s = "";
mutex m;
condition_variable c;

struct threadStruct 
{
   string fileName;
};

void *readFile(void* passedStruct) 
{
	system("wget -q http://undcemcs01.und.edu/~ronald.marsh/CLASS/CS451/hw3-data.txt"); // downloads file "-q" quiet turns off wget output

	ifstream selectedFile;
	string lineCharacter;
	
    struct threadStruct *threadData;
    threadData = (struct threadStruct *) passedStruct;
    string fileName = threadData -> fileName;
    
    selectedFile.open(fileName);
    
    unique_lock<mutex>lock(m);
    while(!selectedFile.eof()) 
    {
        
        selectedFile >> skipws >>lineCharacter;
        
        if(lineCharacter == "0")
        {
            c.notify_all();
            
            if(selectedFile.eof()) break;
            
            c.wait(lock);
        }
        else 
        {
            c.notify_all();
            
            if(selectedFile.eof()) break;   
            
            s += lineCharacter;
            c.wait(lock);
        }
    }
}


int main() 
{
	
	pthread_t p1;
	pthread_t p2;

	threadStruct file1 = {"data1.txt"};
	threadStruct file2 = {"data2.txt"};
	
	pthread_create(&p1, NULL, readFile, (void*)&file1);
	pthread_create(&p2, NULL, readFile, (void*)&file2);
	
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_exit;
	
	cout << s << endl;
	
	return 0;
}
