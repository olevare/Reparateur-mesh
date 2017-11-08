#ifndef OCTREE_H_INCLUDED
#define OCTREE_H_INCLUDED

#include "Point.h"
#include "Fonction.h"



class Octree{

	private:
	
		
		Point center;
		double lenght;
		int drawValue;
		
		float r;
		float g;
		float b;

	public:
		Octree();
		Octree(Point c,double l);
		~Octree();

		void DrawVoxel();
};


#endif
