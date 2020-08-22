#define _CRT_SECURE_NO_WARNINGS
#ifndef Modelo_h
#define Modelo_h
#include "Libraries.h"
#include "Face.h"
#include "Aresta.h"


class Modelo
{
	map<int, Vertice *> MapaVertice;
	map<int, list<Face *>> MapaFaces;
	list<Aresta *> LArestas;
	list<Aresta > L;
	list<Face *> LViz;
	string nome;

	
public:
	Modelo();
	~Modelo();
	int CountA();
	void InsertVertice(string line, int numb);
	void InsertFace(string line, int nFace);
	void MostrarMapaVertice();
	void MostrarListFaces();
	void ValidaAresta(int n1, int n2, int n3);
	bool Ler(const string &fich);
	void MostrarArestas();
	int CountAresta();
	int CountVertice();
	int CountFace();
	double GETArea();
	string GETNome() {return this->nome;}
	Face *MaiorArea();
	int Plano(Vertice A, Vertice B);
	double MaiorCurvatura(Face *f);
	int MemoriaIndividual();
	list<Face*> vizinhos(Face *Face);
	Face *CalcularFaceMaiorCurvatura();
	bool Envolvente(Vertice &min, Vertice &max);
	bool EscreverXMl(const string &fich_xml);
};
#endif 