#include <iostream>
#include "Figura.h"

using namespace std;

Figura::Figura()
{
	m_forma = NO_FIGURA;
	m_color = NO_COLOR;
	m_formaGir = 0;
	m_mida = 3; // Inicializamos por defecto al valor más común

	for (int i = 0; i < MAX_MIDA_FIGURA; i++)
	{
		for (int j = 0; j < MAX_MIDA_FIGURA; j++)
		{
			m_matriu[i][j] = 0;
		}
	}
}

Figura::Figura(TipusFigura forma, ColorFigura color) 
{ 
	m_forma = forma; 
	m_color = color;
	m_formaGir = 0;
	m_mida = 4; // Inicializamos por defecto al valor más grande. Lo cambiaremos luego dependiendo de la forma

	// Inicializamos toda la matriz a 0
	for (int i = 0; i < MAX_MIDA_FIGURA; i++)
	{
		for (int j = 0; j < MAX_MIDA_FIGURA; j++)
		{
			m_matriu[i][j] = 0;
		}
	}

	// Asignamos la medida de la matriz dependiendo de la forma
	switch (forma)
	{
	case FIGURA_I:
		break;
	case FIGURA_O:
		m_mida = 2;
		break;

	case FIGURA_T:
	case FIGURA_L:
	case FIGURA_J:
	case FIGURA_Z:
	case FIGURA_S:
		m_mida = 3;
		break;

	default:
		// Mensaje de error
		cout << "Error en Constructor con Parámetros de la clase Figura. Se ha introducido una figura inválida." << endl;
		break;
	}

	// Ponemos los cuatro bloques de la figura dependiendo de su forma
	int blocksPlaced = 0;
	int positionOnInitialArray = 0;

	for (int i = 0; i < m_mida; i++)
	{
		for (int j = 0; j < m_mida; j++)
		{
			if ((ESTAT_INICIAL_FIGURES[forma][positionOnInitialArray] && blocksPlaced < BLOCS_PER_FIGURA))
			{
				m_matriu[i][j] = 1;
				blocksPlaced++;
			}
			else if (!(positionOnInitialArray < BLOCS_PER_FIGURA) && blocksPlaced < BLOCS_PER_FIGURA)
			{
				m_matriu[i][j] = 1;
				blocksPlaced++;
			}

			if (positionOnInitialArray < BLOCS_PER_FIGURA)
			{
				positionOnInitialArray++;
			}
		}
	}
};

void Figura::mostraFigura() const
{
	for (int i = 0; i < m_mida; i++)
	{
		for (int j = 0; j < m_mida; j++)
		{
			if (m_matriu[i][j])
				cout << m_color << " ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
}