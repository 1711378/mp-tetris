#include <iostream>
#include "Joc.h"

using namespace std;

int main() {

	Figura figuraPrueba(FIGURA_J, COLOR_GROC);

	cout << "Figura inicial: " << endl;
	figuraPrueba.mostraFigura();
	cout << endl;

	cout << "Traspuesta de la figura: " << endl;
	figuraPrueba.matriuTrasposta();
	figuraPrueba.mostraFigura();
	cout << endl;

	cout << "Columnas invertidas de la figura: " << endl;
	figuraPrueba.matriuColumnesCanviades();
	figuraPrueba.mostraFigura();
	cout << endl;

	Joc taulerPrueba(FIGURA_Z);
	
	cout << "Posicion inicial tablero: " << endl;
	taulerPrueba.escriuTaulerConsola();
	cout << endl;

	cout << "Moviendo cursor hacia abajo: " << endl;
	taulerPrueba.baixaFigura();
	taulerPrueba.escriuTaulerConsola();
	cout << endl;

	cout << "Moviendo cursor hacia los lados: " << endl;
	taulerPrueba.mouFigura(MOV_ESQ);
	taulerPrueba.escriuTaulerConsola();
	cout << endl;

	taulerPrueba.mouFigura(MOV_DRE);
	taulerPrueba.mouFigura(MOV_DRE);
	taulerPrueba.escriuTaulerConsola();
	cout << endl;

	Joc prueba(FIGURA_I);
	prueba.giraFigura(GIR_HORARI);

	cout << "Tablero de prueba movimiento: " << endl;
	prueba.escriuTaulerConsola();
	cout << endl;
	//cout << "Mov posible: " << prueba.mouFigura(MOV_ESQ);
	cout << "Mov posible: " << prueba.baixaFigura();
	cout << endl;
	prueba.escriuTaulerConsola();
	
	return 0;
}