#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h>   
#include <sys/wait.h>


//Pedro Schmidt
//homework 2
//fork bomb 

int main()
{

	pid_t pid = fork();  //fork() copy of the the parent used to create new process 
	char* args[] = {"usr/bin/firefox", NULL};
	
  	if (pid < 0) 
   { 
  	printf("Error."); //  fork pid 
  	}
  	else if (pid == 0) 
   {
   
  		execvp("./a.out", NULL); //using exe()
  	}
  	else 
   {  
  		execvp("Mozilla", args);
  	}
	
	return 0;
	
}

}
