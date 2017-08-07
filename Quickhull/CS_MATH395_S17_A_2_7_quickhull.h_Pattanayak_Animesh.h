/*************************
    Animesh Pattanayak
CS395/MATH395  Spring 2017
Assignment #2  Question #7
*************************/

#include <vector>
using namespace std;


struct Point
{
  int x;
  int y;
};

typedef struct Point Point;
typedef vector<Point> Point_Vector;

class quickhull_class
{
 private:
    
  Point_Vector input_set; //set of points to search
  Point_Vector hull; //set of points that are in the convex hull
 public:
  void printhull();
  void printset();
  void create_input(int size);
  void start();
  void findhull(Point P1, Point P2);
  void create_hull();
  void removal(Point P1, Point P2, Point P3);
};
