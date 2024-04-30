#include <iostream>
#include <stdlib.h> // system() function
#include "Joc.h"

using namespace std;

void testDebugging(TipusFigura figura, const string& nomFitxer, bool showCursor)
{
	char userInput;
	Joc juego(figura);

	if (nomFitxer != "")
	{
		juego.inicialitza(nomFitxer);
	}

	juego.escriuTaulerConsola(showCursor);
	cout << endl;

	cout << "Ingrese una accion: ";
	cin >> userInput;

	while (userInput != 'q' && userInput != 'Q')
	{
		switch (userInput)
		{
			case 'W':
			case 'w':
				juego.giraFigura(GIR_HORARI);
			break;
			
			case 'A':
			case 'a':
				juego.mouFigura(MOV_ESQ);
			break;

			case 'S':
			case 's':
				juego.baixaFigura();
			break;

			case 'D':
			case 'd':
				juego.mouFigura(MOV_DRE);
			break;

			default:
			break;
		}

		system("CLS");
		juego.escriuTaulerConsola(showCursor);
		cout << endl;

		cout << "Ingrese una accion: ";
		cin >> userInput;
		cout << flush;
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

	testDebugging(FIGURA_T, "", true);
	
	return 0;
}