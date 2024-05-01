#ifndef TAULER_H
#define TAULER_H

#include "Figura.h"
#include <iostream>
//#include "Punt.h"

const int N_FILES = 8;
const int N_COLUMNES = 8;
const int POS_INICIAL_X = 1;
const int POS_INICIAL_Y = 3;
const int MAX_FILA = N_FILES;
const int MAX_COL = N_COLUMNES;

class Tauler
{
public:
	Tauler();
	Tauler(ColorFigura color, int cursorX, int cursorY);

	void setCursorX(int x) { m_cursor.setX(x); };
	void setCursorY(int y) { m_cursor.setY(y); };
	void setCellOnIndex(int fila, int columna, ColorFigura num) { m_tauler[fila][columna] = num; }


	void moveUpCursor() { m_cursor.decX(); };
	void moveDownCursor() { m_cursor.incX(); };
	void moveRightCursor() { m_cursor.incY(); };
	void moveLeftCursor() { m_cursor.decY(); };

	ColorFigura getCellOnIndex(int fila, int columna) const { return m_tauler[fila][columna]; };
	int getCursorX() { return m_cursor.getX(); };
	int getCursorY() { return m_cursor.getY(); };
private:
	ColorFigura m_tauler[N_FILES][N_COLUMNES];
	Punt m_cursor;
};

#endif