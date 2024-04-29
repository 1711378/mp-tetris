#include <iostream>
#include "Joc.h"

using namespace std;

void testDebugging(TipusFigura figura)
{
	char userInput;
	Joc juego(figura);

	juego.escriuTaulerConsola();
	cout << endl;

	cout << "Ingrese una accion. " << endl;
	cin >> userInput;

	while (userInput != 'q')
	{
		switch (userInput)
		{
			case 'w':
				juego.giraFigura(GIR_HORARI);
			break;
			
			case 'a':
				juego.mouFigura(MOV_ESQ);
			break;

			case 's':
				juego.baixaFigura();
			break;

			case 'd':
				juego.mouFigura(MOV_DRE);
			break;

			default:
			break;
		}

		juego.escriuTaulerConsola();
		cout << endl;

		cout << "Ingrese una accion. " << endl;
		cin >> userInput;
	}

	juego.escriuTauler("resultado.txt");
}

int main() {
	/*
	figura figuraprueba(figura_j, color_groc);

	cout << "figura inicial: " << endl;
	figuraprueba.mostrafigura();
	cout << endl;

	cout << "traspuesta de la figura: " << endl;
	figuraprueba.matriutrasposta();
	figuraprueba.mostrafigura();
	cout << endl;

	cout << "columnas invertidas de la figura: " << endl;
	figuraprueba.matriucolumnescanviades();
	figuraprueba.mostrafigura();
	cout << endl;

	joc taulerprueba(figura_z);
	
	cout << "posicion inicial tablero: " << endl;
	taulerprueba.escriutaulerconsola();
	cout << endl;

	cout << "moviendo cursor hacia abajo: " << endl;
	taulerprueba.baixafigura();
	taulerprueba.escriutaulerconsola();
	cout << endl;

	cout << "moviendo cursor hacia los lados: " << endl;
	taulerprueba.moufigura(mov_esq);
	taulerprueba.escriutaulerconsola();
	cout << endl;

	taulerprueba.moufigura(mov_dre);
	taulerprueba.moufigura(mov_dre);
	taulerprueba.escriutaulerconsola();
	cout << endl;

	joc prueba(figura_i);

	cout << "tablero de prueba movimiento: " << endl;
	prueba.escriutaulerconsola();
	cout << endl;

	prueba.inicialitza("pruebainput1.txt");
	prueba.dwfigura(false);
	prueba.escriutaulerconsola();
	prueba.escriutauler("pruebagiro1.txt");
	cout << endl;

	prueba.girafigura(gir_horari);
	prueba.escriutaulerconsola();
	prueba.escriutauler("pruebagiro2.txt");
	cout << endl;

	prueba.baixafigura();
	prueba.escriutaulerconsola();
	prueba.escriutauler("pruebagiro3.txt");
	cout << endl;

	cout << endl;
	*/

	testDebugging(FIGURA_O);
	
	return 0;
}