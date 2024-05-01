#ifndef TAULER_H
#define TAULER_H

#include "Figura.h"
#include <iostream>

const int N_FILES = 8;
const int N_COLUMNES = 8;
const int POS_INICIAL_X = 0;
const int POS_INICIAL_Y = 3;
const int MAX_FILA = N_FILES;
const int MAX_COL = N_COLUMNES;

class Tauler
{
public:
	//Constructors
	Tauler();
	Tauler(ColorFigura color, int cursorX, int cursorY);

	// Modifying Methods
		//Setters
	void setCursorX(int x) { m_cursor.setX(x); };
	void setCursorY(int y) { m_cursor.setY(y); };
	void setCellOnIndex(int fila, int columna, ColorFigura num) { m_tauler[fila][columna] = num; }

	// Incrementators & decrementators
	void moveUpCursor() { m_cursor.decX(); };
	void moveDownCursor() { m_cursor.incX(); };
	void moveRightCursor() { m_cursor.incY(); };
	void moveLeftCursor() { m_cursor.decY(); };
	// Consulting Methods
		//Getters
	int getCursorX() { return m_cursor.getX(); };
	int getCursorY() { return m_cursor.getY(); };



	ColorFigura getCellOnIndex(int fila, int columna) const { return m_tauler[fila][columna]; };
private:
	ColorFigura m_tauler[N_FILES][N_COLUMNES];
	Punt m_cursor;
};

#endif