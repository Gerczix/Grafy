//
//  graf.cpp
//  Grafy
//
//  Created by Gerard on 22/04/2019.
//  Copyright © 2019 Gerard. All rights reserved.
//

#include "graf.hpp"
int Graf::SzukajMinimum() {
    int min = -1;
    int najmniejszy_Dystans = 2147483647;
    for (int i = 0; i < ilosc_Wierzcholkow; i++) {
        if (!macierz_Poprzednikow[i].odwiedzony && macierz_Poprzednikow[i].dystans < najmniejszy_Dystans) {
            min = i;
            najmniejszy_Dystans = macierz_Poprzednikow[i].dystans;
        }
    }
    return min;
}

void Graf::Dijkstra() {
    macierz_Poprzednikow = new Dane[ilosc_Wierzcholkow];
    
    for (int i = 0; i < ilosc_Wierzcholkow; i++) {
        macierz_Poprzednikow[i].dystans = (i == start) ? 0 : INT_MAX;
        macierz_Poprzednikow[i].odwiedzony = false;
        macierz_Poprzednikow[i].poprzednik = -1;
    }
    
    int u = this->SzukajMinimum();
    while (u != -1) {
        macierz_Poprzednikow[u].odwiedzony = true;
        for (int i = 0; i < ilosc_Wierzcholkow; i++) {
            if (macierz_Sasiedztwa[u][i] > 0 && macierz_Poprzednikow[u].dystans + macierz_Sasiedztwa[u][i] < macierz_Poprzednikow[i].dystans) {
                macierz_Poprzednikow[i].dystans = macierz_Poprzednikow[u].dystans + macierz_Sasiedztwa[u][i];
                macierz_Poprzednikow[i].poprzednik = u;
            }
        }
        u = this->SzukajMinimum();
    }
}

void Graf::WczytajZPliku() {
    int poczatek,koniec,waga;
    
    fstream plik;
    plik.open("/Users/gerard/Uczelnia/PAMSI/Grafy/Grafy/dane.txt", ios::in );
    if(plik.good() == true) {
        plik >>ilosc_Krawedzi;
        cout<<ilosc_Krawedzi;
        plik >>ilosc_Wierzcholkow;
        plik >>start;
        
        macierz_Sasiedztwa = new int*[ilosc_Wierzcholkow];
        for (int i = 0; i < ilosc_Wierzcholkow; i++)
            macierz_Sasiedztwa[i] = new int[ilosc_Wierzcholkow];
        
        for (int i = 0; i < ilosc_Krawedzi; i++)
        {
            plik>>poczatek;
            cout<<"xd";
            plik>>koniec;
            plik>>waga;
            macierz_Sasiedztwa[poczatek][koniec]=waga;
            macierz_Sasiedztwa[koniec][poczatek]=waga;
        }
        
        
        plik.close();
    }
    
}

Graf::Graf(int iloscWierzcholkow, int wierzcholek_startowy,int gestosc) {
    int W1;
    int W2;
    ilosc_Wierzcholkow=iloscWierzcholkow;
    start=wierzcholek_startowy;
    ilosc_Krawedzi=(iloscWierzcholkow-1)*iloscWierzcholkow/2*gestosc/100;
    int waga;
    
    macierz_Sasiedztwa = new int*[ilosc_Wierzcholkow];
    for (int i = 0; i < ilosc_Wierzcholkow; i++)
        macierz_Sasiedztwa[i] = new int[ilosc_Wierzcholkow];
    
    for(int i=0;i<iloscWierzcholkow;i++)
        for(int j=0; j<iloscWierzcholkow;j++)
            macierz_Sasiedztwa[i][j]=0;
    
    int j=0;
    for (int i=0; i< iloscWierzcholkow-1; i++) {
        waga=rand()%10+1;
        macierz_Sasiedztwa[i][i+1]=waga;
        macierz_Sasiedztwa[i+1][i]=waga;
        j++;
    }
    while(j<ilosc_Krawedzi)
    {
        W1=rand()%iloscWierzcholkow;
        W2=rand()%iloscWierzcholkow;
        if(W1!=W2 && macierz_Sasiedztwa[W1][W2]==0)
        {
            waga=rand()%10+1;
            macierz_Sasiedztwa[W1][W2]=waga;
            macierz_Sasiedztwa[W2][W1]=waga;
            j++;
        }
    }
    
}

void Graf::Sciezka(){
    int i;
    fstream plik;
    plik.open("/Users/gerard/Uczelnia/PAMSI/Grafy/Grafy/wynik.txt", ios::out );
    int * Tab = new int[ilosc_Wierzcholkow];
    for(int j=0; j<ilosc_Wierzcholkow; j++)
    {
        Tab[0]=j;
        i=1;
        while(Tab[i-1]!=start) {
            Tab[i]=macierz_Poprzednikow[Tab[i-1]].poprzednik;
            i++;
        }
        //cout<<"xd2";
        if(plik.good() == true) {
            plik << "wierzcholek poczatkowy: "<<start<<"\twierzcholek koncowy: "<<j<<"\tdystans: "<<macierz_Poprzednikow[j].dystans<<" \tsciezka: ";
            while(i>0){
                plik << Tab[i-1]<<" ";
                i--;
                }
        }
        plik <<"\n";
    }
}
