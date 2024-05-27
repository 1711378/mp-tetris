#include "Tetris.h"
#include "InfoJoc.h"

void Tetris::juga(Screen& pantalla, double deltaTime, bool testMode, bool& gameOver)
{
    gameOver = m_partida.actualitza(testMode, deltaTime);
}

void Tetris::mostraPuntuacions()
{

}