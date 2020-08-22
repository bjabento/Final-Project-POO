#ifndef Face_h
#define Face_h
#include "Libraries.h"
#include "Aresta.h"
#include "Vertice.h"
#include "Objeto.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

class Face: public Objeto
{
	Vertice *Vx;
	Vertice *Vy;
	Vertice *Vz;
	Vertice *normal;
	double area;
public:
	Face();
	~Face();
	void Setarea(double area);
	void SetVy(Vertice *Vy);
	void SetVx(Vertice *Vx);
	void SetVz(Vertice *Vz);
	void Setnormal(double a, double b, double c);
	Vertice* GivVx(); 
	Vertice* GivVy();
	Vertice* GivVz();
	Vertice* Givnormal();
	double Givarea() {return this->area;}
	bool Intersect(Vertice &A, Vertice&B);
	double ponto(double a, double b, double c, double d, double e, double f);
	int MEM();
};
#endif
