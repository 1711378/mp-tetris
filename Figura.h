#ifndef FIGURA_H
#define FIGURA_H

typedef enum
{
	FIGURA_O = 0,
	FIGURA_I,
	FIGURA_T,
	FIGURA_L,
	FIGURA_J,
	FIGURA_Z,
	FIGURA_S,
	NO_FIGURA
} TipusFigura;

typedef enum
{
	COLOR_NEGRE = 0,
	COLOR_BLAUCEL,
	COLOR_GROC,
	COLOR_MAGENTA,
	COLOR_TARONJA,
	COLOR_BLAUFOSC,
	COLOR_VERD,
	COLOR_VERMELL,
	NO_COLOR
} ColorFigura;

class Figura 
{
public:
	// Constructors & Destructors
	Figura() { m_forma = NO_FIGURA; m_color = NO_COLOR, m_formaGir = 0; };
	Figura(TipusFigura forma, ColorFigura color) { m_forma = forma; m_color = color, m_formaGir = 0; };

	~Figura() {};

	// Modifying Methods
		// Setters
	void setForma(TipusFigura forma) { m_forma = forma; }
	void setColor(ColorFigura color) { m_color = color; }
	void setFormaGir(int formaGir) { m_formaGir = formaGir; }
	


	// Consulting Methods
		// Getters
	TipusFigura getForma() { return m_forma; };
	ColorFigura getColor() { return m_color; };
	int getFormaGir() { return m_formaGir; };

private:
	TipusFigura m_forma;
	ColorFigura m_color;
	int m_formaGir;
};


#endif