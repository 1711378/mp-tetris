#include "Tetris.h"
#include "InfoJoc.h"

void Tetris::juga(Screen& pantalla, bool testMode)
{
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    bool final = false;

    m_partida.inicialitza(testMode, "", "", "");

    

    do
    {
        //Mostrem la finestra grafica
        pantalla.show();

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();


        final = m_partida.actualitza(testMode, deltaTime);

        // Actualitza la pantalla
        pantalla.update();

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !final);
    // Sortim del bucle si pressionem ESC

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    //SDL_Quit();
}

void Tetris::mostraPuntuacions()
{

}