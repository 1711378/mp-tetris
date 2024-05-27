#ifndef TETRIS_H
#define TETRIS_H

#include "../Graphic Lib/libreria.h"
#include <conio.h>      /* getch */ 
#include "Partida.h"

class Tetris
{
public:
	void inicialitza(bool testMode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
	{
		m_partida.inicialitza(testMode, fitxerInicial, fitxerFigures, fitxerMoviments);
	}
	void juga(Screen& pantalla, double deltaTime, bool testMode, bool& gameOver);
	void mostraPuntuacions();
private:
	Partida m_partida;
};

#endif