#include <iostream>
#include "Vertice.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

Vertice::Vertice()
{
	this->x=0;
	this->y=0;
	this->z=0;
}

Vertice::~Vertice()
{

}

int Vertice::MEM(){
	return sizeof(Vertice);
}

void Vertice::addx(double x){
	this->x=x;
}

void Vertice::addy(double y){
	this->y=y;
}

void Vertice::addz(double z){
	this->z=z;
}

void Vertice::MostraVertice() {
	cout << "x=<" << x << ">y=<" << y << ">z=<" << z << " >" << endl;
}

