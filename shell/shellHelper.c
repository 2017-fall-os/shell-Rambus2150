//reserved for helpers
#include "myToc.h"
#include "shellHelper.h"

#include <stdio.h>
#include <stdlib.h>    
#include <string.h>

#include <sys/wait.h>  
#include  <unistd.h>


void myFree(char **input){
 
    for (int i = 0; *input[i] != '\0'; i++) {
      free(input[i]);
        }
    free(input);
     fprintf(stderr,"Freeing memory" );
    }//end freeMemory
    
char **getPathVec(char ** envp){
    char delim = ':';
    int i = 0;
    char ** path;
    char *pathStr = getenv("PATH");
    path = myToc(pathStr, delim); // Tokenize paths
    
    //testing if path was correctly tokenized
    //write(1,envp[i],2000);
    //printToken(path);
  return path;
}//end getpath Vec

// mending 2 strings togethter
char * concat(char *a ,char * b){
    char *newString;
    int i = 0;
    int j = 0;
    int alength = 0;
    int blength = 0;
    //waiting to reach out of bounds
    //to find length
    while(a[alength] != 0){ 
        alength++;
    }
    while(b[blength] != 0){
        blength++;
    }
    int index = 0;
    newString = (char *) malloc(alength+blength+2);
    // Copy a
    while(index < alength){ 
        newString[index++] = a[i++];
    }
    
    // adding '/'
    newString[index++] = '/'; 
    // add b to a
    while(index < alength+blength+1){ 
        newString[index++] = b[j++];
    }
    newString[index] = 0;
    return newString;
    }//end concat
   ///used for debugging 
void printToken(char ** token){
    int i=0;
    while(1){
    write(1,token[i],200);
    if(token[i]=='\0')
        break;
    i++;
        
    }
}//end print Token
// pipes need "|" symbol
int hasPipe(char* input) {
    char* temp;
    for (temp = input; *temp; temp++) {
        if (*temp == '|') {
            return 1;
        }
    }
    return 0;
}  // end of hasPipe
int hasBack(char* input) {
    char* temp;
    for (temp = input; *temp; temp++) {
        if (*temp == '&') {
            return 1;
        }
    }
    return 0;
} //end back
void myPipe(char* input, char** path, char** envp) {

    int pid1;
    int pid2;
    
    int retA;
    int retB;
    
    char** command;
    char** commandLeft;
    char** commandRight;

    char* temp;
    char* setCommand;
   
    
   
    int pipes[2];
   // char *p = myToc(input,' ');
    
    command = myToc(input, '|');
    
    if (pipe(pipes) == -1) {
       //used for child to run
    }

    pid1 = fork();
    if (pid1 < 0) {
        
      //should not for if true   
    } 
    else if (pid1 == 0) {
        // older child
        commandLeft = myToc(command[0], ' ');

        close(pipes[0]);
        dup2(pipes[1], 1);
        close(pipes[1]);

        retA = execve(commandLeft[0], &commandLeft[0], envp);
        temp = concat("/", commandLeft[0]);
       
        for (int i = 0; path[i] != '\0'; i++) {
            setCommand = concat(path[i], temp);
            commandLeft[0] = setCommand;
            retA = execve(commandLeft[0], &commandLeft[0], envp);
        }
       
       fprintf(stderr, "Command not found\n");
        exit(0);

    } 

    pid2 = fork();
    if (pid2 < 0) {
        //nor fork also
    } 
    else if (pid2 == 0) {
        // child
        commandRight = myToc(command[1], ' ');

        close(pipes[1]);
        dup2(pipes[0], 0);
        close(pipes[0]);

        retB = execve(commandRight[0], &commandRight[0], envp);
        temp = concat("/", commandRight[0]);
        for (int j = 0; path[j] != '\0'; j++) {
            setCommand = concat(path[j], temp);
            commandRight[0] = setCommand;
            retB = execve(commandRight[0], &commandRight[0], envp);
        }
        fprintf(stderr, "Command not found\n");
        exit(2);
    } 
    //need to clode pipes
    for(int a=0; a<2; a++){
    close(pipes[a]);}
    wait(NULL);
   

}

 void background(char* input , char** path, char** envp){
    //tokenize the and symbol
    char** toAnd = myToc(input, '&');
    char** command = myToc(toAnd[0], ' ');

    char* temp;
    char* commandTst;
    int j;
    int rc = fork();
    if (rc < 0) {
        // fork failed, exit
        exit(1);
    } else if (rc == 0) {
        // child
        int retVal = execve(command[0], &command[0], envp);
        temp = concat("/", command[0]);
        for (j = 0; path[j] != '\0'; j++) {
            commandTst = concat(path[j], temp);
            command[0] = commandTst;
            retVal = execve(command[0], &command[0], envp);
        }
        fprintf(stderr, "Command not found\n");
        exit(0);
    } 
    else {
    // parent
        // no waiting
    }

   
}

