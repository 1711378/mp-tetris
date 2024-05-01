#include "joc.h"

/*int randomNumber(int numMin, int numMax)
{
	int numAleatori;

	numAleatori = numMin + (rand() % (numMax - numMin + 1));

	return numAleatori;
}
*/

Joc::Joc() //Constructor Joc
{
	m_tauler.setCursorX(POS_INICIAL_X); //Assigna cursor X a posición inicial
	m_tauler.setCursorY(POS_INICIAL_Y); //Assigna cursor Y a posición inicial
}

Joc::Joc(TipusFigura forma)
{		
	m_tauler.setCursorX(POS_INICIAL_X);
	m_tauler.setCursorY(POS_INICIAL_Y);

	m_figuraActual.inicialitzaMatriuFigura(forma);
}

bool Joc::mouFigura(int direccio)
{
	DireccioMov dirX;
	
	// Convertimos el parámetro direccio al tipo enum DireccioMov
	if (direccio == 1)
	{
		dirX = MOV_DRE;
	}
	else if (direccio == -1)
	{
		dirX = MOV_ESQ;
	}

	bool figureMoved = false, isColliding = false;
	bool currentCell, leftCell;
	ColorFigura taulerCell;
	int i = 0, j = 0;

	if (dirX == MOV_ESQ)
	{
		while (!isColliding && i < m_figuraActual.getMida())
		{
			while (!isColliding && j < m_figuraActual.getMida())
			{
				currentCell = m_figuraActual.getMatriuOnIndex(i, j);
				leftCell = m_figuraActual.getMatriuOnIndex(i, j - 1);
				taulerCell = m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i, m_tauler.getCursorY() - m_figuraActual.getCentreY() + j - 1);


				// Revisamos si las celdas de la primera columna de la matriz figuraActual están ocupadas por 1s
				// y si en las celdas equivalentes de la matriz tauler hay otras figuras
				if (j == 0 && currentCell && taulerCell ||
					(m_tauler.getCursorY() - m_figuraActual.getCentreY() + j == 0 && currentCell)) // o si alguna parte de la figura se está saliendo de la matriz tauler
				{
					isColliding = true;
				}
				else if (currentCell && !(leftCell) && taulerCell) // Confirmamos si hay un 1 en la celda de la matriz figuraActual,
						// que no tenga otro 1 a su izquierda
					 // y si la celda equivalente en la matriz tauler está ocupada
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
	int nFilesCompletadas = 0;

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
	else
		nFilesCompletadas = eliminaFiles();


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
			for (int x = i; x > 0; x--)
			{
				for (int y = N_COLUMNES - 1; y >= 0; y--)
					m_tauler.setCellOnIndex(x, y, m_tauler.getCellOnIndex(x - 1, y));
			}

			// Llenamos de 0 todas las casillas de la primera fila
			for (int y = N_COLUMNES - 1; y >= 0; y--)
				m_tauler.setCellOnIndex(0, y, COLOR_NEGRE);

			i++;
		}

		// Reinicializamos las variables para volver a empezar
		j = N_COLUMNES - 1;
		filaLlena = true;
	}

	return filesEliminades;

}

