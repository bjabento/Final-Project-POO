
#define PI 3.14159265

#include "Modelo.h"
using namespace std::chrono;
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

Modelo::Modelo()
{

}

Modelo::~Modelo()
{
	map<int, list<Face *>>::iterator iMapa;
	list<Face *>::iterator iLista;
	for (iMapa = MapaFaces.begin(); iMapa!=MapaFaces.end(); ++iMapa) {
		for (iLista=iMapa->second.begin(); iLista!=iMapa->second.end(); ++iLista) {
			delete (*iLista);
		}
	}
	MapaFaces.clear();
	for (map<int, Vertice * >::iterator i=MapaVertice.begin(); i!=MapaVertice.end(); ++i)
	{
		delete i->second;
	}
	MapaVertice.clear();
	for (list<Aresta*>::iterator j=LArestas.begin(); j!=LArestas.end(); j++)
	{
		delete (*j);
	}
	LArestas.clear();
	L.clear();
}

bool Modelo::Ler(const string &fich) {
	ifstream file(fich);
	if (!file) return false;
	this->nome=fich;
	string line;
	int num=0;
	int numFace=0;
	while (!file.eof())
	{
		getline(file, line);
		if (line[0]=='v')
		{
			InsertVertice(line, ++num);
			
		}
		else if (line[0] == 'f') {
			InsertFace(line, ++numFace);	
		}
	}
	CountA();
	return true;
}

void Modelo::InsertVertice(string line, int num) {
	double x, y, z;
	Vertice *V = new Vertice();
	sscanf_s(line.c_str(), "v %lf %lf %lf", &x, &y, &z); 
	V->addx(x);
	V->addy(y);
	V->addz(z);
	MapaVertice.insert(pair<int, Vertice *>(num, V));
}

void Modelo::InsertFace(string line, int nFace) {

	int aux1=0, aux2=0, aux3=0, n=0, i=0, aux4=0;
	list<Face *> LF;
	istringstream ss(line);
	while (getline(ss, line, ' ')) {
		if (line !="f" && line != " ") {
			if (n==0) {
				aux1=aux3=aux2=stoi(line);
			}
			else {
				aux1=aux2;
				aux2=stoi(line);
				if (i > 0) {
					Face *F = new Face();
					F->SetVy(this->MapaVertice[aux1]);
					F->SetVz(this->MapaVertice[aux2]);
					F->SetVx(this->MapaVertice[aux3]);
					LF.push_back(F);
					ValidaAresta(aux1, aux2, aux3);
				}
				i++;
			}
			n++;
			
		}
	}
	this->MapaFaces[nFace] = LF;
}

void Modelo::MostrarMapaVertice()
{
	for (map<int, Vertice * >::iterator i=MapaVertice.begin(); i!=MapaVertice.end(); ++i)
	{
		cout << i->first << " " << i->second->getx() << " " << i->second->gety() << " " << i->second->getz() << endl;
	}
}

void Modelo::ValidaAresta(int v1, int v2, int v3) {
	Vertice *Vx=this->MapaVertice[v1];	
	Vertice *Vy=this->MapaVertice[v2];
	Vertice *Vz=this->MapaVertice[v3];
	if (Vx < Vy)
		LArestas.push_back(new Aresta(Vx, Vy));
	else
		LArestas.push_back(new Aresta(Vy, Vx));
	if (Vx < Vz)
		LArestas.push_back(new Aresta(Vx, Vz));
	else
		LArestas.push_back(new Aresta(Vz, Vx));
	if (Vy < Vz)
		LArestas.push_back(new Aresta(Vy, Vz));
	else
		LArestas.push_back(new Aresta(Vz, Vy));
	
}

int Modelo::CountA()
{
	for (list<Aresta*>::iterator i=LArestas.begin(); i!=LArestas.end(); i++)
	{
		L.push_back(**i);
	}
	L.sort();
	L.unique();
	return L.size();
}

