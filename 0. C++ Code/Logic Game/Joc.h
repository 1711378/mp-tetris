#ifndef JOC_H
#define JOC_H

#include <iostream>
#include "Tauler.h"
#include <fstream>

#include "Figura.h"
#include <string>

using namespace std;

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
	// Constructors
	Joc();
	Joc(TipusFigura forma);

	// Modifying Methods
	void inicialitza(const string& nomFitxer);
	void calculGir(DireccioGir direccio, Figura& figura);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int direccio);
	int baixaFigura();
	int hardDrop();
	void DWFigura(bool DeleteWrite); // Delete/Write Figura
	int eliminaFiles();

	void randFig();

	// Consulting Methods
	ColorFigura getTauler(int fila, int columna) { return m_tauler.getCellOnIndex(fila, columna); };
	Punt getCursor() { return m_tauler.getCursor(); };
	Figura getFigura() { return m_figuraActual; };
	bool detectCollision(const Figura& figura);
	void escriuTauler(const string& nomFitxer);
	void escriuTaulerConsola(bool showCursor);
private:
	Figura m_figuraActual;
	Tauler m_tauler;
};

#endif