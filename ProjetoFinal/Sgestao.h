#ifndef Sgestao_h
#define Sgestao_h
#include "Libraries.h"
#include "Modelo.h"
using namespace std;

enum Tipo {VERTICE, ARESTA, FACE};
class SGestao
{
	list<Modelo *> LModelos;
	Modelo *SearchNome(const string &fich) {
		for (list<Modelo *>::iterator itera=LModelos.begin(); itera!=LModelos.end(); itera++) {
			if ((*itera)->GETNome()==fich){
			return *itera;}
		}
		return NULL;
	}
public:
	SGestao();
	~SGestao();
	bool Load(const string &fich);
	int Count(Tipo T);
	double aModelo(const string &fich);
	Face *FaceMaiorArea(const string &fich);
	int nIntersect(Vertice A, Vertice B);
	void EscreverXML(const string &fich, const string &fich_xml);
	Face *FaceMaiorCurvatura(const string &fich);
	int Memoria(const string &fich);
	int MemoriaTotal();
	Modelo *ModeloMaisMemoria();
	bool RemoverModelo(const string &fich);
	bool Envolvente(const string &fich, Vertice &min, Vertice &max);
};
#endif