int Modelo::CountAresta() {
	return L.size();
}

int Modelo::CountFace() {
	return MapaFaces.size();
}

int Modelo::CountVertice() {
	return MapaVertice.size();
}

void Modelo::MostrarListFaces() {
	map<int, list<Face *>>::iterator iMapa;
	list<Face *>::iterator iLista;
	for (iMapa=MapaFaces.begin(); iMapa!=MapaFaces.end(); ++iMapa) {
		for (iLista=iMapa->second.begin(); iLista!=iMapa->second.end(); ++iLista) {
			//cout << " Vx=x=" << (*iLista)->GivVx()->getx() << " Vx=y=" << (*iLista)->GivVx()->gety() << " Vx=z=" << (*iLista)->GivVx()->getz();
			//cout << " Vy=x=" << (*iLista)->GivVy()->getx() << " Vy=y=" << (*iLista)->GivVy()->gety() << " Vy=z=" << (*iLista)->GivVy()->getz();
			//cout << " Vz=x=" << (*iLista)->GivVz()->getx() << " Vz=y=" << (*iLista)->GivVz()->gety() << " Vz=z=" << (*iLista)->GivVz()->getz() << endl;
		}
	}
}


void Modelo::MostrarArestas() {
	for (list<Aresta>::iterator i=L.begin(); i!=L.end(); ++i) {
	}
}

int Modelo::Plano(Vertice A, Vertice B) {
	int aux=0;
	map<int, list<Face *>>::iterator iMapa;
	list<Face *>::iterator iLista;
	for (iMapa=MapaFaces.begin(); iMapa!=MapaFaces.end(); ++iMapa) {
		for (iLista = iMapa->second.begin(); iLista!=iMapa->second.end(); ++iLista) {
			if ((*iLista)->Intersect(A, B)) aux++;
		}
	}
	return aux;
}

double Modelo::GETArea() {
	double a=0, b=0, c=0, d=0, e=0, f=0, aux1, aux2, aux3, AREA=0, aFace=0;
	map<int, list<Face *>>::iterator iMapa;
	list<Face *>::iterator iLista;
	for (iMapa=MapaFaces.begin(); iMapa!=MapaFaces.end(); ++iMapa) {
		for (iLista=iMapa->second.begin(); iLista!=iMapa->second.end(); ++iLista) {
			a = (*iLista)->GivVy()->getx()-(*iLista)->GivVx()->getx();
			b = (*iLista)->GivVy()->gety()-(*iLista)->GivVx()->gety();
			c = (*iLista)->GivVy()->getz()-(*iLista)->GivVx()->getz();
			d = (*iLista)->GivVz()->getx()-(*iLista)->GivVx()->getx();
			e = (*iLista)->GivVz()->gety()-(*iLista)->GivVx()->gety();
			f = (*iLista)->GivVz()->getz()-(*iLista)->GivVx()->getz();
			aux1 = pow((b * f-c * e), 2);
			aux2 = pow((c * d-a * f), 2);
			aux3 = pow((a * e-d * b), 2);
			aFace= (sqrt(aux1+aux2+aux3) / 2);
			(*iLista)->Setarea(aFace);
			AREA+=aFace;
			
		}
	}
	cout << "Area:" << AREA << endl;
	return AREA;
}

Face *Modelo::MaiorArea() {
	map<int, list<Face *>>::iterator iMapa;
	list<Face *>::iterator iLista;
	double MaiorArea=0;
	Face *Maior=NULL;
	for (iMapa=MapaFaces.begin(); iMapa!=MapaFaces.end(); ++iMapa) {
		for (iLista=iMapa->second.begin(); iLista!=iMapa->second.end(); ++iLista) {
			if ((*iLista)->Givarea()>MaiorArea) {
				MaiorArea =(*iLista)->Givarea();
				Maior=(*iLista);
			}
		}
	}
	cout << "Face com maior area:" << Maior->Givarea() << endl;
	return Maior;
}

