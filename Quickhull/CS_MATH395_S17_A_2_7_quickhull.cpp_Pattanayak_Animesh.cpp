/*************************
    Animesh Pattanayak
CS395/MATH395  Spring 2017
Assignment #2  Question #7
*************************/

#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include "CS_MATH395_S17_A_2_7_quickhull.h_Pattanayak_Animesh.h"
using namespace std;



float area(Point P1, Point P2, Point P3)
{
  float area = ( (P1.x*(P2.y-P3.y) + P2.x*(P3.y-P1.y) + P3.x*(P1.y-P2.y)) / 2.0 );
  if( area < 0 )
    {
      area = -1*area;
    }
  return area;
}

int isInside(Point P1, Point P2, Point P3, Point P4)
{
 
  float A_Total = area(P1, P2, P3);
  float A_1 = area(P4, P2, P3);
  float A_2 = area(P1, P4, P3);
  float A_3 = area(P1, P2, P4);
  
  if( A_Total == (A_1 + A_2 + A_3) )
    {
      return 1;
    }
  else
    {
      return 0;
    }
  
}

void quickhull_class::removal(Point P1, Point P2, Point P3)
{
  Point_Vector temp;
  temp.clear();
  int i;
  for(i = 0; i < input_set.size(); i++)
    {
      //equals 0 means the point is outside the triange and therefore should be kept in the input
      if( isInside(P1,P2,P3,input_set[i]) == 0 ) 
	{
	  temp.push_back(input_set[i]);
	}
    }
  input_set = temp;
}

float distance_func(Point P1, Point P2)
{
  //distance formula without sqrt
  float dist = pow( (P1.x - P2.x),2) + pow( (P1.y - P2.y), 2);
  // sqrt of distance formula
  float dist_ret = sqrt(dist);
  return dist_ret;

}

float dot_distance(Point P1, Point P2, Point P3)
{
  //  printf("Point 1 = (%d,%d), Point 2 = (%d,%d), Point 3 = (%d,%d)\n",P1.x,P1.y,P2.x,P2.y,P3.x,P3.y);
  
  // Check to see if Point 1 and Point 2 are at the same location
  float length = distance_func(P1,P2);
  if( length == 0.0 )
    {
      return distance_func(P1, P3);
    }
  
  Point temp1;
  Point temp2;
  //P3 - P1
  temp1.x = P3.x - P1.x; 
  temp1.y = P3.y - P1.y;
  //P2 - P1
  temp2.x = P2.x - P1.x;
  temp2.y = P2.y - P1.y;
  
  //dot product 
  int temp = temp1.x*temp2.x + temp1.y*temp2.y;
  
  if( temp < 0 )
    {
      return distance_func(P3,P1);
    }
  else if( temp > 1 )
    {
      return distance_func(P3,P2);
    }
  
}



Point set_max(Point P1, Point P2, Point_Vector Set)
{
  float max = dot_distance(P1, P2, Set[0]);
  int max_i = 0;

  int i;
  for(i = 1; i < Set.size(); i++)
    {
      float temp = dot_distance(P1, P2, Set[i]);
      if(temp > max)
	{
	  max = temp;
	  max_i = i;
	}
    }
  printf("\nMax Point = (%d,%d)\nPoint1 = (%d,%d) Point2 = (%d,%d)\n",Set[max_i].x,Set[max_i].y,P1.x,P1.y,P2.x,P2.y);
  return Set[max_i];
}

bool orientation(Point P1, Point P2, Point P3)
{
  int orient1 = (P2.x - P1.x)*(P3.y - P1.y);
  int orient2 = (P2.y - P1.y)*(P3.x - P1.x);
  return orient1 > orient2;
}


void quickhull_class::create_input(int size)
{
  input_set.clear();
  
  int i;
  Point temp;
  for(i = 0; i < size; i++)
    {
      
      //srand(i*time(NULL));
      //temp.x = rand()%10;
      //temp.y = rand()%10;
      printf("Enter X ");
      scanf("%d",&temp.x);
      printf("Enter Y ");
      scanf("%d",&temp.y);
      
      
      input_set.push_back(temp);
    }
}

