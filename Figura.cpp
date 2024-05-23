#include <iostream>
#include "Figura.h"

using namespace std;


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
			if (m_matriu[i][j] != m_matriu[j][i])
			{
				swap(m_matriu[i][j], m_matriu[j][i]);
			}
		}
	}
}

void Figura::inicialitzaMatriuFigura(TipusFigura forma)
{
	m_forma = forma;
	m_mida = 3; // Inicializamos por defecto  la mida y el cetro a los valores más comunes. Lo cambiaremos luego dependiendo de la forma
	m_centre.setX(1);
	m_centre.setY(1);

	// Inicializamos toda la matriz a 0
	for (int i = 0; i < MAX_MIDA_FIGURA; i++)
	{
		for (int j = 0; j < MAX_MIDA_FIGURA; j++)
		{
			m_matriu[i][j] = 0;
		}
	}

	// Asignamos la medida de la matriz, el color y el centro de la figura dependiendo de la forma
	switch (forma)
	{

	case FIGURA_O:
		m_color = COLOR_GROC;
		m_mida = 2;
		break;
	case FIGURA_I:
		m_centre.setY(2);
		m_color = COLOR_BLAUCEL;
		m_mida = 4;
		break;
	case FIGURA_T:
		m_color = COLOR_MAGENTA;
		break;
	case FIGURA_L:
		m_color = COLOR_TARONJA;
		break;
	case FIGURA_J:
		m_color = COLOR_BLAUFOSC;
		break;
	case FIGURA_Z:
		m_color = COLOR_VERMELL;
		break;
	case FIGURA_S:
		m_color = COLOR_VERD;
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
			if ((ESTAT_INICIAL_FIGURES[static_cast<int>(forma) - 1][positionOnInitialArray] && blocksPlaced < BLOCS_PER_FIGURA))
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
