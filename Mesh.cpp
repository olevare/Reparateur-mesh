#include "Mesh.h"
#include <iostream>
#include <math.h>
#include <climits>
#include <fstream>
#include <vector>
#include "Fonction.h"


Mesh::Mesh()
{
	nbPoint = 0;
	nbTriangle = 0;
	nbEdge = 0;

	//position des points en x, y et z
	pointsArray = NULL;

	//indice des points de la face
	indiceArray = NULL;

	//normale des sommets
	normalArray = NULL;

	//indice des points des arrètes
	edgesArray = NULL;

	diedreArray = NULL;
}

Mesh::~Mesh()
{
	if(pointsArray)
		delete [] pointsArray;
	if(indiceArray)
		delete [] indiceArray;
	if(normalArray)
		delete [] normalArray;
	if(edgesArray)
		delete [] edgesArray;
	if(diedreArray)
		delete [] diedreArray;
}

bool Mesh::loadOffFile(std::string fileName)
{
	//charge le fichier
	std::ifstream file(fileName.c_str());

	//ouvre le fichier
	if(!file.is_open())
		return false;

	//lis la première ligne
	std::string line;
	getline(file,line);

	//enregistre le nombre de points, de triangles, d'arètes
	file >> nbPoint >> nbTriangle >> nbEdge;

	indiceArray = new int[nbTriangle*3];
	pointsArray = new double[nbPoint*3];

	//pour enregistrer les coordonnées du point
	double x,y,z;

	//pour connaitre la position de la caméra plus tard
	double DBL_MIN = INT_MIN;
	double DBL_MAX = INT_MAX;

	maxVertex = Point(DBL_MIN,DBL_MIN,DBL_MIN);
	minVertex = Point(DBL_MAX,DBL_MAX,DBL_MAX);

	//pour tous les points
	for(int i = 0; i < nbPoint; i++)
	{
		//on enregistre x, y et z
		file >> x >> y >> z;

		pointsArray[i*3] = x;
		pointsArray[i*3+1] = y;
		pointsArray[i*3+2] = z;

		//regarde les coordonnées du points pour la position de la caméra plus tard
		if(x > maxVertex.getX())
			maxVertex.setX(x);
		if(y > maxVertex.getY())
			maxVertex.setY(y);
		if(z > maxVertex.getZ())
			maxVertex.setZ(z);
		if(x < minVertex.getX())
			minVertex.setX(x);
		if(y < minVertex.getY())
			minVertex.setY(y);
		if(z < minVertex.getZ())
			minVertex.setZ(z);
	}

	int nbFaceVertex;

	for(int i = 0; i < nbTriangle; i++)
	{
		file >> nbFaceVertex;

		if(nbFaceVertex != 3)		
			return false;

		file >> indiceArray[i*3] >> indiceArray[i*3+1] >> indiceArray[i*3+2];
	}

	//ferme le fichier
	file.close();

	//pour les normales
	//initNormalVertex();

	return true;
}

void Mesh::initNormalVertex()
{
	if(normalArray)
		delete [] normalArray;

	normalArray = new double[nbPoint*3];

	//initialisation du tableau
	for(int i = 0; i < nbPoint; i++)
	{
		normalArray[i*3] = 0;
		normalArray[i*3+1] = 0;
		normalArray[i*3+2] = 0;
	}

	for(int i = 0; i < nbTriangle; i++)
	{

		Point p1 = Point(pointsArray[indiceArray[i*3]*3],pointsArray[indiceArray[i*3]*3+1],pointsArray[indiceArray[i*3]*3+2]);
		Point p2 = Point(pointsArray[indiceArray[i*3+1]*3],pointsArray[indiceArray[i*3+1]*3+1],pointsArray[indiceArray[i*3+1]*3+2]);
		Point p3 = Point(pointsArray[indiceArray[i*3+2]*3],pointsArray[indiceArray[i*3+2]*3+1],pointsArray[indiceArray[i*3+2]*3+2]);

		Vector v1  = Vector(p2,p1);
		Vector v2  = Vector(p3,p1);

		Vector normal = v1.vectoriel(v2);
		
		Vector BA = Vector(p1,p2);
		Vector u = Vector(p3,p2);

		u.normalize();

		double h = (BA+u).norme() / u.norme();

		double area = distance(p2,p3)*h/2;
		
		//somme des normales des faces contenant le sommet
		normalArray[indiceArray[i*3]*3+0] += normal.getX()*area;
		normalArray[indiceArray[i*3]*3+1] += normal.getY()*area;
		normalArray[indiceArray[i*3]*3+2] += normal.getZ()*area;

		normalArray[indiceArray[i*3+1]*3+0] += normal.getX()*area;
		normalArray[indiceArray[i*3+1]*3+1] += normal.getY()*area;
		normalArray[indiceArray[i*3+1]*3+2] += normal.getZ()*area;

		normalArray[indiceArray[i*3+2]*3+0] += normal.getX()*area;
		normalArray[indiceArray[i*3+2]*3+1] += normal.getY()*area;
		normalArray[indiceArray[i*3+2]*3+2] += normal.getZ()*area;

	}

	//moyenne des normales des faces
	for(int i = 0; i < nbPoint; i++)
	{
		double norme = sqrt(normalArray[i*3]*normalArray[i*3] + normalArray[i*3+1]*normalArray[i*3+1] + normalArray[i*3+2]*normalArray[i*3+2]);

		normalArray[i*3] = normalArray[i*3]/norme;
		normalArray[i*3+1] = normalArray[i*3+1]/norme;
		normalArray[i*3+2] = normalArray[i*3+2]/norme;
	}	

}

