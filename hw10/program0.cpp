#include "hw10.h"
using namespace std;
// Pedro Schmidt
// CSCI 451
//  COMPILE WITH THE FOLLOWING FLAGS :  -std=c++11


struct sembuf sem_operator;
union semaphore sm;
char pass[5];

int main() 
{
	
	int p1[2];
	int p2[2];
	
    if(pipe(p1) == -1)
     {
		perror("Could not create pipe 1.");
		exit(1);
	}

	if(pipe(p2) == -1) 
   {
		perror("Could not create pipe 2.");
		exit(1);
	}
    
    int sem = semget(KEY, 1, IPC_CREAT | 0666);
	if(sem == -1) 
   { 
		cout << "Could not create semaphore." << endl;
		exit(1);
	}
	int ret;
	
	sm.value = 0;
	ret = semctl(sem, 0, SETVAL, sm);
	if(ret == -1)
   {
		cout << "Could not initialize sem value." << endl;
		exit(1);
	}
    
    string semID = to_string(sem);
	
	pid_t process1;
	process1 = fork();

	if(process1 < 0)
    {
		perror("Unable to fork process 1.");
		exit(1);
	} else if(process1 == 0) 
   {

		sprintf(pass, "%d", KEY);

		char read1[16];
		char write1[16];

		sprintf(read1,  "%d", p1[0]);
		sprintf(write1, "%d", p1[1]);		

		char* arr1[5] = {"./p1", pass, read1, write1, NULL};

		execv(arr1[0], arr1);	
	
	}
	
	pid_t process2;
	process2 = fork();

	if(process2 < 0)
    {
		perror("Unable to fork process 2.");
		exit(1);
	} else if(process2 == 0)
    {

		sprintf(pass, "%d", KEY);

		char read1[20];
		char write1[20];

		char read2[20];
		char write2[20];

		sprintf(read1,  "%d", p1[0]);
		sprintf(write1, "%d", p1[1]);

		sprintf(read2,  "%d", p2[0]);
		sprintf(write2, "%d", p2[1]);

		char* arr2[] = {"./p2", pass, read1, write1, read2, write2, NULL};

		execv(arr2[0], arr2);
	
	} else 
   {
		waitpid(process1, 0, 0);
		waitpid(process2, 0, 0);

		pid_t process3;
		process3 = fork();

		if(process3 < 0) 
      {
			perror("Unable to fork process 3.");
			exit(1);
		} else if(process3 == 0)
       {
		
			char read2[20];
			char write2[20];
			sprintf(read2,  "%d", p2[0]);
			sprintf(write2, "%d", p2[1]);
			char* arr3[4] = {"./p3", read2, write2, NULL};
			execv(arr3[0], arr3);
		}
		waitpid(process3, 0, 0);
	}
	return 1;
	
}
