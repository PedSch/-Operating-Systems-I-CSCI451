#include "hw10.h"
using namespace std;
// Pedro Schmidt
// CSCI 451
//  COMPILE WITH THE FOLLOWING FLAGS :  -std=c++11

struct sembuf sem_operator;
int main(int argc, char *argv[]) 
{
	string count = "";
	string fullText = "";
	
	ifstream file1;
	ifstream file2;
	
	ofstream file3;
	
	file1.open("shared1.dat");
	file2.open("shared2.dat");
	
	getline(file1, count);
	cout << "Type 1: " << count << endl;
	
	getline(file2, count);
	cout << "Type 2: " << count << endl << endl;
	
	int p2[2];
	p2[0] = atoi(argv[1]);
	p2[1] = atoi(argv[2]);
	close(p2[1]);
	
	char inbuf[200];
	while(1) 
   {
		read(p2[0], inbuf, 200);
		if(inbuf[0] == '#') 
      {
		break;
		}
		fullText += inbuf;;
		cout << inbuf;
		
	}
	
	file3.open("output.data");
	file3 << fullText;
	file3.close();
	
	cout << endl;
	return 0;
	
}