void Mesh::initEdgesArray()
{
	if(edgesArray)
		delete []edgesArray;

	nbEdge = nbTriangle + nbPoint - 2;

	edgesArray = new int[nbEdge*2];

	int cursor = 0;

	for(int i = 0; i < nbTriangle; i++)
	{		
		int j;
		bool e1 = false;
		bool e2 = false;
		bool e3 = false;
		
		for(j = 0; j < cursor; j++)
		{
			if(edgesArray[j*2] == indiceArray[i*3] && edgesArray[j*2+1] == indiceArray[i*3+1] || edgesArray[j*2 + 1] == indiceArray[i*3] && edgesArray[j*2]  == indiceArray[i*3+1])
				e1=true;
			
			if(edgesArray[j*2] == indiceArray[i*3] && edgesArray[j*2+1] == indiceArray[i*3+2] || edgesArray[j*2 + 1] == indiceArray[i*3] && edgesArray[j*2]  == indiceArray[i*3+2])
				e2=true;

			if(edgesArray[j*2] == indiceArray[i*3+2] && edgesArray[j*2+1] == indiceArray[i*3+1] || edgesArray[j*2 + 1] == indiceArray[i*3+2] && edgesArray[j*2]  == indiceArray[i*3+1])
				e3=true;
		}
		
		if(!e1)
		{
			edgesArray[cursor*2] = indiceArray[i*3];
			edgesArray[cursor*2+1] = indiceArray[i*3 + 1];
			cursor++;
		}
		if(cursor > nbEdge)
			break;
		if(!e2)
		{
			edgesArray[cursor*2] = indiceArray[i*3];
			edgesArray[cursor*2+1] = indiceArray[i*3 + 2];

			cursor++;
		}
		if(cursor > nbEdge)
			break;
		if(!e3)
		{
			edgesArray[cursor*2] = indiceArray[i*3 + 1];
			edgesArray[cursor*2+1] = indiceArray[i*3 + 2];
			cursor++;
		}
		if(cursor > nbEdge)
			break;
	}
}

void Mesh::initDiedreArray()
{
	initEdgesArray();
	
	if(diedreArray)
		delete [] diedreArray;
	
	diedreArray = new double[nbEdge];	
	
	for(int i = 0; i < nbEdge; i++)
	{		
		int index1 = -1;
		int index2 = -1;
		for(int j = 0; j < nbTriangle; j++)
		{
			if(edgesArray[i*2] == indiceArray[j*3] && edgesArray[i*2+1] == indiceArray[j*3+1] || edgesArray[i*2 + 1] == indiceArray[j*3] && edgesArray[i*2]  == indiceArray[j*3+1]
				|| edgesArray[i*2] == indiceArray[j*3] && edgesArray[i*2+1] == indiceArray[j*3+2] || edgesArray[i*2 + 1] == indiceArray[j*3] && edgesArray[i*2]  == indiceArray[j*3+2]
				|| edgesArray[i*2] == indiceArray[j*3+2] && edgesArray[i*2+1] == indiceArray[j*3+1] || edgesArray[i*2 + 1] == indiceArray[j*3+2] && edgesArray[i*2]  == indiceArray[j*3+1])
			{
				if(index1 == -1)
					index1 = j;
				else
				{
					index2=j;
					break;
				}
			}
		}
		if(index2 == -1)
			diedreArray[i]=0;

		else
		{
			Point p1 = Point(pointsArray[indiceArray[index1*3]*3],pointsArray[indiceArray[index1*3]*3+1],pointsArray[indiceArray[index1*3]*3+2]);
			Point p2 = Point(pointsArray[indiceArray[index1*3+1]*3],pointsArray[indiceArray[index1*3+1]*3+1],pointsArray[indiceArray[index1*3+1]*3+2]);
			Point p3 = Point(pointsArray[indiceArray[index1*3+2]*3],pointsArray[indiceArray[index1*3+2]*3+1],pointsArray[indiceArray[index1*3+2]*3+2]);

			Vector v1  = Vector(p2,p1);
			Vector v2  = Vector(p3,p1);

			Vector normal1 = v1.vectoriel(v2);

			p1 = Point(pointsArray[indiceArray[index2*3]*3],pointsArray[indiceArray[index2*3]*3+1],pointsArray[indiceArray[index2*3]*3+2]);
			p2 = Point(pointsArray[indiceArray[index2*3+1]*3],pointsArray[indiceArray[index2*3+1]*3+1],pointsArray[indiceArray[index2*3+1]*3+2]);
			p3 = Point(pointsArray[indiceArray[index2*3+2]*3],pointsArray[indiceArray[index2*3+2]*3+1],pointsArray[indiceArray[index2*3+2]*3+2]);

			v1  = Vector(p2,p1);
			v2  = Vector(p3,p1);
			Vector normal2 = v1.vectoriel(v2);	

			diedreArray[i] = M_PI - normal1.angle(normal2);
		}	
	}
}

