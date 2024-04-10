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

	Tauler taulerPrueba;
	
	cout << "Posicion inicial tablero: " << endl;
	taulerPrueba.mostraTauler();
	cout << endl;

	cout << "Moviendo cursor hacia abajo: " << endl;
	taulerPrueba.moveDownCursor();
	taulerPrueba.mostraTauler();
	cout << endl;

	cout << "Moviendo cursor hacia los lados: " << endl;
	taulerPrueba.moveLeftCursor();
	taulerPrueba.mostraTauler();
	cout << endl;

	taulerPrueba.moveRightCursor();
	taulerPrueba.moveRightCursor();
	taulerPrueba.mostraTauler();
	cout << endl;

	Joc prueba(FIGURA_I);
	prueba.giraFigura(GIR_HORARI);

	prueba.escriuTauler();
	cout << endl;
	cout << "Mov posible: " << prueba.canMove(MOV_HORIZONTAL, NO_GIR, MOV_DRE);
	

	return 0;
}