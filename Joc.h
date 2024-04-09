#ifndef TAULER.H
#define TAULER.H

#include "Figura.h"

class Joc {
public:
	Joc();
	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);
private:
	Figura m_figuraActual;
	Tauler m_tauler;
};

#endif