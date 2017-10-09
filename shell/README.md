To compile simply enter make
once compliled you can run the shell with make play

This program sets the path from the envp argument entered in the main method.
If an invalid command is entered it will display command not found.
To exit the shell or close the program simply type exit. this will say now exiting and close the shell.This will only work if entered as a standalone command and not work with &

The tokeniser was remade with help of Victor to help read the pointer as a whole rather than searching for a null character. Funtions used are concate, to mend to string together and path method, to set the path variable other helper methods were used such as hasPipe for piping with implementations with myPipe functions.myPipe is where many of the dups and closing of pipes are handled. The hasBack functions is used for background functions I realized that this way it cant read both from the helper methods because it only delimits one character at a time. the cd command will only work from the top of the input string but does work. 

shellHelp.c contains these helper methods.
I was unable to get my shell to work with the testshell and all executions end with fail.
To run the testshell I entered ./testShell.sh myShell 

There are some implicit differentiation when compiled but for some reason everything works maybe somthing with the makefile from the shell helper.
