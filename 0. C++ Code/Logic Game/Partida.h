#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "Joc.h"

using namespace std;

class Partida 
{
public:
    Partida();
    void inicialitza(bool testMode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
    void actualitza(bool testMode, double deltaTime);
private:
    Joc m_joc;
    double m_temps;
    int m_score;
    int m_level;
    bool m_testMode;
};

#endif 
