#ifndef TAULER.H
#define TAULER.H

#include "Figura.h"

class Joc {
public:
	Joc();
	void inicialitza();
	void giraFigura();
	void mouFigura();
	void baixaFigura();
	void escriuTauler();
private:
	Figura m_figuraActual;
};

#endif