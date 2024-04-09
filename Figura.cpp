#include <iostream>
#include "Figura.h"

using namespace std;

//void matriuTrasposta(bool matriu[][MAX_MIDA_FIGURA], int mida)
//{
//	for (int i = 0; i < mida; i++)
//	{
//		for (int j = i + 1; j < mida; j++)
//		{
//			if (i != j && matriu[i][j] != matriu[j][i])
//			{
//				swap(matriu[i][j], matriu[j][i]);
//			}
//		}
//	}
//}

//void matriuColumnesCanviades(bool matriu[][MAX_MIDA_FIGURA], int mida)
//{
//	for (int j = 0; j < mida / 2; j++)
//	{
//		for (int i = 0; i < mida; i++)
//		{
//			if (matriu[i][mida - 1 - j] != matriu[mida - 1 - j][i])
//			{
//				swap(matriu[i][mida - 1 - j], matriu[mida - 1 - j][i]);
//			}
//		}
//	}
//}

void Figura::matriuColumnesCanviades()
{
	for (int j = 0; j < m_mida / 2; j++)
	{
		for (int i = 0; i < m_mida; i++)
		{
			if (m_matriu[i][j] != m_matriu[i][m_mida - 1 - j])
			{
				swap(m_matriu[i][j], m_matriu[i][m_mida - 1 - j]);
			}
		}
	}
}

void Figura::matriuTrasposta()
{
	for (int i = 0; i < m_mida; i++)
	{
		for (int j = i + 1; j < m_mida; j++)
		{
			if (i != j && m_matriu[i][j] != m_matriu[j][i])
			{
				swap(m_matriu[i][j], m_matriu[j][i]);
			}
		}
	}
}

void Figura::inicialitzaMatriuFigura(TipusFigura forma)
{
	m_mida = 4; // Inicializamos por defecto al valor más grande. Lo cambiaremos luego dependiendo de la forma

	// Inicializamos toda la matriz a 0
	for (int i = 0; i < MAX_MIDA_FIGURA; i++)
	{
		for (int j = 0; j < MAX_MIDA_FIGURA; j++)
		{
			m_matriu[i][j] = 0;
		}
	}

	// Asignamos la medida de la matriz y el centro de la figura dependiendo de la forma
	switch (forma)
	{
	case FIGURA_I:
		m_centre.setY(2);
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
}

Figura::Figura()
{
	m_forma = NO_FIGURA;
	m_color = NO_COLOR;
	m_formaGir = 0;
	// Inicializamos por defecto los siguientes atributos a los valores más comunes:
	m_centre.setX(1);
	m_centre.setY(1);
	m_mida = 3;

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
	m_centre.setX(1);
	m_centre.setY(1);
	
	inicialitzaMatriuFigura(forma);
}

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

