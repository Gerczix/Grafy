//
//  grafLista.hpp
//  Grafy
//
//  Created by Gerard on 05/05/2019.
//  Copyright © 2019 Gerard. All rights reserved.
//

#ifndef grafLista_hpp
#define grafLista_hpp

const int MAXINT = 2147483647;
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "graf.hpp"
using namespace std;
struct lista
{
    lista * next;
    int v,w;                        // numer węzła docelowego i waga krawędzi
};



//d-Dane.dystans
//p-Dane.poprzednik
//QS-Dane.odwiedzony

class Lista{
public:
    int ilosc_Krawedzi;
    int ilosc_Wierzcholkow;
    int start;
    int *stos;
    lista **graf;                 // Tablica list sąsiedztwa
    lista *pw,*rw;
    Dane *macierz_Poprzednikow;
    int sptr;
    
    int SzukajMinimum();
    void Dijkstra();
    void WczytajZPliku();
    Lista(){};
    Lista(int iloscWierzcholkow, int wierzcholek_startowy,int gestosc);
    void Sciezka();
};


#endif /* grafLista_hpp */
