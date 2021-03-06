/*
Each producer reads its input file one character at a time and writes it into a
shared buffer.The consumer consumes characters from this buffer one at a time and writes them
into output files. The size of the buffer is finite. Use semaphores for synchronization
between producer and consumer processes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
//#include <sys/ipc.h>

#define MAX_BUFFER 1024
#define INPUTFILE "producerInput2.txt"
void main()
{
  //ftok creates a code depending upon actual file and the number you provide.
  key_t key = ftok("producerInput.txt", 420);

  //create shared memory, if already there give 0666 permission.
  int shmid = shmget(key, MAX_BUFFER, 0666 | IPC_CREAT);

  //attach shared memory.
  char *str = (char*) shmat(shmid, NULL, 0);

  printf("Write Data : ");

  //getting input from the file.

  FILE *fp;
  if((fp = fopen(INPUTFILE,"r")) == NULL)
    {
      perror("Input file: ");
      exit(1);
    }

  int i;
  char buffer;
  int n;
  fscanf(fp,"%d",&n);

  for(i = 0; i < n; i++)
    {
      fscanf(fp,"%c",&str[i]);
    }

  for(i = 0; i < n; i++)
    {
	    printf("%c ", str[i]);
      //fprintf(fp,"%c ",str[i]);
    }
}
