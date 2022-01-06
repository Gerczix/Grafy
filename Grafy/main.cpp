//
//  main.cpp
//  Grafy
//
//  Created by Gerard on 22/04/2019.
//  Copyright © 2019 Gerard. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "graf.hpp"
#include "grafLista.hpp"
using namespace std;

void wypiszdane(int i, Dane d) {
    cout << i << "\t";
    if (!d.odwiedzony) {
        cout << "nieodwiedzony";
    } else {
        if (d.poprzednik == -1)
            cout << "brak";
        else cout << d.poprzednik;
        cout << "\t" << d.dystans;
    }
    cout << endl;
}

int main() {
    srand( (int)time( NULL ) );
    clock_t start,stop,start1,stop1;
    string czy_plik;
    cout<<"czy chcesz wczytać z pliku(tak/nie)?"<<endl;
    cin>>czy_plik;
    
    if(czy_plik=="tak")
    {
        Lista grafL;
        grafL.WczytajZPliku();
        grafL.macierz_Poprzednikow = new Dane[grafL.ilosc_Wierzcholkow];
        grafL.stos = new int [grafL.ilosc_Wierzcholkow];
        grafL.sptr=0;
    
    
        for(int i = 0; i < grafL.ilosc_Wierzcholkow; i++)
        {
            grafL.macierz_Poprzednikow[i].dystans = MAXINT;
            grafL.macierz_Poprzednikow[i].poprzednik = -1;
            grafL.macierz_Poprzednikow[i].odwiedzony= false;
        }
        grafL.macierz_Poprzednikow[grafL.start].dystans = 0;                       // Koszt dojścia v jest zerowy
        grafL.Dijkstra();
        grafL.Sciezka();
        //sciezka stos
        /*for(int i = 0; i < grafL.ilosc_Wierzcholkow; i++)
        {
            cout << i << ": ";
            for(int j = i; j > -1; j = grafL.macierz_Poprzednikow[j].poprzednik) {
                grafL.stos[grafL.sptr++] = j;
            }
            while(grafL.sptr) cout << grafL.stos[--grafL.sptr] << " ";
            cout << "$" << grafL.macierz_Poprzednikow[i].dystans << endl;
        }*/
    }
    else if(czy_plik=="nie"){
        cout<<"lista"<<endl;
        int Wierzcholki[] = {10, 50, 100, 500, 1000};
        int Posortowane[] = {25, 50, 75, 100};
        double czas=0;
        start1 = clock();
        for(int i=0; i<sizeof(Posortowane)/sizeof(int); i++)
            for(int j=0; j<sizeof(Wierzcholki)/sizeof(int); j++) {
                for(int k=0; k<100; k++) {
                    Lista grafL(Wierzcholki[j],0,Posortowane[i]);
                    start = clock();
                    grafL.Dijkstra();
                    stop = clock();
                    grafL.Sciezka();
                    czas += (double)(stop-start)/CLOCKS_PER_SEC;
                }
                czas = czas/100;
                cout<<"Dla wierzcholkow: "<<Wierzcholki[j]<<"\tgestosci: "<<Posortowane[i]<<"%"<< "\tczasu: "<<czas<<endl;
                czas=0;
            }
        stop1 = clock();
        czas = (double)(stop1-start1)/CLOCKS_PER_SEC;
        cout<<"czas wykonywania całego programy wynosił: "<<czas<<" s"<<endl;
        return 0;
    }
    else{
        cout<<"macierz"<<endl;
    int Wierzcholki[] = {10, 50, 100, 500, 1000};
    int Posortowane[] = {25, 50, 75, 100};
    double czas=0;

    
        //graf.WczytajZPliku();
    
    
    start1 = clock();
    for(int i=0; i<sizeof(Posortowane)/sizeof(int); i++)
        for(int j=0; j<sizeof(Wierzcholki)/sizeof(int); j++) {
            for(int k=0; k<100; k++) {
                Graf graf(Wierzcholki[j],0,Posortowane[i]);
                start = clock();
                graf.Dijkstra();
                stop = clock();
                graf.Sciezka();
                czas += (double)(stop-start)/CLOCKS_PER_SEC;
            }
            czas = czas/100;
            cout<<"Dla wierzcholkow: "<<Wierzcholki[j]<<"\tgestosci: "<<Posortowane[i]<<"%"<< "\tczasu: "<<czas<<endl;
            czas=0;
        }
    stop1 = clock();
    czas = (double)(stop1-start1)/CLOCKS_PER_SEC;
    cout<<"czas wykonywania całego programy wynosił: "<<czas<<" s"<<endl;
    return 0;
    }
    
};
//  cout << "Wezel\tPoprz.\tDystans" << endl;
// for (int i = 0; i < graf.ilosc_Wierzcholkow; i++)
//   wypiszdane(i, graf.macierz_Poprzednikow[i]);
