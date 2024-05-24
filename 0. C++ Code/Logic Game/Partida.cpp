#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"

Partida::Partida()
{
    m_score = 0;
    m_level = 1;
    m_temps = 0;
}

void Partida::inicialitza(bool testMode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    if (testMode)
    {

    }
    else
    {

        

        // Generamos una figura aleatoria
        m_joc.randFig();

        m_joc.DWFigura(false);
    }
}

void Partida::actualitza(bool testMode, double deltaTime)
{
	ColorFigura colorTauler;
    int returnColisio = -1;

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    string msg = "Nivell: " + to_string(m_level) + "    Puntuacio: " + to_string(m_score);
    GraphicManager::getInstance()->drawFont(RETRO_FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 0.5, msg);

    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
			colorTauler = m_joc.getTauler(i, j);

			if (colorTauler != COLOR_NEGRE)
			{
				GraphicManager::getInstance()->drawSprite(static_cast<IMAGE_NAME>(static_cast<int>(colorTauler) + 1),
					POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
			}
                
        }
    }

    m_temps += deltaTime; 
    if (m_temps > 0.5) 
    { 
        returnColisio = m_joc.baixaFigura();
        m_temps = 0.0; 
    }

    

    if (Keyboard_GetKeyTrg(KEYBOARD_UP) || Keyboard_GetKeyTrg(KEYBOARD_W))
        m_joc.giraFigura(GIR_HORARI);

	if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT) || Keyboard_GetKeyTrg(KEYBOARD_D))
		m_joc.mouFigura(1);

	if (Keyboard_GetKeyTrg(KEYBOARD_LEFT) || Keyboard_GetKeyTrg(KEYBOARD_A))
        m_joc.mouFigura(-1);

	if (Keyboard_GetKeyTrg(KEYBOARD_DOWN) || Keyboard_GetKeyTrg(KEYBOARD_S))
        returnColisio = m_joc.baixaFigura();

    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
        returnColisio = m_joc.hardDrop();
    

    if (returnColisio != -1)
    {
        if (returnColisio == 0)
        {
            m_score += 10;
        }
        else
        {
            m_score += 100 * returnColisio;
        }
    }

    m_level = trunc(sqrt((double)m_score / 1000) + 1);
}

