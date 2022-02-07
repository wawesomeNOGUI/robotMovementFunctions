#include "math.h"
//#include <stdio.h>
#include <iostream>

#define PI 3.14159265

//calculate the angle betweent the robot's yaw vector, and the vector from the robot to the x,y it wants
//to travel to (Yaw Vector will be made using unit circle with GPS10.yaw() e.g <cos(yaw), sin(yaw)>)
//Travel Vector will be made by subtracting robot x,y from point x,y
//then use dot product equation to get angle between the two vectors.
struct vector2 {
  double x, y;
};

struct vector2 *yawVector = new vector2();
struct vector2 *travelVector = new vector2();

//takes x,y of point you want to travel to
double calcAngleBetweenYAndT(double x, double y, double rYaw)
{
  double yaw = rYaw * PI / 180;  //yaw() returns degrees

  //get unit circle x,y from yaw angle
  yawVector->x = cos(yaw);
  yawVector->y = sin(yaw);

  //get travel vector (use robot location as origin)
  travelVector->x = x - 0;
  travelVector->y = y - 0;

  //get dot product of vectors
  double dotProduct = yawVector->x * travelVector->x + yawVector->y * travelVector->y;

  //find magnitudes with distance formula
  double yDistance = 1;  //always 1 because uses <cos(yaw), sin(yaw)> unit circle length
  double tDistance = sqrt(travelVector->x * travelVector->x + travelVector->y * travelVector->y);

  double a = acos(dotProduct / (yDistance * tDistance));
  a = a * 180 / PI; //convert back to degrees

  //Check if point is below or above robot y (cause acos only returns 0-180 degrees)
  //equation in check is based on a . b = |a|*|b|*cos(theta)
  //we then get a perpendicular point to yawVector by making a new point (x,y) = (-yawVector.y, yawVector.x)
  //we know the magnitudes multiplied |a|*|b| will always be positive
  //we also know that if the cos of the angle theta between the perpendicular of yawVector and travelVector
  //is negative then 90 < theta <= 180 or positive then 0 <= theta <= 90
  //therefore if the dot product of a . b is negative, the angle was obtuse
  //if the dot product was positive the angle was acute
  //refer to pg. 808, Chapt. 12 Vectors and the Geometry of Space, James Stewart Calculus
  if (travelVector->y * yawVector->x - travelVector->x * yawVector->y >= 0) { //dot product of perpendicular yawVector and yawVector
    return a;
  } else {
    return -1 * a;
  }

  return a;
}

int main () {
  double x, y, rYaw;
LABEL:
    //printf("%f", calcAngleBetweenYAndT(-86.5, -44));
  std::cout << "X: ";
  std::cin >> x;
  std::cout << "\n";
  std::cout << "Y: ";
  std::cin >> y;
  std::cout << "\n";
  std::cout << "rYaw: ";
  std::cin >> rYaw;
  std::cout << "\n";

  std::cout << calcAngleBetweenYAndT(x, y, rYaw) << "\n";

goto LABEL;
    return 1;
}
