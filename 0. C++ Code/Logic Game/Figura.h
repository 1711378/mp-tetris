#ifndef FIGURA_H
#define FIGURA_H

const int MAX_MIDA_FIGURA = 4;
const int NUM_DE_FIGURES = 7;
const int NUM_DE_COLORS = 10;
const int BLOCS_PER_FIGURA = 4;

#include "Punt.h"
#include "InfoJoc.h"

const bool ESTAT_INICIAL_FIGURES[NUM_DE_FIGURES][BLOCS_PER_FIGURA] =
{
	{1, 1, 1, 1}, // Figura O
	{0, 0, 0, 0}, // Figura I
	{0, 1, 0, 1}, // Figura T
	{0, 0, 1, 1}, // Figura L
	{1, 0, 0, 1}, // Figura J
	{1, 1, 0, 0}, // Figura Z
	{0, 1, 1, 1}  // Figura S
};

typedef enum
{
	GIR_HORARI = 0,
	GIR_ANTI_HORARI
} DireccioGir;

//typedef enum
//{
//	COLOR_NEGRE = 0,
//	COLOR_GROC,
//	COLOR_BLAUCEL,
//	COLOR_MAGENTA,
//	COLOR_TARONJA,
//	COLOR_BLAUFOSC,
//	COLOR_VERMELL,
//	COLOR_VERD,
//	NO_COLOR
//} ColorFigura;
//
//typedef enum
//{
//	NO_FIGURA = 0,
//	FIGURA_O,
//	FIGURA_I,
//	FIGURA_T,
//	FIGURA_L,
//	FIGURA_J,
//	FIGURA_Z,
//	FIGURA_S,
//} TipusFigura;



class Figura 
{
public:
	// Constructors & Destructors
	Figura();
	Figura(TipusFigura forma, ColorFigura color);

	~Figura() {};

	// Modifying Methods
	void matriuTrasposta();
	void matriuColumnesCanviades();
	void inicialitzaMatriuFigura(TipusFigura forma);
		// Setters
	void setForma(TipusFigura forma) { m_forma = forma; };
	void setColor(ColorFigura color) { m_color = color; };
	void setFormaGir(int formaGir) { m_formaGir = formaGir; };
		//Incrementators & decrementators
	void incCentreX() { m_centre.incX();  };
	void incCentreY() { m_centre.incY(); };
	void decCentreX() { m_centre.decX(); };
	void decCentreY() { m_centre.decY(); };

	// Consulting Methods
	void mostraFigura() const;
		// Getters
	TipusFigura getForma() const { return m_forma; };
	ColorFigura getColor() const { return m_color; };
	int getFormaGir() const { return m_formaGir; };
	int getMida() const { return m_mida; };
	bool getMatriuOnIndex(int fila, int columna) const { return m_matriu[fila][columna]; };
	int getCentreX() const { return m_centre.getX(); };
	int getCentreY() const { return m_centre.getY(); };
	Punt getCentre() { return m_centre; };

private:
	TipusFigura m_forma;
	ColorFigura m_color;
	Punt m_centre;
	bool m_matriu[MAX_MIDA_FIGURA][MAX_MIDA_FIGURA];
	int m_mida;
	int m_formaGir;
};




#endif