void Joc::calculGir(DireccioGir direccio, Figura& figura)
{
	if (direccio == GIR_HORARI && figura.getForma() != FIGURA_O)
	{
		// Girar la figura
		figura.matriuTrasposta();
		figura.matriuColumnesCanviades();

		// Recalcular el centro de la Figura I
		if (figura.getForma() == FIGURA_I)
		{
			switch (figura.getFormaGir())
			{
			case 0:
				figura.incCentreX();
				m_tauler.moveDownCursor();
				break;
			case 1:
				figura.decCentreY();
				m_tauler.moveLeftCursor();
				break;
			case 2:
				figura.decCentreX();
				m_tauler.moveUpCursor();
				break;
			case 3:
				figura.incCentreY();
				m_tauler.moveRightCursor();
				break;
			default:
				break;
			}
		}

		// Actualizar la forma de giro de la figura
		if (figura.getFormaGir() < 3)
			figura.setFormaGir(figura.getFormaGir() + 1);
		else
			figura.setFormaGir(0);
	}
	else if (direccio == GIR_ANTI_HORARI && figura.getForma() != FIGURA_O)
	{
		// Girar la figura
		figura.matriuColumnesCanviades();
		figura.matriuTrasposta();

		// Recalcular el centro de la Figura I
		if (figura.getForma() == FIGURA_I)
		{
			switch (figura.getFormaGir())
			{
			case 3:
				figura.incCentreX();
				m_tauler.moveDownCursor();
				break;
			case 2:
				figura.incCentreY();
				m_tauler.moveRightCursor();
				break;
			case 1:
				figura.decCentreX();
				m_tauler.moveUpCursor();
				break;
			case 0:
				figura.decCentreY();
				m_tauler.moveLeftCursor();
				break;
			default:
				break;
			}
		}

		// Actualizar la forma de giro de la figura
		if (figura.getFormaGir() > 0)
			figura.setFormaGir(figura.getFormaGir() - 1);
		else
			figura.setFormaGir(3);
	}
	else if (direccio != GIR_ANTI_HORARI && direccio != GIR_HORARI)
	{
		cout << "Error. Valor de giro invalido." << endl;
	}
}

bool Joc::giraFigura(DireccioGir direccio)
{
	bool figureSpinned = false, isColliding = false;
	Figura copiaFiguraGirada;
	int originalCursorX, originalCursorY;
	int i = 0, j = 0;

	// Borramos la figura del tablero en su posicion original
	DWFigura(true); 

	// Hacemos una shallow copy de la figura actual y guardamos los valores originales del cursor del tablero
	copiaFiguraGirada = m_figuraActual; 
	originalCursorX = m_tauler.getCursorX();
	originalCursorY = m_tauler.getCursorY();

	// Giramos la copia de la figura
	calculGir(direccio, copiaFiguraGirada);

	// Comprobamos si la copia girada colisiona con otra figura
	while (!isColliding && i < copiaFiguraGirada.getMida())
	{
		while (!isColliding && j < copiaFiguraGirada.getMida())
		{
			if (m_tauler.getCursorY() - copiaFiguraGirada.getCentreY() + j < 0 ||
				m_tauler.getCursorY() - copiaFiguraGirada.getCentreY() + j >= N_COLUMNES ||
				(copiaFiguraGirada.getMatriuOnIndex(i, j) &&
				 m_tauler.getCellOnIndex(m_tauler.getCursorX() - copiaFiguraGirada.getCentreX() + i,
				 m_tauler.getCursorY() - copiaFiguraGirada.getCentreY() + j)))
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

	// Si no hay colisiones, igualamos la figura actual a la copia girada
	if (!isColliding)
	{
		figureSpinned = true;
		m_figuraActual = copiaFiguraGirada;
	}
	else
	{
		// Si hay colisiones, regresamos el cursor a su valor original
		m_tauler.setCursorX(originalCursorX);
		m_tauler.setCursorY(originalCursorY);
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
		int formaFigura, color, x, y, formaGir, i = 0, j = 0;
		Punt centre;

		fitxer >> formaFigura >> x >> y >> formaGir;

		DWFigura(true);
		m_figuraActual.setFormaGir(0);
		m_figuraActual.inicialitzaMatriuFigura(static_cast<TipusFigura>(formaFigura));
		m_tauler.setCursorX(x + m_figuraActual.getCentreX() - 1);
		m_tauler.setCursorY(y + m_figuraActual.getCentreY() - 1);

		if (formaGir != 0)
		{
			for (int i = 0; i < formaGir; i++)
			{
				calculGir(GIR_HORARI, m_figuraActual);
			}
		}

		i = 0, j = 0;

		fitxer >> color;
		while (!fitxer.eof() && i < N_FILES)
		{
			while (j < N_COLUMNES)
			{
				m_tauler.setCellOnIndex(i, j, static_cast<ColorFigura>(color));
				fitxer >> color;
				j++;
			}
			j = 0;
			i++;
		}

		fitxer.close();

		DWFigura(false);
	}
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;

	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
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