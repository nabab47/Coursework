/*************************
    Animesh Pattanayak
CS395/MATH395  Spring 2017
Assignment #1  Question #7
*************************/

#include <stdio.h>

int hanoi(int from, int to, int aux, int n)
{
  static int turns = 0;
  if(n > 0)
    {
      hanoi(from,to,aux,n-1);
      turns++;
      printf("%i -> %i\n",from,aux);
      turns++;
      hanoi(to,from,aux,n-1);
      printf("%i -> %i\n",aux,to);
      hanoi(from,to,aux,n-1);
      
    }
  return turns;
}

int main()
{
  int num_disk;
  printf("Enter the number of disks: ");
  scanf("%d",&num_disk);
  int moves;
  moves = hanoi(1,3,2,num_disk);
  printf("%d disks requires %d moves\n",num_disk,moves);
  return 0;
}
