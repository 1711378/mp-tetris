#include "joc.h"

Joc::Joc(TipusFigura forma)
{		
	m_tauler.setCursorX(6);
	m_tauler.setCursorY(5);

	m_figuraActual.inicialitzaMatriuFigura(forma);
}

bool Joc::linearMovementCondition(int i, int j, int iConstantTerm, int jConstantTerm, int marginalVariable, int stopCondition)
{
	bool isColliding = false;
	
	if (marginalVariable == stopCondition &&
		m_figuraActual.getMatriuOnIndex(i, j) &&
		m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + iConstantTerm,
								m_tauler.getCursorY() - m_figuraActual.getCentreY() + j + jConstantTerm) &&
		(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + iConstantTerm) >= N_FILES &&
		 m_tauler.getCursorY() - m_figuraActual.getCentreY() + j + jConstantTerm >= N_COLUMNES)
	{
		isColliding = true;
	}
	else if (m_figuraActual.getMatriuOnIndex(i, j) &&
			!(m_figuraActual.getMatriuOnIndex(i + iConstantTerm, j + jConstantTerm)) &&
			m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + iConstantTerm,
									m_tauler.getCursorY() - m_figuraActual.getCentreY() + j + jConstantTerm))
	{
		isColliding = true;
	}

	return isColliding;
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
			m_tauler.moveLeftCursor();
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
			m_tauler.moveRightCursor();
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
				m_tauler.getCursorX() - m_figuraActual.getCentreX() + i == N_FILES - 1)
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
		m_tauler.moveDownCursor();
	}

	return figureMoved;
}

/*
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
				isColliding = linearMovementCondition(i, j, 0, -1, j, 0);
				j++;
			}
			j = 0;
			i++;
		}

		if (!isColliding)
		{
			figureMoved = true;
			m_tauler.moveLeftCursor();
		}
	}
	else if (dirX == MOV_DRE)
	{
		while (!isColliding && i < m_figuraActual.getMida())
		{
			while (!isColliding && j < m_figuraActual.getMida())
			{
				isColliding = linearMovementCondition(i, j, 0, 1, j, m_figuraActual.getMida() - 1);
				j++;
			}
			j = 0;
			i++;
		}

		if (!isColliding)
		{
			figureMoved = true;
			m_tauler.moveRightCursor();
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
			isColliding = linearMovementCondition(i, j, 1, 0, i, m_figuraActual.getMida() - 1);
			j++;
		}
		j = 0;
		i++;
	}

	if (!isColliding)
	{
		figureMoved = true;
		m_tauler.moveDownCursor();
	}

	return figureMoved;
}
*/

bool Joc::giraFigura(DireccioGir direccio)
{
	bool canSpin = true;

	if (direccio == GIR_HORARI && m_figuraActual.getForma() != FIGURA_O)
	{
		// Girar la figura
		m_figuraActual.matriuTrasposta();
		m_figuraActual.matriuColumnesCanviades();

		// Recalcular el centro de la Figura I
		if (m_figuraActual.getForma() == FIGURA_I)
		{
			switch (m_figuraActual.getFormaGir())
			{
			case 0:
				m_figuraActual.incCentreX();
				m_figuraActual.setFormaGir(1);
				break;
			case 1:
				m_figuraActual.decCentreY();
				m_figuraActual.setFormaGir(2);
				break;
			case 2:
				m_figuraActual.decCentreX();
				m_figuraActual.setFormaGir(3);
				break;
			case 3:
				m_figuraActual.incCentreY();
				m_figuraActual.setFormaGir(0);
				break;
			default:
				break;
			}
		}
	}
	else if (direccio == GIR_ANTI_HORARI && m_figuraActual.getForma() != FIGURA_O)
	{
		// Girar la figura.
		m_figuraActual.matriuColumnesCanviades();
		m_figuraActual.matriuTrasposta();

		// Recalcular el centro de la Figura I
		if (m_figuraActual.getForma() == FIGURA_I)
		{
			switch (m_figuraActual.getFormaGir())
			{
			case 3:
				m_figuraActual.incCentreX();
				m_figuraActual.setFormaGir(2);
				break;
			case 2:
				m_figuraActual.incCentreY();
				m_figuraActual.setFormaGir(1);
				break;
			case 1:
				m_figuraActual.decCentreX();
				m_figuraActual.setFormaGir(0);
				break;
			case 0:
				m_figuraActual.decCentreY();
				m_figuraActual.setFormaGir(3);
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

	return canSpin;
}

void Joc::escriuTaulerConsola()
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
					cout << "X ";
				}
				else
				{
					cout << m_figuraActual.getMatriuOnIndex(i - minX, j - minY) << " ";
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
		fitxer << m_figuraActual.getForma() << m_tauler.getCursorX() << m_tauler.getCursorY() << m_figuraActual.getFormaGir();

		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				fitxer << m_tauler.getCellOnIndex(i, j);
			}
		}

		fitxer.close();
	}
}