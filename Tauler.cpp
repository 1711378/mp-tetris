#include <iostream>
#include "Tauler.h"

using namespace std;

Tauler::Tauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			/*
			if ((j == 0 || j == N_COLUMNES - 1) || (i == N_FILES - 1))
			{
				m_tauler[i][j] = COLOR_GRIS;
			}
			else
			{
				m_tauler[i][j] = COLOR_NEGRE;
			}
			*/
			m_tauler[i][j] = COLOR_NEGRE;
		}
	}

	m_cursor.setX(POS_INICIAL_X);
	m_cursor.setY(POS_INICIAL_Y);
}

Tauler::Tauler(ColorFigura color, int cursorX, int cursorY)
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			/*
			if ((j == 0 || j == N_COLUMNES - 1) || (i == N_FILES - 1))
			{
				m_tauler[i][j] = COLOR_GRIS;
			}
			else
			{
				m_tauler[i][j] = color;
			}
			*/
			m_tauler[i][j] = color;
		}
	}

	m_cursor.setX(cursorX);
	m_cursor.setY(cursorY);
}

void Tauler::mostraTauler() const
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			if (i == m_cursor.getX() && j == m_cursor.getY())
			{
				cout << "X ";
			}
			else
			{
				cout << m_tauler[i][j] << " ";
			}
				
		}
		cout << endl;
	}
}