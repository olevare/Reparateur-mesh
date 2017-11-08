#include "Octree.h"
#include "math.h"
#include <iostream>

Octree::Octree( ){}

Octree::Octree(Point c, double l)
{
	center = c;
	lenght = l;
	drawValue = 1;					
}

Octree::~Octree()
{
}

void Octree::DrawVoxel()
{
  	glBegin(GL_QUADS);

  	//face
    glVertex3f(center.getX(), center.getY(), center.getZ());
    glVertex3f(center.getX(), center.getY() + lenght, center.getZ());
    glVertex3f(center.getX() + lenght, center.getY() + lenght, center.getZ());
    glVertex3f(center.getX() + lenght, center.getY(), center.getZ());

    //dessous
    glVertex3f(center.getX(), center.getY(), center.getZ());
    glVertex3f(center.getX(), center.getY(), center.getZ() + lenght);
    glVertex3f(center.getX() + lenght, center.getY(), center.getZ() + lenght);
    glVertex3f(center.getX() + lenght, center.getY(), center.getZ());

    //dessus
    glVertex3f(center.getX(), center.getY(), center.getZ() + lenght);
    glVertex3f(center.getX(), center.getY() + lenght, center.getZ() + lenght);
    glVertex3f(center.getX() + lenght, center.getY() + lenght, center.getZ() + lenght);
    glVertex3f(center.getX() + lenght, center.getY(), center.getZ() + lenght);

    //haut
    glVertex3f(center.getX(), center.getY() + lenght, center.getZ() + lenght);
    glVertex3f(center.getX() + lenght, center.getY() + lenght, center.getZ() + lenght);
    glVertex3f(center.getX() + lenght, center.getY() + lenght, center.getZ());
    glVertex3f(center.getX(), center.getY() + lenght, center.getZ());

    //gauche
    glVertex3f(center.getX(), center.getY(), center.getZ());
    glVertex3f(center.getX(), center.getY(), center.getZ() + lenght);
    glVertex3f(center.getX(), center.getY() + lenght, center.getZ() + lenght);
    glVertex3f(center.getX(), center.getY() + lenght, center.getZ());

    //droite
    glVertex3f(center.getX() + lenght, center.getY(), center.getZ());
    glVertex3f(center.getX() + lenght, center.getY(), center.getZ() + lenght);
    glVertex3f(center.getX() + lenght, center.getY() + lenght, center.getZ() + lenght);
    glVertex3f(center.getX() + lenght, center.getY() + lenght, center.getZ());

	glEnd();
}