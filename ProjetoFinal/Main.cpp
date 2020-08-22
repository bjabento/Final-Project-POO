#include "main.h"
using namespace std;

int menu() {
	int OP;
	cout << "1-Ler modelo OBJ" << endl;
	cout << "2-Contar numero de vertices, arestas e faces" << endl;
	cout << "3-Area modelo OBJ" << endl;
	cout << "4-Determinar envolvente OBJ" << endl;
	cout << "5-Total de memória ocupada" << endl;
	cout << "6-Memoria ocupada por um modelo OBJ" << endl;
	cout << "7-Modelo que ocupa mais memoria" << endl;
	cout << "8-Numero de faces intersetadas por uma reta" << endl;
	cout << "9-Remover um modelo OBJ" << endl;
	cout << "10-Gravar em formato XML" << endl;
	cout << "11-Face com maior area de um modelo OBJ" << endl;
	cout << "12-Face com maior curvatura" << endl;
	cout << "0-Sair" << endl;
	cin >> OP;
	return OP;
}

Vertice Inicializar() {
	double x, y, z;
	Vertice V;
	cout << "Insira as coordenadas do vertice" << endl;
	cout << "Coordenada x:" << endl;
	cin >> x;
	cout << "Coordenada y:" << endl;
	cin >> y;
	cout << "Coordenada z:" << endl;
	cin >> z;
	V.addx(x);
	V.addy(y);
	V.addz(z);
	return V;
}

void main()
{
	int OP=menu(), aux=-1;
	string nFich, nm;
	SGestao Sg;
	double area=-1;
	Vertice Vx, Vy;
	int i=0;
	Face *FACE;
	bool FILE;
do {
		switch (OP) {
			case 1: {
				cout << "Insira o nome do ficheiro que pretende abrir:" << endl;
				cin >> nFich;
				FILE = Sg.Load(nFich);
				if (!FILE) cout << "Ficheiro não existe!" << endl;
				break;
			}
			case 2: {
				Sg.Count(Tipo::VERTICE);
				Sg.Count(Tipo::FACE);
				Sg.Count(Tipo::ARESTA);
				break;
			}
			case 3: {
				cout << "Insira o nome do ficheiro que pretende abrir:" << endl;
				cin >> nFich;
				area=Sg.aModelo(nFich);
				if (area==-1) cout << "Ficheiro não existe!" << endl;
				break;
			}
			case 4: {
				cout << "Insira o nome do ficheiro que pretende abrir:" << endl;
				cin >> nFich;
				FILE=Sg.Envolvente(nFich, Vx, Vy);
				if (!FILE) cout << "Ficheiro não existe!" << endl;
				break;
			}
			case 5: {
				Sg.MemoriaTotal();
				break;
			}
			case 6: {
				cout << "Insira o nome do ficheiro que pretende abrir:" << endl;
				cin >> nFich;
				aux=Sg.Memoria(nFich);
				cout << "Memoria ocupada:[" << aux << "]" << endl;
				break;
			}
			case 7: {
				Sg.ModeloMaisMemoria();
				break;
			}
			case 8: {
				cout << "Insira o nome do ficheiro que pretende abrir:" << endl;
				cin >> nFich;
				Vx=Inicializar();
				Vy=Inicializar();
				aux=Sg.nIntersect(Vx, Vy);
				cout << "Faces intersetadas pela reta:[" << aux << "]" << endl;
				break;
			}
			case 9: {
				cout << "Insira o nome do ficheiro que pretende remover:" << endl;
				cin >> nFich;
				FILE=Sg.RemoverModelo(nFich);
				break;
			}
			case 10: {
				cout << "Insira o nome do ficheiro que pretende abrir:" << endl;
				cin >> nFich;
				cout << "Insira o nome do ficheiro que pretende escrever:" << endl;
				cin >> nm;
				Sg.EscreverXML(nFich, nm);
				break;
			}
			case 11: {
				cout << "Insira o nome do ficheiro que pretende abrir:" << endl;
				cin >> nFich;
				if (area==-1) {Sg.aModelo(nFich);}
				FACE=Sg.FaceMaiorArea(nFich);
				if(!FACE) cout << "Ficheiro não existe!" << endl;
				break;
			}
			case 12: {
				cout << "Insira o nome do ficheiro que pretende abrir:" << endl;
				cin >> nFich;
				if (aux==-1) Sg.nIntersect(Vx, Vy);
				FACE= Sg.FaceMaiorCurvatura(nFich);
				if (!FACE) cout << "Ficheiro não existe!" << endl;
				else cout << "Face com maior curvatura:[" << FACE->Givnormal()->getx() << "], ["<< FACE->Givnormal()->gety() << "], ["<< FACE->Givnormal()->getz() << "]" << endl;
				break;
			}
			default: {
				cout << "Opcao nao existe!" << endl;
				break;
			}
		}
	OP=menu();
	} while (OP!=0);
}