void quickhull_class::printset()
{
  printf("\nPrinting Input Set\n");
  if(input_set.size() == 0)
    {
      printf("Empty Vector\n");
    }
  else
    {
      for(int i = 0; i < input_set.size(); i++)
	{
	  printf("(%d,%d)\n",input_set[i].x,input_set[i].y);
	}
    }
}

void quickhull_class::printhull()
{
  printf("\nPrinting Hull Set\n");
  if(hull.size() == 0)
    {
      printf("Empty Vector\n");
    }
  else
    {
      for(int i = 0; i < hull.size(); i++)
	{
	  printf("(%d,%d)\n",hull[i].x,hull[i].y);
	}
    }
}

void quickhull_class::start()
{
  hull.clear();
  int minx_i = 0;
  int maxx_i = 0;
  int minx = input_set[0].x;
  int maxx = input_set[0].y;
  
  int i;
  for(i = 0; i < input_set.size(); i++)
    {
      Point temp = input_set[i];
      if(temp.x < minx)
	{
	  minx_i = i;
	  minx = temp.x;
	}
      else if(temp.x > maxx)
	{
	  maxx_i = i;
	  maxx = temp.x;
	}
    }
  
  hull.push_back(input_set[minx_i]);
  hull.push_back(input_set[maxx_i]);
  //printf("Pushed back points\n");
  findhull(input_set[minx_i],input_set[maxx_i]);
}

void quickhull_class::findhull(Point P1, Point P2)
{
  //printf("Entered Findhull\n");
  if(input_set.size() == 0)
    {
      return;
    }

  Point_Vector left;
  Point_Vector right;
  //left.clear();
  //right.clear();
  int i;
  for(i = 0; i < input_set.size(); i++)
    {
      if( orientation(P1,P2,input_set[i]) )
	{
	  
	  if( (P1.x != input_set[i].x || P1.y != input_set[i].y) &&
	      (P2.x != input_set[i].x || P2.y != input_set[i].y) 
	     )
	    {
	      
	      printf("The point being pushed into left = (%d,%d) with points (%d,%d) and (%d,%d)\n",input_set[i].x,input_set[i].y,P1.x,P1.y,P2.x,P2.y);
	      left.push_back(input_set[i]);
	    }
	}
      else
	{
	  
	  
	  if( (P1.x != input_set[i].x || P1.y != input_set[i].y) &&
	      (P2.x != input_set[i].x || P2.y != input_set[i].y) 
	     )
	    {
	      printf("The point being pushed into right = (%d,%d) with points (%d,%d) and (%d,%d)\n",input_set[i].x,input_set[i].y,P1.x,P1.y,P2.x,P2.y);
	      right.push_back(input_set[i]);
	    }
	}
    }
  
  if(left.size() != 0)
    {
      Point max_point = set_max(P1,P2,left);
      int repeat = 0;
      int i;
      for(i = 0; i < hull.size(); i++)
	{
	  if(max_point.x == hull[i].x && max_point.y == hull[i].y)
	    {
	      repeat = 1;
	    }
	}
      
      if(repeat == 0)
	{
	  //remove point needs to be implemented
	  removal(P1,P2,max_point);
	  hull.push_back(max_point);
	  
	 
	  findhull(max_point,P1);
	  
	  findhull(max_point,P2);
	  
	}
      else
	{
	  return;
	}
    }
  
   if(right.size() != 0)
    {
      Point max_point = set_max(P1,P2,right);
      int repeat = 0;
      int i;
      for(i = 0; i < hull.size(); i++)
	{
	  if(max_point.x == hull[i].x && max_point.y == hull[i].y)
	    {
	      repeat = 1;
	    }
	}
      
      if(repeat == 0)
	{
	  //remove point needs to be implemented
	  removal(P1,P2,max_point);
	  hull.push_back(max_point);
	  
	  
	  
	  findhull(max_point,P1);
	  
	  findhull(max_point,P2);
	  
	  
	}
      else
	{
	  return;
	}
    }
}