void Mesh::fusion(int point1, int point2)
{	
	//pour tous les triangles
	for(int i = 0; i < nbTriangle*3; i++)
	{
		//si on recontre le point a fusionner on le remplace
		if(indiceArray[i] == point1)
			indiceArray[i] = point2;
	}
}

void Mesh::simplificationParGrille(double size, double res, std::vector<Point> &v)
{
	std::vector<int> c;

	int cpt = 0;
	int max = pow((int)(size*2. / (res*2.)),2);

	//pour tous les X
	for(double i = -size; i < size; i += res*2)
	{
		//pour tous les Y
		for(double j = -size; j < size; j += res*2)
		{
			//compteur pourcentage
			std::cout << 100*cpt/max << "\% \r";
			cpt++;

			//pour tous les Z
			for(double k = -size; k < size; k += res*2)
			{
				//on nettoie le vecteur
				c.clear();

				//pour tous les points
				for(int m = 0; m < nbPoint; m++)
				{
					//si le point se trouve dans le cube
					if(isInCube(i, j, k, res, Point(pointsArray[m*3], pointsArray[m*3+1], pointsArray[m*3+2])))
					{
						//on l'ajoute au vecteur
						c.push_back(m);
					};
				}

				//pour tous les points se trouvant dans le vecteur
				for(int m = 1; m < c.size(); m++)
				{
					//on les fusionne entre eux
					fusion(c[m], c[0]);
				}

				v.push_back(Point(i, j, k));
			}
		}
	}
}

bool Mesh::isInCube(double i, double j, double k, double res, Point pt)
{
	return (i-res <= pt.getX() && pt.getX() <= i+res && j-res <= pt.getY() && pt.getY() <= j+res && 
		k-res <= pt.getZ() && pt.getZ() <= k+res);
}

void Mesh::drawMesh()
{
	//active le tableau de points
	glEnableClientState(GL_VERTEX_ARRAY);

	//active le tableau de normales
    //glEnableClientState(GL_NORMAL_ARRAY);

	//lis le tableau de points
    glVertexPointer(3, GL_DOUBLE, 0, pointsArray);

    //lis le tableau de normales
    //glNormalPointer(GL_DOUBLE, 0, normalArray);
    
    //on trace le maillage
    glDrawElements(GL_TRIANGLES, nbTriangle*3, GL_UNSIGNED_INT, indiceArray);

    //on desactive le tableau de points
	glDisableClientState(GL_VERTEX_ARRAY);

	//on desactive le tableau de normales
    //glDisableClientState(GL_NORMAL_ARRAY);
}

void Mesh::drawEdgesDiedre(double angle)
{
	for(int i = 0; i < nbEdge; i++)
	{
		glLineWidth(8);		
		glColor3f(0.545, 0.000, 0.000);
		if(abs(diedreArray[i] * 180 / M_PI - angle ) < 1 )
			drawLine(Point(pointsArray[edgesArray[i*2]*3], pointsArray[edgesArray[i*2]*3+1], pointsArray[edgesArray[i*2]*3+2]), Point(pointsArray[edgesArray[i*2+1]*3], pointsArray[edgesArray[i*2+1]*3+1], pointsArray[edgesArray[i*2+1]*3+2]));
	}
}