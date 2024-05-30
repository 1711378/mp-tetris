//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Tetris.h"
#include "./InfoJoc.h"


int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);

    Tetris tetris;
    //Partida game;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    char userOption;
    bool testMode = false, gameOver = false, fin = false;
    int puntuacio;

    do
    {
        cout << "    MENU PRINCIPAL    " << endl;
        cout << "======================" << endl;
        cout << "1. Joc en mode normal" << endl;
        cout << "2. Joc en mode test" << endl;
        cout << "3. Mostrar puntuacions" << endl;
        cout << "4. Sortir" << endl;
        cin >> userOption;

        switch (userOption)
        {
        case '1':
            testMode = false;
            gameOver = false;
            fin = false;
            puntuacio = 0;

            tetris.inicialitza(testMode, 
                "./data/Games/partida.txt",
                "./data/Games/puntuacions.txt", 
                "./data/Games/figures.txt", 
                "./data/Games/moviments.txt");
            do
            {
                //Mostrem la finestra grafica
                pantalla.show();

                LAST = NOW;
                NOW = SDL_GetPerformanceCounter();
                deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

                // Captura tots els events de ratolí i teclat de l'ultim cicle
                pantalla.processEvents();

                if (!fin)
                {
                    puntuacio = tetris.juga(pantalla, deltaTime, testMode, fin,
                        "./data/Games/figures.txt",
                        "./data/Games/moviments.txt");

                    // Actualitza la pantalla
                    pantalla.update();
                }
                else
                {
                    if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
                    {
                        fin = false;
                        gameOver = true;
                        pantalla.close();
                    }
                }
                //Sortim del bucle si pressionem ESC
            } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !gameOver);

            if (!fin)
            {
                pantalla.close();
            }

            // Actualiza las puntuaciones
            tetris.actualitzaPuntuacions("./data/Games/puntuacions.txt", puntuacio);
            tetris.vaciaListPuntuacions();
            
            break;
        case '2':
            testMode = true;

            tetris.inicialitza(testMode,
                "./data/Games/partida.txt",
                "./data/Games/puntuacions.txt",
                "./data/Games/figures.txt",
                "./data/Games/moviments.txt");
            do
            {
                //Mostrem la finestra grafica
                pantalla.show();

                LAST = NOW;
                NOW = SDL_GetPerformanceCounter();
                deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

                // Captura tots els events de ratolí i teclat de l'ultim cicle
                pantalla.processEvents();


                puntuacio = tetris.juga(pantalla, deltaTime, testMode, gameOver, 
                    "./data/Games/figures.txt",
                    "./data/Games/moviments.txt");

                // Actualitza la pantalla
                pantalla.update();

            } while (!gameOver);

            gameOver = false;

            break;
        case '3':
            tetris.mostraPuntuacions("./data/Games/puntuacions.txt");
            break;
        case '4':
            cout << "Sortint" << endl;
            break;
        default:
            cout << "Error. Opcio invàlida." << endl;
            break;
        }

        

         
    } while (userOption != '4');
    

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

