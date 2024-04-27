#ifndef TAULER_H
#define TAULER_H

#include "Figura.h"
//#include "Punt.h"

const int N_FILES = 9;
const int N_COLUMNES = 10;
const int POS_INICIAL_X = 1;
const int POS_INICIAL_Y = 3;


class Tauler
{
public:
	Tauler();
	Tauler(ColorFigura color, int cursorX, int cursorY);

	void setCursorX(int x) { m_cursor.setX(x); };
	void setCursorY(int y) { m_cursor.setY(y); };
	void setCellOnIndex(int fila, int columna, ColorFigura num) { m_tauler[fila][columna] = num; }

	void moveDownCursor() { m_cursor.incX(); };
	void moveRightCursor() { m_cursor.incY(); };
	void moveLeftCursor() { m_cursor.decY(); };

	int getCellOnIndex(int fila, int columna) const { return m_tauler[fila][columna]; };
	int getCursorX() { return m_cursor.getX(); };
	int getCursorY() { return m_cursor.getY(); };
	void mostraTauler() const;
private:
	ColorFigura m_tauler[N_FILES][N_COLUMNES];
	Punt m_cursor;
};

#endif