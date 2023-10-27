#include "hw10.h"
using namespace std;
// Pedro Schmidt
// CSCI 451
//  COMPILE WITH THE FOLLOWING FLAGS :  -std=c++11

int type1 = 0;
int type2 = 0;

string pigLatin(string temp) 
{
	//transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	string sub = temp.substr(0, 1);
	transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
	string mark = "";
	string post = temp.substr(temp.size() - 1, temp.size());
	if(post.compare(",") == 0) 
   {
		temp = temp.substr(0, temp.size() - 1);
		mark = ",";
	}
	if(post.compare(".") == 0) 
   {
		temp = temp.substr(0, temp.size() - 1);
		mark = ".";
	}
	char letter[sub.size() + 1];
	strcpy(letter, sub.c_str());
	
	switch(letter[0]) 
   {
		case 'a':
			temp += "ray" + mark;
			type1++;
			break;
		case 'e':
			temp += "ray" + mark;
			type1++;
			break;
		case 'i':
			temp += "ray" + mark;
			type1++;
			break;
		case 'o':
			temp += "ray" + mark;
			type1++;
			break;
		case 'u':
			temp += "ray" + mark;
			type1++;
			break;
		default:
			temp = temp.substr(1, temp.size());
			temp = temp + sub + "ay" + mark;
			type2++;
			break;
	}
	
	
	return temp;
}


struct sembuf sem_operator;
int main(int argc, char *argv[]) 
{
	
	int ID = atoi(argv[1]);
	int sem = semget(ID, 1, IPC_CREAT | 0666);
	int rv; 
	
	int p1[2];
	p1[0] = atoi(argv[2]);
	p1[1] = atoi(argv[3]);
	
	int p2[2];
	p2[0] = atoi(argv[4]);
	p2[1] = atoi(argv[5]);
	
	close(p1[1]);
	close(p2[0]);
	
	char inbuf[200];
	string temp = "";
	while(1) 
   {
		rv = semctl(sem, 0, GETVAL);
    	while(rv % 2 == 0) 
      {
    		rv = semctl(sem, 0, GETVAL);
    	}
		
		read(p1[0], inbuf, 200);
		if(inbuf[0] == '#')
       {
			break;
		}
		//cout << inbuf << endl;
		temp = inbuf;
		if (temp.find('*') != string::npos) 
      {
    		temp.pop_back();
    		
    		temp = pigLatin(temp);
    		
    		temp += "\n";
    		
    	} else 
      {
    		temp = pigLatin(temp);
    		temp += " ";
    		
    	}
		
		write(p2[1], temp.c_str(), 200);
		sem_operator.sem_num = 0;
		sem_operator.sem_op = +1;
		sem_operator.sem_flg = 0;
		semop(sem, &sem_operator, 1);
		
		//cout << temp << " ";
	}
	string pound = "#";
	write(p2[1], pound.c_str(), 200);
	
	ofstream file1;
	ofstream file2;
	
	file1.open("shared1.dat");
	file2.open("shared2.dat");
	
	file1 << type1;
	file2 << type2;
	
	file1.close();
	file2.close();
	
	semctl(sem, 0, IPC_RMID);
	
	return 0;
}

