double Modelo::MaiorCurvatura(Face *F) {
	list<Face*> LV=vizinhos(F);
	Vertice Vx, Vy;
	double CurvaturaTotal=0, Curvatura;
	int countVizinho=0;
	if (F->Givnormal()->getx() <= 0.000001) {
		F->Intersect(Vx, Vy);
	}
	for (list<Face *>::iterator iF = LV.begin(); iF!=LV.end(); iF++)
	{
		Curvatura = F->Givnormal()->getx() * (*iF)->Givnormal()->getx()+F->Givnormal()->gety() * (*iF)->Givnormal()->gety()+F->Givnormal()->getz() * (*iF)->Givnormal()->getz();
		CurvaturaTotal+=((acos(Curvatura) * (180 / PI)));
	}
	return CurvaturaTotal;
}

Face *Modelo::CalcularFaceMaiorCurvatura()
{
	double maiorCurvatura=0;
	Face *F = NULL;
	for (map<int, list<Face *>>::iterator i=MapaFaces.begin(); i!=MapaFaces.end(); i++)
	{
		for (list<Face *>::iterator iF=i->second.begin(); iF!=i->second.end(); iF++)
		{
			if (this->MaiorCurvatura((*iF))>maiorCurvatura) {
				F = (*iF);
				maiorCurvatura=this->MaiorCurvatura(*iF);
			}
		}
	}
	return F;
}

list<Face *>Modelo::vizinhos(Face *P)
{
	list<Face *> LV = {};
	list<int> Lindex = {};
	for (map<int, list<Face *>>::iterator i=MapaFaces.begin(); i!=MapaFaces.end(); i++)
	{
		for (list<Face *>::iterator iF=i->second.begin(); iF!=i->second.end(); iF++)
		{
			if ((*iF)->GivVx()==P->GivVx()||(*iF)->GivVx()==P->GivVy()||(*iF)->GivVx()==P->GivVz())
			{
				if ((*iF)==P) continue;
				if (find(LV.begin(), LV.end(), (*iF))==LV.end()){
				LV.push_front((*iF));}
			}
			if ((*iF)->GivVy()==P->GivVx()||(*iF)->GivVy()==P->GivVy()||(*iF)->GivVy()==P->GivVz())
			{
				if ((*iF)==P) continue;
				if (find(LV.begin(), LV.end(), (*iF))==LV.end()){
				LV.push_front((*iF));}
			}
			if ((*iF)->GivVz()==P->GivVx()||(*iF)->GivVz()==P->GivVy()||(*iF)->GivVz()==P->GivVz())
			{
				if ((*iF)==P) continue;
				if (find(LV.begin(), LV.end(), (*iF))==LV.end()){
				LV.push_front((*iF));}
			}
		}
	}
	return LV;
}


bool Modelo::Envolvente(Vertice &min, Vertice &max) {
	int MAXx, MINx, MAXy, MINy, MAXz, MINz;
	MAXx=MINx=MapaVertice.at(1)->getx();
	MAXy=MINy=MapaVertice.at(1)->gety();
	MAXz=MINz=MapaVertice.at(1)->getz();
	for (map<int, Vertice * >::iterator i=MapaVertice.begin(); i!=MapaVertice.end(); ++i)
	{
		if (i->second->getx()>MAXx) MAXx=i->second->getx();
		if (i->second->gety()>MAXy) MAXy=i->second->gety();
		if (i->second->getz()>MAXz) MAXz=i->second->getz();
		if (i->second->getx()<MINx) MINx=i->second->getx();
		if (i->second->gety()<MINy) MINy=i->second->gety();
		if (i->second->getz()<MINz) MINz=i->second->getz();
	}
	max.addx(MAXx);
	max.addy(MAXy);
	max.addz(MAXz);
	min.addx(MINx);
	min.addy(MINy);
	min.addz(MINz);
	return true;
}

