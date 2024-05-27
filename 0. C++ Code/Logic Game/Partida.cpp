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
        m_joc.inicialitza(fitxerInicial);


    }
    else
    {



        // Generamos una figura aleatoria
        m_joc.randFig();

        m_joc.DWFigura(false);
    }
}

bool Partida::actualitza(bool testMode, double deltaTime)
{
    ColorFigura colorTauler;
    int returnColisio = -1;
    bool final = false;
    double speed;


    m_temps += deltaTime;
    speed = (3.0 / (m_level + 2));
    //if (m_temps > (1/sqrt(m_level))) 
    if (m_temps > speed)
    {
        cout << "Velocidad: " << speed << endl;
        returnColisio = m_joc.baixaFigura();
        m_temps = 0.0;
    }



    if (Keyboard_GetKeyTrg(KEYBOARD_UP) || Keyboard_GetKeyTrg(KEYBOARD_W))
        m_joc.giraFigura(GIR_HORARI);

    if (Keyboard_GetKeyTrg(KEYBOARD_DOWN) || Keyboard_GetKeyTrg(KEYBOARD_S))
        m_joc.giraFigura(GIR_HORARI);

    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT) || Keyboard_GetKeyTrg(KEYBOARD_D))
        m_joc.mouFigura(1);

    if (Keyboard_GetKeyTrg(KEYBOARD_LEFT) || Keyboard_GetKeyTrg(KEYBOARD_A))
        m_joc.mouFigura(-1);

    if (Keyboard_GetKeyTrg(KEYBOARD_Z) || Keyboard_GetKeyTrg(KEYBOARD_P))
    {
        returnColisio = m_joc.baixaFigura();
        m_score++;
    }


    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
    {
        m_score += N_FILES - m_joc.getCursor().getY();
        returnColisio = m_joc.hardDrop();
    }



    if (returnColisio != -1)
    {
        if (returnColisio == 0)
        {
            m_score += 5;
        }
        else
        {
            m_score += 100 * returnColisio;
        }
        m_score += m_level * 10;

        m_joc.randFig();

        final = m_joc.detectCollision(m_joc.getFigura());

        m_joc.DWFigura(false);
    }

    //m_level = trunc(sqrt((double)m_score / 1000) + 1);
    if (m_score >= 600 * (m_level * m_level + 2 * m_level + 1)
        && m_level < 25)
    {
        m_level++;
    }


    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    string msgLvl = "Nivell: " + to_string(m_level);
    string msgPunt = "Puntuacio: " + to_string(m_score);
    GraphicManager::getInstance()->drawFont(RETRO_FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 70, 0.5, msgLvl);
    GraphicManager::getInstance()->drawFont(RETRO_FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 0.5, msgPunt);

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

    if (final)
    {
        // Do stuff
        GraphicManager::getInstance()->drawSprite(GRAFIC_TRANSPARENT_FONS, 0, 0, false);
        string msgFin = "GAME OVER";
        GraphicManager::getInstance()->drawFont(RETRO_FONT_RED_30, SCREEN_SIZE_X / 8, SCREEN_SIZE_Y / 2, 1.4, msgFin);
    }


    return final;
}
