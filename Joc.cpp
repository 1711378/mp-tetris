#include "joc.h"

int randomNumber(int numMin, int numMax)
{
	int numAleatori;

	numAleatori = numMin + (rand() % (numMax - numMin + 1));

	return numAleatori;
}

Joc::Joc(TipusFigura forma)
{		
	m_tauler.setCursorX(4);
	m_tauler.setCursorY(5);

	m_figuraActual.inicialitzaMatriuFigura(forma);
}

bool Joc::mouFigura(DireccioMov dirX)
{
	bool figureMoved = false, isColliding = false;
	int i = 0, j = 0;

	if (dirX == MOV_ESQ)
	{
		while (!isColliding && i < m_figuraActual.getMida())
		{
			while (!isColliding && j < m_figuraActual.getMida())
			{
				if (j == 0 &&
					m_figuraActual.getMatriuOnIndex(i, j) &&
					m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i,
											m_tauler.getCursorY() - m_figuraActual.getCentreY() + j - 1) ||
					(m_tauler.getCursorY() - m_figuraActual.getCentreY() + j == 0 && m_figuraActual.getMatriuOnIndex(i, j)))
				{
					isColliding = true;
				}
				else if (m_figuraActual.getMatriuOnIndex(i, j) &&
					!(m_figuraActual.getMatriuOnIndex(i, j - 1)) &&
					m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i,
											m_tauler.getCursorY() - m_figuraActual.getCentreY() + j - 1))
				{
					isColliding = true;
				}
				j++;
			}
			j = 0;
			i++;
		}

		if (!isColliding)
		{
			figureMoved = true;
			DWFigura(true); // Borramos la figura del tablero en su posicion original
			m_tauler.moveLeftCursor(); // Movemos la figura
			DWFigura(false); // Redibujamos la figura en su nueva posicion
		}
	}
	else if (dirX == MOV_DRE)
	{
		while (!isColliding && i < m_figuraActual.getMida())
		{
			while (!isColliding && j < m_figuraActual.getMida())
			{
				if (j == m_figuraActual.getMida() - 1 &&
					m_figuraActual.getMatriuOnIndex(i, j) &&
					m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i,
											m_tauler.getCursorY() - m_figuraActual.getCentreY() + j + 1) ||
					(m_tauler.getCursorY() - m_figuraActual.getCentreY() + j == N_COLUMNES - 1 && m_figuraActual.getMatriuOnIndex(i, j)))
				{
					isColliding = true;
				}
				else if (m_figuraActual.getMatriuOnIndex(i, j) &&
					!(m_figuraActual.getMatriuOnIndex(i, j + 1)) &&
					m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i,
											m_tauler.getCursorY() - m_figuraActual.getCentreY() + j + 1))
				{
					isColliding = true;
				}
				j++;
			}
			j = 0;
			i++;
		}

		if (!isColliding)
		{
			figureMoved = true;
			DWFigura(true); // Borramos la figura del tablero en su posicion original
			m_tauler.moveRightCursor(); // Movemos la figura
			DWFigura(false); // Redibujamos la figura en su nueva posicion
		}
	}

	return figureMoved;
}

int Joc::baixaFigura()
{
	bool figureMoved = false, isColliding = false;
	int i = 0, j = 0;

	while (!isColliding && i < m_figuraActual.getMida())
	{
		while (!isColliding && j < m_figuraActual.getMida())
		{
			if (i == m_figuraActual.getMida() - 1 &&
				m_figuraActual.getMatriuOnIndex(i, j) &&
				m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + 1,
					m_tauler.getCursorY() - m_figuraActual.getCentreY() + j) ||
				(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i == N_FILES - 1 && m_figuraActual.getMatriuOnIndex(i, j)))
			{
				isColliding = true;
			}
			else if (m_figuraActual.getMatriuOnIndex(i, j) &&
				!(m_figuraActual.getMatriuOnIndex(i + 1, j)) &&
				m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + 1,
					m_tauler.getCursorY() - m_figuraActual.getCentreY() + j))
			{
				isColliding = true;
			}
			j++;
		}
		j = 0;
		i++;
	}

	if (!isColliding)
	{
		figureMoved = true;
		DWFigura(true); // Borramos la figura del tablero en su posicion original
		m_tauler.moveDownCursor(); // Movemos la figura
		DWFigura(false); // Redibujamos la figura en su nueva posicion
	}

	return figureMoved;
}

