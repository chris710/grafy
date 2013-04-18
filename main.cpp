#include<iostream>
#include<stdlib>
#include<list>              //w końcu działamy na listach c'nie?

using namespace std;



//          DO ZROBIENIA:
//  1)  coś do sprawdzania czy graf jest acykliczny
//  2)  macierz sąsiedztwa
//  3)  lista krawędzi zapisana jako tabela
//  4)  sortowanie topologiczne (zgodnie z algorytmem przeszukiwania w głąb)
//  5)  i magiczny zegarek mierzący ile to zajmuje
//  6)  pętelka mierząca czas dla 10 wartości "liczba"



struct vertex                                                           //struktura wierzchołka grafu dla listy następników (ta pierwsza pozycja)
{
    int id;             //"numer" wierzchołka
    vertex* next;       //wskaźnik na sąsiada
};

struct vneigh                                                           //"vertex neighbour" czyli kolejne pozycje na liście następników
{
    int id;             //numer sąsiada
    vneigh* next;       //wskaźnik na kolejnego sąsiada
};

int main()                                                              //main
{
    int liczba;         //liczba wierzchołków w tworzonym grafie
    bool dalej=true;    //flaga dla pętli programu; jeżeli staje się false to program zostaje przerwany


    while (dalej)       //pętla programu, dzięki temu można wykonać parę operacji bez wielokrotnego włączania programu
    {
        cout<<"Podaj liczbe vertexow grafu"<<endl;      //prosimy użytkownika o liczę danych
        cin>>liczba;

        vertex pierwszy = new vertex[liczba];       //tworzymy graf "pierwszy" zawierający "liczba" wierzchołków; jest to lista struktur

        for(int i=0;i<liczba;i++)       //zapełniamy graf danymi
        {
            pierwszy[i].id=i;       //każdy wierzchołek dostaje własne id (lecą po kolei od 0)
            pierwszy[i].next=NULL;  //chwilowo nie robimy żadnych krawędzi
        }


    }


    return 0;
}
