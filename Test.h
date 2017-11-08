#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

int planeBoxOverlap(float normal[3],float d, float maxbox[3]);
int triBoxOverlap(float boxcenter[3],float boxhalfsize[3],float triverts[3][3]);

#endif