int Joc::eliminaFiles()
{
	bool filaLlena = true;
	int filesEliminades = 0, j = N_COLUMNES - 1;

	// Revisamos todas las casillas del Tauler
	for (int i = N_FILES - 1; i >= 0; i--)
	{
		while (j >= 0 && filaLlena)
		{
			// Si hay una sola casilla vacia en una fila, salimos del bucle while y revisamos la siguiente fila
			if (!m_tauler.getCellOnIndex(i, j))
				filaLlena = false;
			else
				j--;
		}

		// Si, despues de completar el while, no hemos encontrado ninguna casilla vacia, eliminamos la fila i
		if (filaLlena)
		{
			filesEliminades++;

			// Desplazamos todas las casillas una fila hacia abajo excepto las de la primera fila
			for (int x = N_COLUMNES - 1; x >= 0; x--)
			{
				for (int y = i; y > 0; y--)
					m_tauler.setCellOnIndex(y, x, m_tauler.getCellOnIndex(y + 1, x));
			}

			// Llenamos de 0 todas las casillas de la primera fila
			for (int x = N_COLUMNES - 1; x >= 0; x--)
				m_tauler.setCellOnIndex(0, x, COLOR_NEGRE);
		}

		// Reinicializamos la j para volver a empezar
		j = N_COLUMNES - 1;
	}

	return filesEliminades;

}

bool Joc::giraFigura(DireccioGir direccio)
{
	bool figureSpinned = false, isColliding = false;
	Figura copiaFiguraGirada;
	int i = 0, j = 0;

	// Borramos la figura del tablero en su posicion original
	DWFigura(true); 

	// Hacemos una shallow copy de la figura actual
	copiaFiguraGirada = m_figuraActual; 

	if (direccio == GIR_HORARI && copiaFiguraGirada.getForma() != FIGURA_O)
	{
		// Girar la copia de la figura
		copiaFiguraGirada.matriuTrasposta();
		copiaFiguraGirada.matriuColumnesCanviades();

		// Recalcular el centro de la Figura I
		if (copiaFiguraGirada.getForma() == FIGURA_I)
		{
			switch (copiaFiguraGirada.getFormaGir())
			{
			case 0:
				copiaFiguraGirada.incCentreX();
				copiaFiguraGirada.setFormaGir(1);
				break;
			case 1:
				copiaFiguraGirada.decCentreY();
				copiaFiguraGirada.setFormaGir(2);
				break;
			case 2:
				copiaFiguraGirada.decCentreX();
				copiaFiguraGirada.setFormaGir(3);
				break;
			case 3:
				copiaFiguraGirada.incCentreY();
				copiaFiguraGirada.setFormaGir(0);
				break;
			default:
				break;
			}
		}
	}
	else if (direccio == GIR_ANTI_HORARI && copiaFiguraGirada.getForma() != FIGURA_O)
	{
		// Girar la copia de la figura
		copiaFiguraGirada.matriuColumnesCanviades();
		copiaFiguraGirada.matriuTrasposta();

		// Recalcular el centro de la Figura I
		if (copiaFiguraGirada.getForma() == FIGURA_I)
		{
			switch (copiaFiguraGirada.getFormaGir())
			{
			case 3:
				copiaFiguraGirada.incCentreX();
				copiaFiguraGirada.setFormaGir(2);
				break;
			case 2:
				copiaFiguraGirada.incCentreY();
				copiaFiguraGirada.setFormaGir(1);
				break;
			case 1:
				copiaFiguraGirada.decCentreX();
				copiaFiguraGirada.setFormaGir(0);
				break;
			case 0:
				copiaFiguraGirada.decCentreY();
				copiaFiguraGirada.setFormaGir(3);
				break;
			default:
				break;
			}
		}
	}
	else if (direccio != GIR_ANTI_HORARI && direccio != GIR_HORARI)
	{
		cout << "Error. Valor de giro invalido." << endl;
	}

	// Comprobamos si la copia girada colisiona con otra figura
	while (!isColliding && i < copiaFiguraGirada.getMida())
	{
		while (!isColliding && j < copiaFiguraGirada.getMida())
		{
			if (copiaFiguraGirada.getMatriuOnIndex(i, j) && 
				m_tauler.getCellOnIndex(m_tauler.getCursorX() - copiaFiguraGirada.getCentreX() + i,
										m_tauler.getCursorY() - copiaFiguraGirada.getCentreY() + j))
			{
				isColliding = true;
			}
			else
			{
				j++;
			}
		}
		j = 0;
		i++;
	}

	if (!isColliding)
	{
		figureSpinned = true;

		// Igualamos la figura actual a la copia girada
		m_figuraActual = copiaFiguraGirada;
	}

	// Redibujamos la figura, independientemente de los cambios
	DWFigura(false); 

	return figureSpinned;
}

