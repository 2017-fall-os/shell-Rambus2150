//reserved for the shell
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/wait.h>  
    #include <sys/types.h>
    #include  <unistd.h>
    
        //reserved for helpers
#include "myToc.h"
#include "shellHelper.h"

        //cant have more than 10000 chars
#define BUFF 10000
    int main (int argc, char **argv, char** envp){
    
   
    char *exitL = "exit";
    char delimCmd = ' ';
    char *cd = "cd";
    char ** path=getPathVec(envp);
    char *input;
    char ** command;
    int dir;
   
    
    int wait = 0;
    
    int retVal;
    while(1){
       input =(char*)malloc(BUFF);
        //print a new line
        //Print dollar symbol on console
        fprintf(stderr,"\n$" );
        int len=read(0,input,BUFF);
        input[len-1]='\0';
        
        command = myToc(input,delimCmd);
        //lazy exit
        if(strncmp(input, exitL,4)==0){
            fprintf(stderr,"now exiting\n");
            return 0;
        }// lazy change dir
        
        if(strncmp(input,cd,2)==0){
            //remove the command from inputstring
            input = input+3;
            dir = chdir(input);
            if (dir < 0) {
                fprintf(stderr,  "Dir not found");
            }
            continue;
        }
         if(hasPipe(input)){
            myPipe(input,path,envp);
            continue;
        }
        if(hasBack(input)){
            background(input,path,envp);
            continue;
        }
        //store the tokens retrieved from the myToc function call
        //has an int value
         pid_t forkVal = fork();
	 
        if(forkVal == 0){
            // write(1,forkVal,10);
           
            retVal = execve(command[0], &command[0], envp);
            char *temp =concat("/",command[0]);
            ///Looking through tokenized paths to exec
            
            for (int i = 0; path[i] != '\0'; i++) { 
            
                //Concatinate path to command name
                char *setp = concat(path[i],temp);
                command[0]=setp;
        
                retVal = execve(command[0], &command[0], envp);
            
                }
        //No paths in PATH were able to execute the command
            fprintf(stderr, "Command not found\n", command[0], retVal);
            myFree(command);
            free(input);
            return 0;
        }
        else{

            waitpid(forkVal, &wait, 0);
            }
           
  // free(input);
   //myFree(command);
    }
  
  return 0;
}
        
    
