#include "hw10.h"
using namespace std;
// Pedro Schmidt
// CSCI 451
//  COMPILE WITH THE FOLLOWING FLAGS :  -std=c++11


struct sembuf sem_operator;

int main(int argc, char *argv[]) 
{
	
	int ID = atoi(argv[1]);
	int sem = semget(ID, 1, IPC_CREAT | 0666);
	int rv; 
	
	
	//cout << rv << endl;
	
	string line;
	string total = "";
	ifstream fin;
    fin.open("input.data");
    while(fin) {
        getline(fin, line);
        line += "*\n";
        total += line;
    }
    
    fin.close();
    
    string s{total};
	regex regex{R"([\s]+)"};
	sregex_token_iterator it{s.begin(), s.end(), regex, -1};
	vector<string> words{it, {}};
    
    int p1[2];
	p1[0] = atoi(argv[2]);
	p1[1] = atoi(argv[3]);
    
    char inbuf[100];
    for(int i = 0; i < words.size() - 1; i++)
    {
    	rv = semctl(sem, 0, GETVAL);
    	while(rv % 2 == 1) 
      {
    		rv = semctl(sem, 0, GETVAL);
    	}
    	string temp = words[i];
    	//cout << temp << endl;
    	write(p1[1], temp.c_str(), 200);
    	sem_operator.sem_num = 0;
		sem_operator.sem_op = +1;
		sem_operator.sem_flg = 0;
		semop(sem, &sem_operator, 1);
	}
	rv = semctl(sem, 0, GETVAL);
    while(rv % 2 == 1) 
    {
    	rv = semctl(sem, 0, GETVAL);
    }
	string pound = "#";
    write(p1[1], pound.c_str(), 200);
    sem_operator.sem_num = 0;
	sem_operator.sem_op = +1;
	sem_operator.sem_flg = 0;
	semop(sem, &sem_operator, 1);
    
	return 0;
}







