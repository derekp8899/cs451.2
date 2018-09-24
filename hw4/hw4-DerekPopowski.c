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

pthread_mutex_t mutex;
int input;
void readIn(void);
void writeOut(void *outFile);

int main(int argc, char *argv[]){

  pthread_mutex_init(&mutex, NULL);  
  FILE *outFile = fopen("hw4.out","w");
  readIn();

}
void readIn(void){

  FILE *inFile = fopen("hw4.in","r");
  
  int i;
  for(i = 0; i < 4; i++){
    fscanf(inFile,"%d\n",&input);
    printf("%d\n",input);
  }
}

void writeOut(void *outFile){

  int i;
  for(i = 0; i < 4; i++){

    fprintf(outFile,"%d\n",input);

  }


}
