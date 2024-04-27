#include "joc.h"

Joc::Joc(TipusFigura forma)
{		
	m_tauler.setCursorX(4);
	m_tauler.setCursorY(8);

	m_figuraActual.inicialitzaMatriuFigura(forma);
}

bool Joc::movementCondition(int iConstantTerm, int jConstantTerm, int marginalVariable, int stopCondition)
{
	bool isMovPossible = true;
	for (int i = 0; i < m_figuraActual.getMida(); i++)
	{
		for (int j = 0; j < m_figuraActual.getMida(); j++)
		{
			if (marginalVariable == stopCondition &&
				m_figuraActual.getMatriuOnIndex(i, j) &&
				m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + iConstantTerm,
										m_tauler.getCursorY() - m_figuraActual.getCentreY() + j + jConstantTerm))
			{
				isMovPossible = false;
			}
			else if (m_figuraActual.getMatriuOnIndex(i, j) &&
				!(m_figuraActual.getMatriuOnIndex(i + iConstantTerm, j + jConstantTerm)) &&
				m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + iConstantTerm,
										m_tauler.getCursorY() - m_figuraActual.getCentreY() + j + jConstantTerm))
			{
				isMovPossible = false;
			}
		}
	}

	return isMovPossible;
}

bool Joc::canMove(TipusDeMov mov, DireccioGir direccio, DireccioMov dirX) 
{
	bool isMovPossible = true;

	switch (mov)
	{
	case MOV_VERTICAL:
		
		for (int i = 0; i < m_figuraActual.getMida(); i++)
		{
			for (int j = 0; j < m_figuraActual.getMida(); j++)
			{
				if (i == m_figuraActual.getMida() - 1 &&
					m_figuraActual.getMatriuOnIndex(i, j) &&
					m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + 1, 
											m_tauler.getCursorY() - m_figuraActual.getCentreY() + j))
				{
					isMovPossible = false;
				}
				else if (m_figuraActual.getMatriuOnIndex(i, j) && 
						!(m_figuraActual.getMatriuOnIndex(i + 1, j)) && 
						m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + 1, 
												m_tauler.getCursorY() - m_figuraActual.getCentreY() + j))
				{
					isMovPossible = false;
				}
			}
		}
		break;

	case MOV_HORIZONTAL:
		if (dirX == MOV_ESQ)
		{
			for (int i = 0; i < m_figuraActual.getMida(); i++)
			{
				for (int j = 0; j < m_figuraActual.getMida(); j++)
				{
					if (j == 0 &&
						m_figuraActual.getMatriuOnIndex(i, j) &&
						m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i,
												m_tauler.getCursorY() - m_figuraActual.getCentreY() + j - 1))
					{
						isMovPossible = false;
					}
					else if (m_figuraActual.getMatriuOnIndex(i, j) &&
						!(m_figuraActual.getMatriuOnIndex(i, j - 1)) &&
						m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i,
												m_tauler.getCursorY() - m_figuraActual.getCentreY() + j - 1))
					{
						isMovPossible = false;
					}
				}
			}
		}
		else if (dirX == MOV_DRE)
		{
			for (int i = 0; i < m_figuraActual.getMida(); i++)
			{
				for (int j = 0; j < m_figuraActual.getMida(); j++)
				{
					if (j == m_figuraActual.getMida() - 1 &&
						m_figuraActual.getMatriuOnIndex(i, j) &&
						m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i,
												m_tauler.getCursorY() - m_figuraActual.getCentreY() + j + 1))
					{
						isMovPossible = false;
					}
					else if (m_figuraActual.getMatriuOnIndex(i, j) &&
						!(m_figuraActual.getMatriuOnIndex(i, j + 1)) &&
						m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i,
												m_tauler.getCursorY() - m_figuraActual.getCentreY() + j + 1))
					{
						isMovPossible = false;
					}
				}
			}
		}
		
		break;

	case MOV_GIRO:
		if (direccio == GIR_HORARI)
		{

		}
		else if (direccio == GIR_ANTI_HORARI)
		{

		}
		break;

	default:
		cout << "Error. Tipo de movimiento invalido." << endl;
		break;
	}

	return isMovPossible;
}

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
	m_tauler.mostraTauler();
}

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;

	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		TipusFigura formaFigura;
		Punt centre;
		int x, y;
		int formaGir;
		int num;

		fitxer >> formaFigura >> x >> y >> formaGir;

		m_figuraActual.inicialitzaMatriuFigura(formaFigura);
		m_tauler.setCursorX(x);
		m_tauler.setCursorY(y);
		m_figuraActual.setFormaGir(formaGir);
		fitxer >> num;
		while (!fitxer.eof())
		{


		}
	}

}

void Joc::escriuTauler(const string& nomFitxer)
{

}


ifstream& operator>>(ifstream& input, TipusFigura forma)
{
	TipusFigura valorForma;

	input >> valorForma;

	forma = valorForma;

	return input;
}