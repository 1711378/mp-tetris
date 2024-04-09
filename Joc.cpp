#include "joc.h"

Joc::Joc(TipusFigura forma)
{
	m_tauler.setCursorX(7);
	m_tauler.setCursorY(3);

	m_figuraActual.inicialitzaMatriuFigura(forma);
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
				if (m_figuraActual.getMatriuOnIndex(i, j) && 
					!(m_figuraActual.getMatriuOnIndex(i + 1, j)) && 
					m_tauler.getCellOnIndex(m_tauler.getCursorX() - m_figuraActual.getCentreX() + i + 1, m_tauler.getCursorY() - m_figuraActual.getCentreX() + j))
				{
					isMovPossible = false;
				}
			}
		}
		break;
	case MOV_HORIZONTAL:
		break;
	case MOV_GIRO:
		break;
	default:
		break;
	}

	return isMovPossible;
}


bool Joc::giraFigura(DireccioGir direccio)
{
	bool canSpin = true;

	if (direccio == GIR_HORARI)
	{
		m_figuraActual.matriuTrasposta();
		m_figuraActual.matriuColumnesCanviades();
	}
	else if (direccio == GIR_ANTI_HORARI)
	{
		m_figuraActual.matriuColumnesCanviades();
		m_figuraActual.matriuTrasposta();
	}
	else
	{
		cout << "Error. Valor de giro invalido." << endl;
	}

	return canSpin;
}

void Joc::escriuTauler()
{
	m_tauler.mostraTauler();
}