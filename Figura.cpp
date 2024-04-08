#include <iostream>
#include "Figura.h"

using namespace std;

Figura::Figura()
{
	m_forma = NO_FIGURA;
	m_color = NO_COLOR;
	m_formaGir = 0;
	m_mida = 3; // Inicializamos por defecto al valor m�s com�n

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
	m_mida = 4; // Inicializamos por defecto al valor m�s grande. Lo cambiaremos luego dependiendo de la forma

	for (int i = 0; i < MAX_MIDA_FIGURA; i++)
	{
		for (int j = 0; j < MAX_MIDA_FIGURA; j++)
		{
			m_matriu[i][j] = 0;
		}
	}

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
		cout << "Error en Constructor con Par�metros de la clase Figura. Se ha introducido una figura inv�lida." << endl;
		break;
	}

	int counter = 0;
	int positionOnArray = 0;

	for (int i = 0; i < m_mida; i++)
	{
		for (int j = 0; j < m_mida; j++)
		{
			if ((ESTAT_INICIAL_FIGURES[forma][positionOnArray] && counter < BLOCS_PER_FIGURA))
			{
				m_matriu[i][j] = 1;
				counter++;
			}
			else if (!(positionOnArray < BLOCS_PER_FIGURA) && counter < BLOCS_PER_FIGURA)
			{
				m_matriu[i][j] = 1;
				counter++;
			}

			if (positionOnArray < BLOCS_PER_FIGURA)
			{
				positionOnArray++;
			}
		}
	}
};

void Figura::mostraFigura()
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