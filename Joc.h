#ifndef JOC_H
#define JOC_H

#include <iostream>
#include "Tauler.h"
#include <fstream>

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

	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(DireccioMov dirX);
	int baixaFigura();
	void DWFigura(bool DeleteWrite); // Delete/Write Figura
	int eliminaFiles();

	bool canMove(TipusDeMov mov, DireccioGir direccio, DireccioMov dirX);
	bool linearMovementCondition(int i, int j, int iConstantTerm, int jConstantTerm, int marginalVariable, int stopCondition);
	void escriuTauler(const string& nomFitxer);
	void escriuTaulerConsola();
private:
	Figura m_figuraActual;
	Tauler m_tauler;
};

#endif