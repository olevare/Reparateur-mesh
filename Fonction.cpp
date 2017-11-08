#include <math.h>
#include "Fonction.h"


int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void displayVoxel(Point center, double lenght){

  double l = lenght/2;

  	glBegin(GL_QUADS);

    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()+l);


    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()+l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()+l);

    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()-l);

    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()+l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()+l);

    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()+l);
    glVertex3f(center.getX()+l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()+l);

    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()+l);
    glVertex3f(center.getX()-l,center.getY()+l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()-l);
    glVertex3f(center.getX()-l,center.getY()-l,center.getZ()+l);
	glEnd();

}



void drawPoint(Point p){
  glPointSize(5);
  glBegin(GL_POINTS);
   glVertex3f(p.getX(), p.getY(), p.getZ());
  glEnd();
}

void drawLine(Point p1,Point p2){
  glBegin(GL_LINES);
   glVertex3f(p1.getX(), p1.getY(), p1.getZ());
   glVertex3f(p2.getX(), p2.getY(), p2.getZ());
  glEnd();
}

void drawGrid(){
  int xmax = 4;
  int xmin = -4;
  int ymin = -4;
  int ymax = 4;

  for(int i=xmin; i<xmax ;++i){
    if(i == 0){
      glColor3f(.0, .7, .0);
    }else{
      glColor3f(0.4, .4, .4);
    }
    glBegin(GL_LINES);
     glVertex3f(i, ymin, 0);
     glVertex3f(i, ymax, 0);
    glEnd();
  }

  for(int i=ymin; i<ymax ;++i){
    if(i == 0){
      glColor3f(.7, 0, 0);
    }else{
      glColor3f(0.4, .4, .4);
    }

    glBegin(GL_LINES);
     glVertex3f(xmin, i, 0);
     glVertex3f(xmax, i, 0);
    glEnd();
  }

}

void drawCurve(Point TabPointsOfCurve[], long nbPoints){
  
  glBegin(GL_LINE_STRIP);
  for(int i=0; i<nbPoints; ++i){
    glVertex3f(TabPointsOfCurve[i].getX(), TabPointsOfCurve[i].getY(), TabPointsOfCurve[i].getZ());
  }
  glEnd();
}

void drawQuad(Point p1,Point p2,Point p3,Point p4)
{
	glBegin(GL_POLYGON);
		glVertex3f(p1.getX(),p1.getY(),p1.getZ());
		glVertex3f(p2.getX(),p2.getY(),p2.getZ());
		glVertex3f(p3.getX(),p3.getY(),p3.getZ());
		glVertex3f(p4.getX(),p4.getY(),p4.getZ());
	glEnd();
}

void drawTriangle(Point p1,Point p2,Point p3)
{
  glBegin(GL_TRIANGLES);
    glVertex3f(p1.getX(),p1.getY(),p1.getZ());
    glVertex3f(p2.getX(),p2.getY(),p2.getZ());
    glVertex3f(p3.getX(),p3.getY(),p3.getZ());
  glEnd();
}

double distance(Point p1,Point p2)
{
	return sqrt(pow(p1.getX()-p2.getX(),2)+pow(p1.getY()-p2.getY(),2)+pow(p1.getZ()-p2.getZ(),2));
}


