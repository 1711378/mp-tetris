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

	cout << "Tablero de prueba movimiento: " << endl;
	prueba.escriuTaulerConsola();
	cout << endl;

	prueba.inicialitza("pruebaInput1.txt");
	prueba.DWFigura(false);
	prueba.escriuTaulerConsola();
	prueba.escriuTauler("pruebaGiro1.txt");
	cout << endl;

	prueba.giraFigura(GIR_HORARI);
	prueba.escriuTaulerConsola();
	prueba.escriuTauler("pruebaGiro2.txt");
	cout << endl;

	prueba.baixaFigura();
	prueba.escriuTaulerConsola();
	prueba.escriuTauler("pruebaGiro3.txt");
	cout << endl;

	cout << endl;
	
	return 0;
}