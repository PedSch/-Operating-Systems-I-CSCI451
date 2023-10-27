#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <fstream>
#include <sys/wait.h>
#include <regex>
#include <sys/sem.h>

#define KEY 6969
union semaphore 
{
	int value;
};
