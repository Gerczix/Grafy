//
//  grafLista.cpp
//  Grafy
//
//  Created by Gerard on 05/05/2019.
//  Copyright © 2019 Gerard. All rights reserved.
//

#include "grafLista.hpp"

int Lista::SzukajMinimum(){
    int u,j;
    for(j = 0; macierz_Poprzednikow[j].odwiedzony; j++);
    for(u = j++; j < ilosc_Wierzcholkow; j++)
        if(!macierz_Poprzednikow[j].odwiedzony && (macierz_Poprzednikow[j].dystans < macierz_Poprzednikow[u].dystans)) u = j;
    
    macierz_Poprzednikow[u].odwiedzony = true;
    
    return u;
};


void Lista::Dijkstra(){
    for(int i = 0; i < ilosc_Wierzcholkow; i++)
    {

        // Szukamy wierzchołka w Q o najmniejszym koszcie d
        
        int u=this->SzukajMinimum();
        
        // Znaleziony
        // Modyfikujemy odpowiednio wszystkich sąsiadów u, którzy są w Q
        
        for(pw = graf[u]; pw; pw = pw->next){
            
                if(!macierz_Poprzednikow[pw->v].odwiedzony && (macierz_Poprzednikow[pw->v].dystans > macierz_Poprzednikow[u].dystans + pw->w))
                {
                    macierz_Poprzednikow[pw->v].dystans = macierz_Poprzednikow[u].dystans + pw->w;
                    macierz_Poprzednikow[pw->v].poprzednik = u;
                }
        }
    }
};

void Lista::WczytajZPliku() {
    int poczatek,koniec,waga;
  
       // Tablica list sąsiedztwa
    
    fstream plik;
    plik.open("/Users/gerard/Uczelnia/PAMSI/Grafy/Grafy/dane.txt", ios::in );
    if(plik.good() == true) {
        plik >>ilosc_Krawedzi;
        plik >>ilosc_Wierzcholkow;
        plik >>start;
        graf = new lista * [ilosc_Wierzcholkow];    
        
        for(int i=0; i <ilosc_Wierzcholkow; i++)
            graf[i]=NULL;
        
        for (int i = 0; i < ilosc_Krawedzi; i++)
        {
            plik>>poczatek;
            plik>>koniec;
            plik>>waga;
            pw = new lista;             // Tworzymy element listy sąsiedztwa
            pw->v = koniec;                    // Wierzchołek docelowy krawędzi
            pw->w = waga;                    // Waga krawędzi
            pw->next = graf[poczatek];
            graf[poczatek]=pw;
        }
        
        
        plik.close();
    }
}

Lista::Lista(int iloscWierzcholkow, int wierzcholek_startowy,int gestosc) {
    int W1;
    int W2;
    int ** macierz_Sasiedztwa;
    ilosc_Wierzcholkow=iloscWierzcholkow;
    start=wierzcholek_startowy;
    ilosc_Krawedzi=(iloscWierzcholkow-1)*iloscWierzcholkow/2*gestosc/100;
    int waga;
    graf = new lista * [ilosc_Wierzcholkow];
    
    for(int i=0; i <ilosc_Wierzcholkow; i++)
        graf[i]=NULL;
    
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
        pw = new lista;             // Tworzymy element listy sąsiedztwa
        pw->v = i+1;                    // Wierzchołek docelowy krawędzi
        pw->w = waga;                    // Waga krawędzi
        pw->next = graf[i];
        graf[i]=pw;
        
        pw = new lista;             // Tworzymy element listy sąsiedztwa
        pw->v = i;                    // Wierzchołek docelowy krawędzi
        pw->w = waga;                    // Waga krawędzi
        pw->next = graf[i+1];
        graf[i+1]=pw;
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
            pw = new lista;             // Tworzymy element listy sąsiedztwa
            pw->v = W1;                    // Wierzchołek docelowy krawędzi
            pw->w = waga;                    // Waga krawędzi
            pw->next = graf[W2];
            graf[W2]=pw;
            
            pw = new lista;             // Tworzymy element listy sąsiedztwa
            pw->v = W2;                    // Wierzchołek docelowy krawędzi
            pw->w = waga;                    // Waga krawędzi
            pw->next = graf[W1];
            graf[W1]=pw;
            j++;
        }
    }
    macierz_Poprzednikow = new Dane[ilosc_Wierzcholkow];
    for(int i = 0; i <ilosc_Wierzcholkow; i++)
    {
        macierz_Poprzednikow[i].dystans = MAXINT;
        macierz_Poprzednikow[i].poprzednik = -1;
        macierz_Poprzednikow[i].odwiedzony= false;
    }
    macierz_Poprzednikow[start].dystans = 0;
}

void Lista::Sciezka(){
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
