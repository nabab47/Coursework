/***msh.h***/

/*Animesh Pattanayak*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>



int pipe_nopipe(char* og_string)
{
  int i = 0;
  for(i = 0; i < strlen(og_string); i++)
    {
      if(og_string[i] == '|')
	{
	  return 1;
	}
    }
  return 0;
}
    
void launch_command(char** arg_array, char* og_string, int add_or_run)
{
  pid_t pid, wpid = 0;
  int status;
  int exec_ret;
  int z;
  int index = 0;
  static int count = 0;
  static int history_start = 0;

  static int hist_empty = 0;
  
  static char** history;
  if(hist_empty == 0)
    {
      hist_empty = 1;
      
      history = (char**)malloc(20*sizeof(char*));
      
      for(index = 0; index < 20; index++)
	{
	  history[index] = '\0';
	}
    }
  
  
  if(count < 20)
    {
      if( (strcmp(og_string,"!!") != 0) && (og_string[0] != '!') )
	{
	  history[count] = (char*)malloc(strlen(og_string)*sizeof(char));
	  strcpy(history[count],og_string);
	  count++;
	}
    }
  else
    {
      if( (strcmp(og_string,"!!") != 0) && (og_string[0] != '!') )
	{
	  free(history[0]);
	  for(index = 0; index < 19; index++)
	    {
	      history[index] = history[index+1];
	    }
	  history[19] = (char*)malloc(strlen(og_string)*sizeof(char));
	  strcpy(history[19],og_string);
	  count++;
	  history_start = count - 20;
	}
    }
  
  if(add_or_run == 0)
    {
      if( strcmp(arg_array[0],"history") == 0 )
	{
	  int temp = 0;
	  
	  for(temp = 0; temp < 20; temp++)
	    {
	      if(history[temp] != '\0')
		{
		  printf("%i : %s\n",(history_start+temp),history[temp]);
		}
	    }
	}
      
      else if ( arg_array[0][0] == '!' )
	{
	  if( arg_array[0][1] == '!' )
	    {
	      //bang bang
	      //execute history
	      if(count < 20)
		{
		  char** temp;
		  
		  if( strcmp(history[count-1],"history") == 0 )
		    {
		      int temp = 0;
		      
		      for(temp = 0; temp < 20; temp++)
			{
			  if(history[temp] != '\0')
			    {
			      printf("%i : %s\n",(history_start+temp),history[temp]);
			    }
			}
		    }
		  else
		    {
		      makearg(history[count-1],&temp);
		      //printf("Make arg worked!\n");
		      pid = fork();
		      
		      if(pid == 0)
			{
			  exec_ret = execvp(temp[0], temp);
			  
			  if(exec_ret == -1)
			    {
			      printf("?: %s: command not found.\n",temp[0]);
			      exit(1);
			    }
			}
		      else if(pid < 0)
			{
			  printf("Error: Forking Error\n");
			}
		      else
			{
			  while(wait(&status) != pid);
			}
		      
		      
		      //launch_command(temp,history[count-1]);
		      
		      //execute history[count-1]
		    }
		}
	      else
		{
		  if( strcmp(history[19],"history") == 0 )
		    {
		      int temp = 0;
		      
                      for(temp = 0; temp < 20; temp++)
                        {
                          if(history[temp] != '\0')
                            {
                              printf("%i : %s\n",(history_start+temp),history[temp]);
                            }
                        }
		    }
		  else
		    {
		      char** temp;
		      makearg(history[19],&temp);
		      //printf("Make arg worked!\n");
		      
		      pid = fork();
		      
		      if(pid == 0)
			{
			  exec_ret = execvp(temp[0],temp);
			  
			  if(exec_ret == -1)
			    {
			      printf("?: %s: command not found.\n",temp[0]);
			      exit(1);
			    }
			}
		      else if(pid < 0)
			{
			  printf("Error: Forking Error\n");
			}
		      else
			{
			  while(wait(&status) != pid);
			}
		      //execute history[19]
		    }
		}
	    }
	  else if ( isdigit(arg_array[0][1]) )
	    {
	      //bang number
	      int temp = 1;
	      char* str = (char*)malloc((strlen(arg_array[0])-1)*sizeof(char));
	      while( (arg_array[0][temp] >= '0') && (arg_array[0][temp] <= '9') && (arg_array[0][temp] != '\0') )
		{
		  //printf("The character at arg_array[0][%i] is %c\n",temp,arg_array[0][temp]);
		  str[temp-1] = arg_array[0][temp];
		  temp++;
		}
	      //printf("The string recorded is %s\n",str);
	      int str_num = atoi(str);
	      //printf("The number recorded is %i\n",str_num);
	      
	      if(count < 20)
		{
		  if(str_num > count || str_num < history_start)
		    {
		      printf("Error: Cannot execute\n");
		    }
		  else
		    {
		      if( strcmp(history[str_num],"history") == 0 )
			{
			  int temp = 0;
			  
			  for(temp = 0; temp < 20; temp++)
			    {
			      if(history[temp] != '\0')
				{
				  printf("%i : %s\n",(history_start+temp),history[temp]);
				}
			    }
			}
		      else
			{
			  char** temp;
			  makearg(history[str_num],&temp);
			  
			  pid = fork();
			  
			  if(pid == 0)
			    {
			      exec_ret = execvp(temp[0],temp);
			      
			      if(exec_ret == -1)
				{
				  printf("?: %s: command not found.\n",temp[0]);
				  exit(1);
				}
			    }
			  else if(pid < 0)
			    {
			      printf("Error: Forking Error\n");
			    }
			  else
			    {
			      while(wait(&status) != pid);
			    }
			}
		      //execute history[str_num]
		    }
		}
	      else
		{
		  if(str_num > count || str_num < history_start)
		    {
		      printf("Error: Cannot execute\n");
		    }
		  else
		    {
		      if( strcmp(history[(20 - (count - str_num))],"history") == 0 )
			{
			  int temp = 0;
			  
			  for(temp = 0; temp < 20; temp++)
			    {
			      if(history[temp] != '\0')
				{
				  printf("%i : %s\n",(history_start+temp),history[temp]);
				}
			    }
			}
		      else if( strcmp(history[(20 - (count -str_num))],"!!") == 0 )
			{
			  //Do nothing, this does not support recursive calls to !! 
			}
		      else
			{
			  char** temp;
			  makearg(history[(20 - (count - str_num))],&temp);
			  
			  pid = fork();
			  
			  if(pid == 0)
			    {
			      exec_ret = execvp(temp[0],temp);
			      
			      if(exec_ret == -1)
				{
				  printf("?: %s: command not found.\n",temp[0]);
				  exit(1);
				}
			    }
			  else if(pid < 0)
			    {
			      printf("Error: Forking Error\n");
			    }
			  else
			    {
			      while(wait(&status) != pid);
			    }
			}
		      //execute history[20-(count-num)]
		    }
		}
	    }
	  else
	    {
	      printf("FAILURE!!!!!\n");
	    }
	}
      else
	{
	  pid = fork();
	  
	  if(pid == 0)
	    {
	      exec_ret = execvp(arg_array[0], arg_array);
	      
	      if(exec_ret == -1)
		{
		  printf("?: %s: command not found.\n",arg_array[0]);
		  exit(1);
		}
	    }
	  else if(pid < 0)
	    {
	      printf("Error: Forking Error\n");
	    }
	  else
	    {
	      while(wait(&status) != pid);
	    }
      
	  //Copy code from other assignment
	}
    }
}

void multiple_commands(int num_SC,char* og_string)
{
  
int temp = 0;
  int index = 0;
  int num_strings = num_SC+1;
  char temp_string[256];
  int last_index = 0;
  for(index = 0; index < num_strings; index++)
    {
      for(temp = 0; temp < 256; temp++)
	{
	  temp_string[temp] = '\0';
	}
      temp = 0;
      //int count = 0;
      while( og_string[last_index] != ';' )
	{
	  temp_string[temp] = og_string[last_index];
	  temp++;
	  last_index++;
	}
      last_index = last_index + 2;

      char** double_arg;
      makearg(temp_string,&double_arg);
      launch_command(double_arg,temp_string,0);
      //      printf("The current string is %s\n",temp_string);
    }
}


void single_command(char** arg_array, char* og_string)
{
  launch_command(arg_array,og_string,0);
}

int makearg(char s[], char **args[])
{
  int string_index = 0;
  int buffer_index = 0;
  int size = 0; //Will allow us to know how large to make dynamically allocated array
  int i = 0;
  int j = 0;
  int count = 0;
  char temp;
  char* start;
  char* end;
  char first_char;
  int first_non_space_char_index;
  int spaces_check = 0;
  int not_empty = 0;
  char last_char;
  char buffer[256];
  first_char = s[string_index];
  
  //This function will skip over extra spaces in an input line
  void recursive_space_no_null()
  {
    if(s[string_index + 1] == ' ')
      {
	string_index = string_index + 1;
	recursive_space_no_null();
      }
  }

  if(first_char == ' ')
    {
      //printf("The first char is a space\n");
      recursive_space_no_null();
    }
  
  if(first_char == ' ')
    {
      string_index++;
    }
  //printf("The string index at the end of checking for spaces is %i\n", string_index);
  //Assign the index of the first non space char
  first_non_space_char_index = string_index;
  //Start string index where it was any way, this line is unnecessary
  //but it is there because it will be used later on
  string_index = first_non_space_char_index;
  //This function will replace extra spaces with null character
  //and then update the char* end to the next character that is
  //not a space
  void recursive_space()
  {
    if(s[string_index + 1] == ' ')
      {
	string_index = string_index + 1;
	s[string_index] = '\0';
	recursive_space();
      }
    else
      {
	end = &s[string_index];
      }
  }
  
  //This function determines the number of arguments by reading 
  //until each space or sequence of spaces handled by
  //recursive_space_no_null()
	
  while(s[string_index] != '\0')
    {
      last_char = s[string_index];
      not_empty = 1;
      if(s[string_index] == ' ' || s[string_index] == '\0')
	{
	  //spaces_check = 1;
	  // if(size != 0 && s[string_index] != '\0')
	  if(s[string_index] != '\0')
	    {
	      recursive_space_no_null();
	    }
	  size++;
	  if(s[string_index] == '\0')
	    {
	      break;
	    }
	}
      string_index++;
    }
  
  if(not_empty == 1 && last_char != ' ')
    {
      size++;
    }
  //Reset string index for actual storing of arguments
  string_index = first_non_space_char_index;
  //string_index = 0;
  
  //Dynamically allocate memory for char** arg
  char** arg = malloc(size*sizeof(char*));
  
  start = &(s[string_index]);
  
  //printf("You are about to actually enter storing loop!\n");
  while(1)
    {
      end = &s[string_index];
      temp = s[string_index];
      //  printf("Checkpoint 1\n");
      if(temp == ' ' || temp == '\0')
	{
	  if(size != 0 && s[string_index] != '\0')
	    {
	      s[string_index] = '\0';
	      recursive_space();
	    }
	  s[string_index] = '\0';
	  
	  if(not_empty == 1)
	    {
	      buffer[count++] = '\0';
	      //printf("You are about to malloc\n");
	      arg[i] = malloc(count*sizeof(char));
	      //printf("You have malloc\n");
	      strcpy(arg[i], buffer);
	      int j;
	      for(j = 0; j < 256; j++)
		{
		  buffer[j] = 0;
		}
	      count = 0;
	      i++;
	    }
	  if(i == size)
	    {
	      break;
	    }
	  start = end+1;
	}
      //     printf("Checkpoint 2\n");
      if(s[string_index] != '\0' && s[string_index] != ' ')
	{
	  buffer[count] = s[string_index];
	  count++;
	}
      string_index++;
      // printf("Checkpoint 3\n");
    }
  
  arg[i++] = '\0';
  
  //printf("Do you make it to the end of the program?\n");
  *args = arg;
  return size; //This takes care of returning the argument count
}

int num_semicolon(char* og_string)
{
  int i;
  int count = 0;
  for(i = 0; i < strlen(og_string); i++)
    {
      if( og_string[i] == ';')
	{
	  count++;
	}
    }
  return count;
}
