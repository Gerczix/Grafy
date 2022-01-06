//
//  graf.hpp
//  Grafy
//
//  Created by Gerard on 22/04/2019.
//  Copyright © 2019 Gerard. All rights reserved.
//

#ifndef graf_hpp
#define graf_hpp

#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

struct sciezka
{
    sciezka * next;
    int wierzcholek;
};

struct Dane {
    int dystans;
    int poprzednik;
    bool odwiedzony;
};

class Graf{
public:
    int ilosc_Krawedzi;
    int ilosc_Wierzcholkow;
    int start;
    int** macierz_Sasiedztwa;
    Dane* macierz_Poprzednikow;
    int SzukajMinimum();
    void Dijkstra();
    void WczytajZPliku();
    void ZapiszDoPliku();
    void Sciezka();
    Graf(){};
    Graf(int iloscWierzcholkow, int wierzcholek_startowy, int gestosc);
};





#endif /* graf_hpp */
