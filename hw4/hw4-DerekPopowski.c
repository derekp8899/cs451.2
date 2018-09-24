/*
Derek Popowski
derek.a.popowski@und.edu
CSci 451 - Operating Systems 1
Homework 4
9-24-18

*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int input;
int s;
int f;
void* readIn(void *ptr);
void* writeOut(void *out);

int main(int argc, char *argv[]){

  pthread_t thrd1,thrd2;
  pthread_mutex_init(&mutex, NULL);
  FILE *outFile = fopen("hw4.out","w");
  FILE *inFile;
  s = 0;
  f = 1;
  pthread_create(&thrd1,NULL,readIn,NULL);
  pthread_create(&thrd2,NULL,writeOut,(void*)outFile);
  pthread_join(thrd1,(void**)&inFile);
  pthread_join(thrd2,NULL);
  fclose(outFile);
  fclose(inFile);
}
void* readIn(void* ptr){

  FILE *inFile = fopen("hw4.in","r");
  
  int i;
  while(s == 0){
    while(f ==1){ 
      pthread_mutex_lock(&mutex);
      if(fscanf(inFile,"%d\n",&input) != EOF){ 
	f--;
	pthread_mutex_unlock(&mutex);   
      }
      else{
	s++;
	pthread_mutex_unlock(&mutex);
	break;
      }
    }
  }
  return (void*)inFile;
}

void* writeOut(void *out){

  FILE *outFile = (FILE*)out;
  
  while (s == 0){
    while( f == 0){
      pthread_mutex_lock(&mutex);
      if(input%2 == 0)
	fprintf(outFile,"%d\n%d\n",input,input);
      else
	fprintf(outFile,"%d\n",input);
      pthread_mutex_unlock(&mutex);
      f++;
    }
  }
  return NULL;
}
