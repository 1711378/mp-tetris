#ifndef JOC_H
#define JOC_H

#include <iostream>
#include "Tauler.h"

using namespace std;

typedef enum
{
	NO_GIR = 0,
	GIR_HORARI,
	GIR_ANTI_HORARI
} DireccioGir;

typedef enum
{
	NO_DIR = 0,
	MOV_ESQ,
	MOV_DRE
} DireccioMov;

typedef enum
{
	MOV_VERTICAL = 0,
	MOV_HORIZONTAL,
	MOV_GIRO
} TipusDeMov;

class Joc {
public:
	Joc(TipusFigura forma);

	void saveGame(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(DireccioMov dirX);
	int baixaFigura();

	bool canMove(TipusDeMov mov, DireccioGir direccio, DireccioMov dirX);
	void loadGame(const string& nomFitxer);
	void escriuTauler();
private:
	Figura m_figuraActual;
	Tauler m_tauler;
};

#endif