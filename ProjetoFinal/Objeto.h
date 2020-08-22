#ifndef Objeto_h
#define Objeto_h
using namespace std;

class Objeto
{
public:
	Objeto();
	virtual ~Objeto();
	virtual int MEM() {return 0;}
};
#endif

