#include "Face.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

Face::Face()
{
	this-> Setarea(-1);
	/*this-> SetVx(0);
	this-> SetVy(0);
	this-> SetVz(0);
	this-> Setnormal(0,0,0);*/
}

int Face::MEM(){
	return sizeof(Face);
}

void Face::Setarea(double area){
	this->area;
}

void Face::SetVx(Vertice *Vx){
	this->Vx=Vx;
}

void Face::SetVy(Vertice *Vy){
	this->Vy=Vy;
}

void Face::SetVz(Vertice *Vz){
	this->Vz=Vz;
}

Vertice*  Face::GivVx() {
	return this->Vx;
}

Vertice*  Face::GivVy() {
	return this->Vy;
}

Vertice*  Face::GivVz() {
	return this->Vz;
}

Vertice* Face::Givnormal() {
	return normal;
}

void Face::Setnormal(double a, double b, double c){
	normal->addx(a);
	normal->addy(b);
	normal->addz(c);
}

Face::~Face()
{
}

double Face::ponto(double a, double b, double c, double d, double e, double f) {
	return a * d + b * e + c * f;
}

bool Face::Intersect(Vertice &A, Vertice &B) {
	double a=0, b=0, c=0, d=0, e=0, f=0, wx=0, wy=0, wz=0, D=0, g=0, h=0, i=0, den=0, t=0;
	double i1 = 0, i2 = 0, i3 = 0;
	double Vxnormal=0, Vynormal=0, Vznormal=0;
	g=B.getx()-A.getx(); //(x,y,z) AB->
	h=B.gety()-A.gety();
	i=B.getz()-A.getz();
	a=this->GivVy()->getx()-this->GivVx()->getx(); // (x,y,z) Vx,Vy
	b=this->GivVy()->gety()-this->GivVx()->gety();
	c=this->GivVy()->getz()-this->GivVx()->getz();
	d=this->GivVz()->getx()-this->GivVx()->getx(); // (x,y,z) Vx,Vz
	e=this->GivVz()->gety()-this->GivVx()->gety();
	f=this->GivVz()->getz()-this->GivVx()->getz();
	wx=(b * f-c * e); // (x,y,z) normal->
	wy=(c * d-a * f);
	wz=(a * e-d * b);
	Vxnormal=(wx / sqrt(pow(wx, 2)+pow(wy, 2)+pow(wz, 2))); // (x,y,z) normal-> normalizar
	Vynormal=(wy / sqrt(pow(wx, 2)+pow(wy, 2)+pow(wz, 2)));
	Vznormal=(wz / sqrt(pow(wx, 2)+pow(wy, 2)+pow(wz, 2)));
	this->Setnormal(Vxnormal, Vynormal, Vznormal);
	D=(-wx * this->GivVx()->getx()-wy * this->GivVx()->gety()-wz * this->GivVx()->getz());
	den=( wx * g+wy * h+wz * i);
	float tolerar=0.000001;
	if(fabs(den)<=tolerar) return false;
	t=(-d-wx * A.getx()-wy * A.gety()-wz * A.getz()) / den;
	i1=A.getx()+t * g;
	i2=A.gety()+t * h;
	i3=A.getz()+t * i;
	double vyx=i1-this->GivVx()->getx();
	double vyy=i2-this->GivVx()->gety();
	double vyz=i3-this->GivVx()->getz();
	double dot00=ponto(a, b, c, a, b, c);
	double dot01=ponto(a, b, c, d, e, f);
	double dot02=ponto(a, b, c, vyx, vyy, vyz);
	double dot11=ponto(d, e, f, d, e, f);
	double dot12=ponto(d, e, f, vyx, vyy, vyz);
	double Invertden=1 / (dot00 * dot11-dot01 * dot01);
	double u=(dot11 * dot02-dot01 * dot12) * Invertden;
	double v=(dot00 * dot12-dot01 * dot02) * Invertden;
	if ((u>=0) && (v>=0) && (u+v<=1))
	{
		return true;
	}
	return false;
}


