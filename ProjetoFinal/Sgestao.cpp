#include <iostream>
#include <string>
#include "Sgestao.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

SGestao::SGestao()
{

}

SGestao::~SGestao(){
	if (LModelos.size()==0) return;
	for (list<Modelo *>::iterator i=LModelos.begin(); i!=LModelos.end(); ++i) {
	delete (*i);}
}

bool SGestao::Load(const string &fich) {
	bool TRUE;
	Modelo *M=new Modelo();
	TRUE=M->Ler(fich);
	if (TRUE) { 
		LModelos.push_back(M); 
	}
	else
		delete M;
	return true;
}

int SGestao::Count(Tipo T) {
	list<Modelo *>::iterator i=LModelos.begin();
	for (i; i!=LModelos.end(); i++) {
		cout << "O modelo [" << (*i)->GETNome() << "] possui:\n" << endl;
		switch (T)
			{
			case ARESTA: cout << "Arestas: "<< (*i)->CountAresta()<< endl; break;
			case FACE: cout << "Faces: " << (*i)->CountFace() << endl; break;
			case VERTICE: cout << "Vertices: " << (*i)->CountVertice() << endl; break;
			}
	}
	return -1;
}

double SGestao::aModelo(const string &fich) {
	Modelo *M=SearchNome(fich);
	if (M){
		return M->GETArea();}
	return -1;
}

Face *SGestao::FaceMaiorArea(const string &fich) {
	Modelo *M=SearchNome(fich);
	if (M){
	return M->MaiorArea();}
	return NULL;
}

bool SGestao::RemoverModelo(const string &fich) {
	string nome = fich;
	Modelo *M=SearchNome(fich);
	if (M) {
		for (list<Modelo *>::iterator i=LModelos.begin(); i!= LModelos.end(); ++i) {
			if ((*i)->GETNome()==nome) {
				delete (*i);
				LModelos.remove(*i);
				return true;
			}
		}
	}
	return false;
}

int SGestao::nIntersect(Vertice A, Vertice B) {
	int aux1=0, aux2=0;
	for (list<Modelo *>::iterator i=LModelos.begin(); i!=LModelos.end(); ++i) {
		aux2=(*i)->Plano(A, B);
		cout << "O modelo " << (*i)->GETNome() << " tem [" << aux2 << "] faces intersetadas." << endl;
		aux1+=aux2;
	}
	return aux1;
}

Face *SGestao::FaceMaiorCurvatura(const string &fich) {
	Modelo *M=SearchNome(fich);
	if (M) {
		return M->CalcularFaceMaiorCurvatura();
	}
	return NULL;
}

int SGestao::Memoria(const string &fich) {
	Modelo *M=SearchNome(fich);
	if (M) {
		return M->MemoriaIndividual();
	}
	return -1;
}


int SGestao::MemoriaTotal() {
	int mem=0;
	for (list<Modelo *>::iterator i=LModelos.begin(); i!=LModelos.end(); ++i) { 
		mem+=(*i)->MemoriaIndividual();
	}
	cout << "Total de memoria utilizada:[" << mem << "]" << endl;
	return mem;
}

Modelo *SGestao::ModeloMaisMemoria() {
	int mem = 0;
	Modelo *M = NULL;
	for (list<Modelo *>::iterator i=LModelos.begin(); i!=LModelos.end(); ++i) {
		if ((*i)->MemoriaIndividual() > mem) {
			mem = (*i)->MemoriaIndividual();
			M = (*i);
		}
	}
	cout << "O modelo com mais memoria e:[" << M->GETNome() << "]" << endl;
	return M;
}

bool SGestao::Envolvente(const string &fich, Vertice &min, Vertice &max) {
	Modelo *M=SearchNome(fich);
	if (M) {
	return M->Envolvente(min, max);}
	return false;
}


void SGestao::EscreverXML(const string &fich, const string &fich_xml) {
	Modelo *M=SearchNome(fich);
	if (M)
	{
		M->EscreverXMl(fich_xml);
	}
}


