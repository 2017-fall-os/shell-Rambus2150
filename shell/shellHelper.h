//reserve for the helper headers
#ifndef TokeDef
#define TokeDef

void myFree(char **input);
char * concat(char *a,char* b);
char **getPathVec(char ** envp);
void printToken(char **token);
int hasPipe(char* input);
int hasBack(char* input);
void myPipe(char* input, char** path, char** envp);
void background(char* input, char** path char** envp);
#endif
