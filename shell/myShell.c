//reserved for the shell
    //this is reserved for the test or main.
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/wait.h>  
    #include "myToc.h"
    #include    <unistd.h>
    
    void myfree(char **cmd);
    char * concat(char *a,char* b);
    char **getPathVec(char ** envp);
    void printToken(char **token);
    int main (int argc, char **argv, char** envp){
    
    //cant have more than 100 chars
    char *input = (char*)malloc(100);
    char *exitL = "exit";
    char delimCmd = ' ';
    
    char ** path=getPathVec(envp);
    
    char ** command;
    char ** dir;
    
    int wait = 0;
    while(1){
        
        //print a new line
        ///trying write
        write(1,'\n',1);
        //Print dollar symbol on console
       
        write(1,"$",1);
        
        read(0,input,100);
       
        
        if(strncmp(input, exitL,4)==0){
            printf("now exiting");
            return 0;
        }
        //store the tokens retrieved from the myToc function call
        command = myToc(input,delimCmd);
         if(command[0] == 0){
        continue;
        }
       
        
        //  write(1,'\n',1);
       // free(tokens);
         pid_t forkVal = fork();

    if(forkVal == 0){
      
      int index = 0;
      int retVal;
      
      retVal = execve(command[0], &command[0], envp);
    ///Look through tokenized paths and try to exec
      while(path[index] != 0){ 
          //Concatinate path to command name
	char *setp = concat(path[index],command[0]); 
    
	retVal = execve(setp, &command[0], envp);
        index++;
      }
      //No paths in PATH were able to execute the command
      fprintf(stderr, "Command not found\n", command[0], retVal);
      return 0;
    }else{
      
      waitpid(forkVal, &wait, 0);
    }
    
    }
  
  return 0;
}
        
    

void myFree(char **cmd){
    int i;
    for (i = 0; cmd[i] != '\0'; i++) {
        free(cmd[i]);
        }
    free(cmd);
    }
    
char **getPathVec(char ** envp){
    char delim = ':';
    int i = 0;
    char ** path;
     while(envp[i] != 0){ // Look through envp
        if(strncmp(envp[i],"PATH=",5) == 0){ // Find PATH=
            // Trim PATH= from paths string
            char *pathStr = envp[i];
            pathStr = pathStr+5;
      path = myToc(pathStr, delim); // Tokenize paths
    //testing if path was correctly tokenised
      write(1,path[0],20);
      printToken(path);
      break;
    }
    i++;
  }
  return path;
}
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
    }
void printToken(char ** token){
    int i=0;
    while(1){
    write(1,token[i],sizeof(token));
    if(token[i]=='\0')
        break;
    i++;
        
    }
}
