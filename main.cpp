#include<iostream>
#include <cstdlib>
#include<list>              //w końcu działamy na listach c'nie?
#include<time.h>            //do liczb pseudolosowych

using namespace std;



//          DO ZROBIENIA:
//
//      NAJPIERW MA BYĆ MACIERZ SĄSIEDZTWA!!! RESZTĄ SIĘ ZBYTNIO NIE PRZEJMUJ, BO I TAK BĘDZIE TRZEBA JĄ WYWALIĆ/ZMODYFIKOWAĆ
//
//  1)  coś do sprawdzania czy graf jest acykliczny
//  2)  macierz sąsiedztwa
//  3)  lista krawędzi zapisana jako tabela
//  4)  sortowanie topologiczne (zgodnie z algorytmem przeszukiwania w głąb)
//  5)  i magiczny zegarek mierzący ile to zajmuje
//  6)  pętelka mierząca czas dla 10 wartości "liczba"


//to niestety musi iść pierwsze choć wiem, że to nielogiczne trochę :(
struct vneigh;                                                          //"vertex neighbour" czyli kolejne pozycje na liście następników

struct vertex                                                           //struktura wierzchołka grafu dla listy następników (pierwsza pozycja)
{
    int id;             //"numer" wierzchołka
    vneigh* next;       //wskaźnik na sąsiada
};

struct vneigh                                                           //"vertex neighbour" czyli kolejne pozycje na liście następników
{
    vertex* id;         //wskaźnik na numer sąsiada
    vneigh* next;       //wskaźnik na kolejnego sąsiada
};

int main()                                                              //main
{
    srand(NULL);

    int liczba;         //liczba wierzchołków w tworzonym grafie
    bool dalej=true;    //flaga dla pętli programu; jeżeli staje się false to program zostaje przerwany


    while (dalej)       //pętla programu, dzięki temu można wykonać parę operacji bez wielokrotnego włączania programu
    {
        cout<<"Podaj liczbe vertexow grafu"<<endl;      //prosimy użytkownika o liczbę danych
        cin>>liczba;




        //TO POD SPODEM NA PÓŹNIEJ, BO NIE DA SIĘ ZROBIĆ W TEN SPOSÓB GRAFU ACYKLICZNEGO, NAJPIERW MACIERZ
        vertex* pierwszy = new vertex[liczba];       //tworzymy graf "pierwszy" zawierający "liczba" wierzchołków; jest to lista struktur

        for(int i=0;i<liczba;i++)       //zapełniamy graf danymi
        {
            pierwszy[i].id=i;       //każdy wierzchołek dostaje własne id (lecą po kolei od 0)
            pierwszy[i].next=NULL;  //chwilowo nie robimy żadnych krawędzi/łuków
        }

        for(int i=0;i<liczba;i++)       //dodajemy łuki dla każdego wierzchołka       //DO POPRAWY
        {
            pierwszy[i].next= new vneigh;        //tworzymy nową pozycję na liście następników
            //tutaj sprawdzić czy nie wylosował siebie samego
            pierwszy[i].next->id=&pierwszy[rand()%liczba];            //dodajemy pierwszy łuk do losowego wierzchołka,
                                                                        //ten musi być aby graf był spójny
            vneigh* nnext=pierwszy[i].next->next;       //wskaźnik na następnik sąsiada

            for(int j=0;j<( (liczba-1)/2 );j++)     //każdy vertex ma po (liczba/2) łuków
            {
                nnext= new vneigh;        //tworzymy nową pozycję na liście następników
                //tutaj wsadzić sprawdzenie czy połącznia przypadkiem już nie ma
                nnext->id=&pierwszy[rand()%liczba];     //dodajemy łuk do losowego wierzchołka
                nnext=nnext->next;      //zmieniamy wskaźnik na kolejną pozycję
            }
        }
    }


    return 0;
}
