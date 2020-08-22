#ifndef Aresta_h
#define Aresta_h
#include "Objeto.h"
#include "Vertice.h"
using namespace std;
class Aresta: public Objeto
{
	Vertice *Vx;
	Vertice *Vy;
public:
	Aresta(Vertice *Vx, Vertice *Vy);
	~Aresta();
	Vertice *GetVx() {return this->Vx;}
	Vertice *GetVy() {return this->Vy;}
	bool compare(const Aresta& x, const Aresta& y);
	bool operator == (Aresta const& y) {
		if (Vx!=y.Vx){
		return false;}
		return Vy==y.Vy;
	}
	bool operator<(Aresta const& y)
	{
		if (Vx<y.Vx){
		return true;}
		if (Vx>y.Vx){
		return false;}
		if (Vy<y.Vy){
		return true;}
		return false;
	}
	int MEM();
};
#endif