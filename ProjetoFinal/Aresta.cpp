#include "Aresta.h"

Aresta::Aresta(Vertice *Vx, Vertice *Vy)
{
	this->Vx=Vx;
	this->Vy=Vy;
}

int Aresta::MEM() {
	return sizeof(Aresta);
}

Aresta::~Aresta()
{
}