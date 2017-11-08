#include "./freeglut-3.0.0/include/GL/freeglut.h" 

#include "Point.h"

int factorial(int n);

void drawPoint(Point p);
void drawLine(Point p1,Point p2);

void drawGrid();

void drawCurve(Point TabPointsOfCurve[], long nbPoints);

void drawQuad(Point p1,Point p2,Point p3,Point p4);
void drawTriangle(Point p1,Point p2,Point p3);

void displayVoxel(Point center, double lenght);

double distance(Point p1,Point p2);