int Modelo::MemoriaIndividual() {
	int mem = 0;
	map<int, list<Face *>>::iterator iMapa;
	list<Face *>::iterator iLista;
	for (iMapa=MapaFaces.begin(); iMapa!=MapaFaces.end(); ++iMapa) {
		for (iLista=iMapa->second.begin(); iLista!=iMapa->second.end(); ++iLista) {
			mem+=(*iLista)->MEM();
		}
	}
	for (map<int, Vertice * >::iterator i=MapaVertice.begin(); i!=MapaVertice.end(); ++i)
	{
		mem+=i->second->MEM();
	}
	for (list<Aresta*>::iterator F=LArestas.begin(); F!=LArestas.end();F++) 
	{
		mem+=(*F)->MEM();
	}
	return mem;
}

bool Modelo::EscreverXMl(const string &fich_xml) {
	cout << "XML escrito em:" << fich_xml << endl;
	ofstream file;
	file.open(fich_xml);
	file << "<Modelo>" << endl;
	file << "\t<NomeModelo>" << this->GETNome() << "</NomeModelo>" << endl;
	file << "\t<TotalVertices>" << this->CountVertice() << "</TotalVertices>" << endl;
	file << "\t<TotalArestas>" << this->CountAresta() << "</TotalVertices>" << endl;
	file << "\t<TotalFaces>" << this->CountFace() << "</TotalVertices>" << endl;
	file << "\t<Vertices>" << endl;
	for (map<int, Vertice *>::iterator i=MapaVertice.begin(); i!=MapaVertice.end(); i++)
	{
		file << "\t\t<Vertice>" << endl;
		file << "\t\t<x>" << i->second->getx() << "</x>" << endl;
		file << "\t\t<y>" << i->second->gety() << "</y>" << endl;
		file << "\t\t<z>" << i->second->getz() << "</z>" << endl;
		file << "\t\t<Vertice>" << endl;
	}
	file << "\t</Vertices>" << endl;
	file << "\t<Arestas>" << endl;
	for (list<Aresta >::iterator i =L.begin(); i!=L.end(); i++)
	{
		file << "\t\t<Aresta>"<< endl;
		file << "\t\t<Vertice1>";
		file << (i)->GetVx()->getx() << ", " << (i)->GetVx()->gety() << ", " << (i)->GetVx()->getz();
		file << "</Vertice1>" << endl;
		file << "\t\t<Vertice2>";
		file << (i)->GetVy()->getx() << ", " << (i)->GetVy()->gety() << ", " << (i)->GetVy()->getz();
		file << "</Vertice2>" << endl;
		file << "\t\t</Aresta>" << endl;
	}
	file << "\t</Arestas>" << endl;
	file << "\t<Faces>" << endl;
	for (map<int, list<Face *>>::iterator i=MapaFaces.begin(); i!=MapaFaces.end(); i++)
	{
		file << "\t\t<Face >" << endl;
		for (list<Face *>::iterator iL=i->second.begin(); iL!=i->second.end(); iL++)
		{
			file << "\t\t<FaceTriangular>" << endl;
			file << "\t\t<Vertice1>" << (*iL)->GivVx()->getx() << ", ";
			file << (*iL)->GivVz()->gety() << ", ";
			file << (*iL)->GivVx()->getz() << "</Vertice1>" << endl;
			file << "\t\t<Vertice2>" << (*iL)->GivVy()->getx() << ", ";
			file << (*iL)->GivVy()->gety() << ", ";
			file << (*iL)->GivVy()->getz() << "</Vertice2>" << endl;
			file << "\t\t<Vertice3>" << (*iL)->GivVz()->getx() << ", ";
			file << (*iL)->GivVz()->gety() << ", ";
			file << (*iL)->GivVz()->getz() << "</Vertice3>" << endl;
			file << "\t\t<FaceTriangular>" << endl;
		}
		file << "\t\t</Face>" << endl;
	}
	file << "</Faces>" << endl;
	file << "</Modelo>" << endl;
	file.close();
	return 1;
}