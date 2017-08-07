/***msh.c***/

/**********************/
/* Animesh Pattanayak */
/*    Axel Krings     */
/*   Assignment #3    */
/**********************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "msh.h"

#define READ 0
#define WRITE 1

int main(char* envp[])
{
  /*
    The section below shows my adding to the PATH variable I have initially
    extracted the PATH variable, then have added to it and printed the result 
    and then updated the temp variable holding the PATH to show the actual 
    PATH variable and not just my path_var was updated!
  */
  char* path_var = getenv("PATH");
  printf("************************************************\n");
  printf("The path before extension is: %s\n\n",path_var);
  char* exten = "/animesh";
  strcat(path_var,exten);
  setenv(path_var,"PATH",0);
  printf("The path after extension is: %s\n\n",path_var);
  path_var = getenv("PATH");
  printf("The path after receiving again: %s\n\n",path_var);
  printf("************************************************\n");
 
  
  FILE* IN;
  IN = fopen("mshrc","r");
  char** argv;
  int temp;
  while(1)
    {
      
      char str[256];
      char copy[256];
      
      int size = 256;
      int pipe_exist = 0;
      int count = 0;
      int argc;
      int i;
      int semicolon_count = 0;
      int rand_var = 0;
      int static end = 0;
      
      if(end == 0)
	{
	  while( (temp = fgetc(IN))  != '\n')
	    {
	      
	      if(temp == EOF)
		{
		  end = 1;
		  break;
		}
	      else
		{
		  //fgetc(IN);
		  str[count++] = temp;
		}
	    }
	  /*
	  if(end == 1)
	    {
	      break;
	    }
	  */
	  str[count] = '\0'; 
	}
      else if(end == 1)
	{
	  //fgets(str,256,IN);
	  //printf("The string entered is %s\n",str);
	  
	  printf("?: ");
	  
	  while( (temp = getchar())  != '\n')
	    {
	      str[count++] = temp;
	    }
	  
	  str[count] = '\0';
	  
	}
      
      strcpy(copy,str);
      //printf("The string entered is %s\n",copy);
      
      if(count == 0)
	{
	  //printf("You have entered an empty string.\n");
	}
      else if( (strcmp(str, " ")) == 0)
	{
	  //printf("You have entered a space.\n");
	}
      else if( (strcmp(str, "exit")) == 0)
	{
	  break;
	}
      else if(count >= 256)
	{
	  printf("That is too many characters for a command. Goodbye\n");
	}
      else
	{
	  argc = makearg(str, &argv);
	  //printf("The string entered is %s\n",copy);
	  pipe_exist = pipe_nopipe(copy);
	  semicolon_count = num_semicolon(copy);
	  //printf("The number of semicolons is %i\n",semicolon_count);
	  if(pipe_exist == 0)
	    {
	      //printf("Entered no pipe section\n");
	      if(semicolon_count == 0)
		{
		  single_command(argv,copy);
		}
	      else
		{
		  multiple_commands(semicolon_count,copy);
		}
	      //No piping, run normal
	    }
	  else
	    {
	      char** garbage;
	      launch_command(garbage,copy,1);
      
	      char str_wo_pipe[256];
	      int word_count = 0;
	      int index_num;
	      for(index_num = 0; index_num < 256; index_num++)
		{
		  str_wo_pipe[index_num] = '\0';
		}
	      //    printf("Allocated space for str_wo_pipe\n");
	      int temp = 0;
	      int str_temp = 0;
	      for(temp = 0; temp < 256; temp++)
		{
		  if(copy[temp] == ' ')
		    {
		      word_count++;
		    }
		  if(copy[temp] == '|')
		    {
		      break;
		    }
		}
	      //printf("The word count before the pipe is: %i\n",word_count);
	      for(temp = 0; temp < 256; temp++)
		{
		  //  printf("Looped %i times\n",temp);
		  if(copy[temp] != '|')
		    {
		      str_wo_pipe[str_temp] = copy[temp];
		      //printf("Currently the string reads %s\n",str_wo_pipe);
		      str_temp++;
		    }
		  else
		    {
		      
		      temp++;
		    }
		}
	      //printf("Finished the looping\n");
	      //printf("The string is: %s\n",str_wo_pipe);
	      char** args1;
	      char** args2;
	      
	      /*Do what I did with semicolon*/
	      char str1[256];
	      char str2[256];
	      int tempy = 0;
	      int tempx = 0;
	      for(tempy = 0; tempy < 256; tempy++)
		{
		  str1[tempy] = '\0';
		  str2[tempy] = '\0';
		}
	      tempy = 0;
	      while(copy[tempy] != '|')
		{
		  str1[tempx] = copy[tempy];
		  tempx++;
		  tempy++;
		}
	      tempy=tempy+2;
	      tempx=0;
	      while(copy[tempy] != '\0')
		{
		  str2[tempx] = copy[tempy];
		  tempx++;
		  tempy++;
		}
	      //printf("Strings are: %s %s\n",str1,str2);
	      //makearg(str_wo_pipe,&args);

	      
	      
	      
	      int fd[2];
	      pid_t pid;
	      int status;
	      int save_stdin = dup(0);
	      int save_stdout = dup(1);
	      pid = fork();
	      if(pid == 0)
		{
		  pipe(fd); //Create a pipe
		  pid = fork();
		  if(pid == 0)
		    {
		      makearg(str1,&args1);
		      close(fd[READ]);
		      dup2(fd[WRITE],1);
		      //close(fd[WRITE]);
		      execvp(args1[0],args1);
		      perror("connect\n");
		    }
		  else if(pid < 0)
		    {
		      exit(1); 
		    }
		  else
		    {
		      makearg(str2,&args2);
		      close(fd[WRITE]);
		      dup2(fd[READ],0);
		      //close(fd[READ]);
		      execvp(args2[0],args2);
		      perror("connect\n");
		      // dup2(0,fd[READ]);
		    }
		   dup2(save_stdin,0);
		   dup2(save_stdout,1);
		}
	      else if(pid < 0)
		{
		  exit(1);
		}
	      else
		{
		  while(wait(&status) != pid);
		}
	      
	      //exit(1);
	      //Piping, run pipe
	    }
	}
    }
}

