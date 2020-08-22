#ifndef Vertice_h
#define Vertice_h
#include "Objeto.h"

class Vertice: public Objeto
{
	double x;
	double y;
	double z;
public:
	Vertice();
	~Vertice();
	double getx() {return this->x;}
	double gety() {return this->y;}
	double getz() {return this->z;}
	void addx(double x);
	void addy(double y);
	void addz(double z);
	void MostraVertice();
	int MEM();
};
#endif