void Joc::DWFigura(bool DeleteWrite)
{
	int minX, minY, maxX, maxY;
	ColorFigura color;

	if (DeleteWrite)
	{
		color = COLOR_NEGRE;
	}
	else
	{
		color = m_figuraActual.getColor();
	}

	minX = m_tauler.getCursorX() - m_figuraActual.getCentreX();
	minY = m_tauler.getCursorY() - m_figuraActual.getCentreY();
	maxX = minX + m_figuraActual.getMida() - 1;
	maxY = minY + m_figuraActual.getMida() - 1;

	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			if ((i >= minX && i <= maxX) && (j >= minY && j <= maxY))
			{
				if (m_figuraActual.getMatriuOnIndex(i - minX, j - minY))
				{
					m_tauler.setCellOnIndex(i, j, color);
				}
			}
		}
	}
}

void Joc::escriuTaulerConsola(bool showCursor)
{
	int minX, minY, maxX, maxY;

	minX = m_tauler.getCursorX() - m_figuraActual.getCentreX();
	minY = m_tauler.getCursorY() - m_figuraActual.getCentreY();
	maxX = minX + m_figuraActual.getMida() - 1;
	maxY = minY + m_figuraActual.getMida() - 1;

	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			if ((i >= minX && i <= maxX) && (j >= minY && j <= maxY))
			{
				if (i == m_tauler.getCursorX() && j == m_tauler.getCursorY())
				{
					if (showCursor)
					{
						cout << "X ";
					}
					else
					{
						cout << m_figuraActual.getColor() << " ";
					}
				}
				else if (m_figuraActual.getMatriuOnIndex(i - minX, j - minY))
				{
					cout << m_figuraActual.getColor() << " ";
				}
				else
				{
					cout << m_tauler.getCellOnIndex(i, j) << " ";
				}
			}
			else
			{
				cout << m_tauler.getCellOnIndex(i, j) << " ";
			}
		}
		cout << endl;
	}
}

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;

	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		Punt centre;
		int formaFigura, color, x, y, formaGir, i = 0, j = 0;

		fitxer >> formaFigura >> x >> y >> formaGir;

		m_figuraActual.inicialitzaMatriuFigura(static_cast<TipusFigura>(formaFigura));
		m_tauler.setCursorX(x);
		m_tauler.setCursorY(y);
		m_figuraActual.setFormaGir(formaGir);

		fitxer >> color;
		while (!fitxer.eof() && i < N_FILES)
		{
			while (!fitxer.eof() && j < N_COLUMNES)
			{
				m_tauler.setCellOnIndex(i, j, static_cast<ColorFigura>(color));
				fitxer >> color;
				j++;
			}
			j = 0;
			i++;
		}

		fitxer.close();
	}
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;

	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		fitxer << m_figuraActual.getForma() << " " << m_tauler.getCursorX() << " " << m_tauler.getCursorY() << " " << m_figuraActual.getFormaGir() << endl;

		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				fitxer << m_tauler.getCellOnIndex(i, j);
				if (j < N_COLUMNES - 1)
				{
					fitxer << " ";
				}
			}
			if (i < N_FILES - 1)
			{
				fitxer << endl;
			}
		}

		fitxer.close();
	}
}