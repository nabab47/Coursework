/*ReadMe_Assign3.c*/


/***********************************************************


          Animesh's Shell Instruction Manual

Thank you for choosing to operate Animesh's Shell. This is 
a bash based shell with similar functionality. This shell 
is currently in beta 0.2 stage. Please, understand that
although this shell has some functionality, it should not
be used in place of an actual bash shell. With that, let us
view some of the instructions and features of Animesh's 
Shell, hereinafter referred to as The Shell.

The shell can be used by ensuring the following files
are all in the same directory:
msh.c
msh.h
mshrc

mshrc should contain commands line by line concluded with
the exit command.

One should compile msh.c by typing: gcc msh.c
Then one can begin execution by typing: ./a.out

To save the struggle, use the mshrc file specified 

*******************************************
****IT IS IMPERATIVE THAT ALL THE FILES**** 
******SPECIFIED ABOVE ARE IN THE SAME******
****DIRECTORY AND NAMED EXACTLY AS ABOVE***
*******************************************

How does The Shell operate?

The Shell takes a command from the command line. The
Shell then parses the command. After parsing the command, 
The Shell will fork off another shell to run the command.
The Shell will use the first argument of the arguments list
to search for an executable program for the command
specified. This can result in one of two primary cases.

Case I: Command Not Found
If the command specified is not found, the Shell will return
an error message and promptly kill the child shell produced.

Case II: Command Found
If the command specified is found, there are two cases.

Case II-a: Options Unrecognized
If the options after the command are not valid, an error 
message will be displayed and the child shell will promptly 
be killed.

Case II-b: Options Recognized
If the options after the command are valid, the command will
be executed! Success!

Features:

This shell includes a number of additional features such as:
History
Multiple Commands
Piping
Updated PATH variable

History:
The history is a twenty elment array of "strings". 
Elements are inserted into the front of the array until 20 
elements are entered. After that, elements will be entered into
the last index of the array and the first element is lost.
There is a running count of the number of elements that have
been entered since running the program. The history command will
print the last twenty commands attempted along with the running
count of each command. Executing the '!!' command will execute 
last command run ie: history[19]. Additionally, executing '!num'
will execute the command affiliated with 'num', if the number 
entered either does not exist in the history buffer ie: more than 
the last command entered or less than 20 commands from the current 
position, an error message should be displayed. It should be noted,
when running the command !num, !num will be stored in history before
execution, therefore, the first element of the array when the 
command is run will no longer be available. 

Multiple Commands:
Multiple commands can be run in the same line by entering in 
this fashion: cmd1 ; cmd2 ; ... ; cmd_n. Entering commands
in this way will execute the commands as if they were 
entered in succession.

Piping:
Piping allows the user to pipe the output of one command to the input of 
another. My program performs this by breaking down the commands left and 
right of the pipe and executes one after another linking the two through a 
pipe. 

PATH Variable:
The updated PATH variable works in the following way:
The user of the program must specify directly in the code what the extension
to use for the path variable. The original PATH variable is then assigned to a 
char* using the getenv("PATH") call. Then the strcat function is used to 
concatenate the extension. Then the new path is reset using setenv(String). 
The program does not make any use of this feature yet, however, it may in future 
versions! The use of the feature is visible however, as there are two print
statements in the program depicting that the variable was modified with the 
extension specified.

What commands are available?

This can be a difficult question to answer as not all 
commands have been attempted, however a brief list of common
commands that are and are not available is listed below.

Available Commands
ls
ps
top **running top requires ^C to kill which also kills The 
      Shell
more
cat
date
man **running man requires ^C to kill which also kills The 
      Shell or q which will not exit the Shell
clear
exit ***running exit will kill The Shell

Unavailable Commands
cd

This list is not, by any means, comprehensive.

The Shell accepts commands in the following ways:

Spaces before the first argument will be ignored.
Extra spaces between the arguments will be ignored.
Spaces after the final arhument will be ignored.

It should be noted: This version reads commands in from a 
file as if they were entered from stdin. And executes them.



Please enjoy experimenting with The Shell!


***********************************************************/
