#include "joc.h"

Joc::Joc() //Constructor Joc
{
	m_tauler.setCursorX(POS_INICIAL_X); //Assigna cursor X a posici�n inicial
	m_tauler.setCursorY(POS_INICIAL_Y); //Assigna cursor Y a posici�n inicial
	m_figuraActual.inicialitzaMatriuFigura(NO_FIGURA);
}

Joc::Joc(TipusFigura forma)
{		
	m_tauler.setCursorX(POS_INICIAL_X);
	m_tauler.setCursorY(POS_INICIAL_Y);

	m_figuraActual.inicialitzaMatriuFigura(forma);
}

bool Joc::detectCollision(const Figura& figura)
{
	bool isColliding = false, currentCell;
	int taulerXCell, taulerYCell, i = 0, j = 0;
	ColorFigura taulerCell;

	// Comprobamos si la figura colisiona o se sale del tablero
	while (!isColliding && i < figura.getMida())
	{
		while (!isColliding && j < figura.getMida())
		{

			//Celda Actual
			currentCell = figura.getMatriuOnIndex(i, j);

			//Componente X celda equivalente tauler
			taulerXCell = m_tauler.getCursorX() - figura.getCentreX() + i;

			//Componente Y celda equivalente tauler
			taulerYCell = m_tauler.getCursorY() - figura.getCentreY() + j;

			if (((taulerXCell < 0 || taulerYCell < 0 || taulerYCell >= N_COLUMNES || taulerXCell >= N_FILES) && currentCell))
			{
				isColliding = true;
			}
			else
			{
				// Celda equivalente en tauler
				taulerCell = m_tauler.getCellOnIndex(taulerXCell, taulerYCell);

				// Revisamos si las celdas de las primeras/�ltimas columnas/filas de la matriz figuraActual se est�n saliendo del tauler
				// o si hay un 1 en la celda de la figuraActual y hay otra figura en la celda equivalente de la matriz tauler
				if (currentCell && taulerCell)
				{
					isColliding = true;
				}
				else
				{
					j++;
				}
			}
		}
		j = 0;
		i++;
	}

	return isColliding;
}

bool Joc::mouFigura(int direccio)
{
	DireccioMov dirX;

	// Convertimos el par�metro direccio al tipo enum DireccioMov
	if (direccio == 1)
	{
		dirX = MOV_DRE;
	}
	else if (direccio == -1)
	{
		dirX = MOV_ESQ;
	}

	bool figureMoved = false, isColliding = false;

	DWFigura(true); // Borramos la figura del tablero en su posicion original

	if (dirX == MOV_ESQ)
	{
		m_tauler.moveLeftCursor(); // Movemos la figura

		isColliding = detectCollision(m_figuraActual);

		if (!isColliding)
		{
			figureMoved = true;
		}
		else
		{
			// Devolvemos la figura a su posicion original
			m_tauler.moveRightCursor();
		}
	}
	else if (dirX == MOV_DRE)
	{
		m_tauler.moveRightCursor(); // Movemos la figura

		isColliding = detectCollision(m_figuraActual);

		if (!isColliding)
		{
			figureMoved = true;
		}
		else
		{
			// Devolvemos la figura a su posicion original
			m_tauler.moveLeftCursor();
		}
	}

	DWFigura(false); // Redibujamos la figura en la posicion resultante

	return figureMoved;
}

int Joc::baixaFigura()
{
	bool figureMoved = false, isColliding = false;
	int nFilesCompletadas = -1;

	DWFigura(true); // Borramos la figura del tablero en su posicion original
	m_tauler.moveDownCursor(); // Movemos la figura

	isColliding = detectCollision(m_figuraActual);

	if (!isColliding)
	{
		figureMoved = true;
		DWFigura(false); // Redibujamos la figura en la posicion resultante
	}
	else
	{
		m_tauler.moveUpCursor();
		DWFigura(false); // Redibujamos la figura en la posicion resultante
		nFilesCompletadas = eliminaFiles();

		// Generamos una nueva figura aleatoria
		//randFig();
		//DWFigura(false);
	}

	return nFilesCompletadas;
}

int Joc::hardDrop()
{
	int collision = baixaFigura();

	while (collision == -1)
	{
		collision = baixaFigura();
	}

	return collision;
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

		// Recalcular el centro de la Figura I y mover el cursor del tauler
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

		// Recalcular el centro de la Figura I  y mover el cursor del tauler
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
	isColliding = detectCollision(copiaFiguraGirada);

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
	ColorFigura color;

	// Determinamos si hay que redibujar o eliminar la figuraActual del tauler
	if (DeleteWrite)
	{
		color = COLOR_NEGRE;
	}
	else
	{
		color = m_figuraActual.getColor();
	}

	for (int i = 0; i < m_figuraActual.getMida(); i++)
	{
		for (int j = 0; j < m_figuraActual.getMida(); j++)
		{
			if (m_figuraActual.getMatriuOnIndex(i, j))
			{
				m_tauler.setCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i, 
				m_tauler.getCursorY() - m_figuraActual.getCentreY() + j, 
				color);
			}
		}
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

		// Leemos datos de la figura a inicializar del fitxer
		fitxer >> formaFigura >> x >> y >> formaGir;

		// Desdibujamos la figura del tauler, en caso de que estuviera dibujada
		DWFigura(true);

		// Guardamos los datos le�dos
		m_figuraActual.setFormaGir(0);
		m_figuraActual.inicialitzaMatriuFigura(static_cast<TipusFigura>(formaFigura));
		m_tauler.setCursorX(x + m_figuraActual.getCentreX() - 1);
		m_tauler.setCursorY(y + m_figuraActual.getCentreY() - 1);

		// Giramos la figura en caso de que sea necesario
		if (formaGir != 0)
		{
			for (int i = 0; i < formaGir; i++)
			{
				calculGir(GIR_HORARI, m_figuraActual);
			}
		}

		// Leemos datos del tauler a inicializar del fitxer
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

int randomNumber(int numMin, int numMax)
{
	int numAleatori;

	numAleatori = numMin + (rand() % (numMax - numMin + 1));

	return numAleatori;
}

void Joc::generarFig(int tipusFigura, int posFil, int posCol, int gir)
{
	TipusFigura numFig = static_cast<TipusFigura>(tipusFigura);
	//cout << endl << "Dentro de randFig()" << endl;
	//cout << "Figura generada: " << numFig << endl;
	m_figuraActual.inicialitzaMatriuFigura(numFig);

	m_tauler.setCursorX(posFil);
	m_tauler.setCursorY(posCol);
}