#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include <windows.h>

Partida::Partida()
{
    srand(time(NULL));
    m_score = 0;
    m_level = 1;
    m_temps = 0;
}

void Partida::imprimirTauler()
{
    ColorFigura colorTauler;

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
}

void Partida::inicialitza(bool testMode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    m_score = 0;
    m_level = 1;
    m_temps = 0;
    m_joc.vaciarTauler();

    if (testMode)
    {
        m_joc.inicialitza(fitxerInicial);

        int array[MAX_VALORS_NODE] = {};
        ifstream fitxer;

        // Leemos los movimientos del archivo y los guardamos en la cola
        fitxer.open(fitxerMoviments);

        if (fitxer.is_open())
        {
            fitxer >> array[0];

            while (!fitxer.eof())
            {
                movsTest.afegeix(array, 1);
                fitxer >> array[0];
            }

            fitxer.close();
        }

        // Leemos las figuras del archivo y las guardamos en la cola
        fitxer.open(fitxerFigures);

        if (fitxer.is_open())
        {

            while (!fitxer.eof())
            {
                for (int i = 0; i < MAX_VALORS_NODE; i++)
                    fitxer >> array[i];

                figurasTest.afegeix(array, MAX_VALORS_NODE);
            }

            fitxer.close();
        }
    }
    else
    {
        // Generamos una figura aleatoria
        m_joc.generarFig(randomNumber(1, NUM_DE_FIGURES), POS_INICIAL_X, POS_INICIAL_Y, 0);

        m_joc.DWFigura(false);
    }
}

bool Partida::actualitza(bool testMode, double deltaTime, const string& fitxerFigures, const string& fitxerMoviments)
{
    int returnColisio = -1;
    bool final = false;
    double speed;

    // Dibujamos el estado actual del tauler
    imprimirTauler();
    
    // Bajamos la figura automaticamente dependiendo de la velocidad del nivel
    m_temps += deltaTime;
    speed = (3.0 / (m_level + 2));
    if (m_temps > speed && !testMode)
    {
        returnColisio = m_joc.baixaFigura();
        m_temps = 0.0;
    }

    // Leemos los movimientos de las figuras dependiendo del modo de juego
    if (!testMode)
    {
        if (Keyboard_GetKeyTrg(KEYBOARD_UP) || Keyboard_GetKeyTrg(KEYBOARD_W))
            m_joc.giraFigura(GIR_HORARI);

        if (Keyboard_GetKeyTrg(KEYBOARD_DOWN) || Keyboard_GetKeyTrg(KEYBOARD_S))
            m_joc.giraFigura(GIR_ANTI_HORARI);

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
    }
    else
    {
        TipusTecla currentMov = NO_TECLA;

        if (movsTest.size())
        {
            currentMov = static_cast<TipusTecla>(movsTest.getPrimer()->getValor(0));
            movsTest.treu();
        }

        switch (currentMov)
        {
        case TECLA_ESQUERRA:
            m_joc.mouFigura(-1);
            break;
        case TECLA_DRETA:
            m_joc.mouFigura(1);
            break;
        case TECLA_AMUNT:
            m_joc.giraFigura(GIR_HORARI);
            break;
        case TECLA_ABAIX:
            m_joc.giraFigura(GIR_ANTI_HORARI);
            break;
        case TECLA_ESPAI:
            returnColisio = m_joc.baixaFigura();
            m_score++;
            break;
        case TECLA_ESCAPE:
            m_score += N_FILES - m_joc.getCursor().getY();
            returnColisio = m_joc.hardDrop();
            break;
        default:
            break;
        }

        if (movsTest.empty())
        {
            final = true;
        }

        Sleep(1000);
    }
    

    
    // Detectamos si una figura ha colisionado
    if (returnColisio != -1)
    {
        // Calculamos el aumento de puntuacion
        if (returnColisio == 0)
        {
            m_score += 500;
        }
        else
        {
            m_score += 100 * returnColisio;
        }
        m_score += m_level * 10;

        if (!testMode)
        {
            // Generamos una nueva figura aleatoria
            m_joc.generarFig(randomNumber(1, NUM_DE_FIGURES), POS_INICIAL_X, POS_INICIAL_Y, 0);
        }
        else
        {
            // Leemos la siguiente figura de la cola
            int fig, posCol, posFil, gir;

            fig = figurasTest.getPrimer()->getValor(0);
            posFil = figurasTest.getPrimer()->getValor(1);
            posCol = figurasTest.getPrimer()->getValor(2);
            gir = figurasTest.getPrimer()->getValor(3);

            figurasTest.treu();

            // Guardando la nueva figura en la matriz de Joc y poniendo el cursor en la posicion
            // solicitada en la cola
            m_joc.generarFig(fig, posFil, posCol, gir);
            
            m_joc.setCursor(posFil + m_joc.getCentre().getX() - 1, 
                            posCol + m_joc.getCentre().getY() - 1);

            // Giramos la figura en caso de que sea necesario
            if (gir != 0)
            {
                Figura copiaFigura = m_joc.getFigura();
                for (int i = 0; i < gir; i++)
                {
                    m_joc.calculGir(GIR_HORARI, copiaFigura);
                }

                m_joc.setFigura(copiaFigura);
            }
        }

        // Comprobamos si la figura colisiona nada mas ser invocada
        final = m_joc.detectCollision(m_joc.getFigura());

        m_joc.DWFigura(false);
    }

    // Calculamos si se han acumulado suficientes puntos para subir de nivel
    if (m_score >= 600 * (m_level * m_level + 2 * m_level + 1)
        && m_level < 25)
    {
        m_level++;
    }

    if (final)
    {
        // Pausamos la musica
        mciSendString("stop mp3", NULL, 0, NULL);

        // Imprimimos mensaje de final de partida
        GraphicManager::getInstance()->drawSprite(GRAFIC_TRANSPARENT_FONS, 0, 0, false);
        string msgFin = "GAME OVER";
        GraphicManager::getInstance()->drawFont(RETRO_FONT_RED_30, SCREEN_SIZE_X / 8.0, SCREEN_SIZE_Y / 2.0, 1.4, msgFin);

        if (testMode)
        {
            // Vaciamos las colas de figuras y movimientos
            figurasTest.clear();
            movsTest.clear();
        }
    }

    return final;
}
