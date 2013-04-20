#include<iostream>
#include<cstdlib>
//#include<vector>            //do macierzy sąsiedztwa      //walić to, zrobimy to na tablicy
#include<list>              //w końcu działamy na listach c'nie?
#include<time.h>            //do liczb pseudolosowych

using namespace std;



//          DO ZROBIENIA:
//
//  zmodyfikować listę następników aby odwzorowywała graf z macierzy
//  3)  lista krawędzi zapisana jako tabela
//  4)  sortowanie topologiczne (zgodnie z algorytmem przeszukiwania w głąb)
//  5)  i magiczny zegarek mierzący ile to zajmuje
//  6)  pętelka mierząca czas dla 10 wartości "liczba"


//to niestety musi iść pierwsze choć wiem, że to nielogiczne trochę :(
struct vneigh;                                                          //"vertex neighbour" czyli kolejne pozycje na liście następników

//teraz dopiero można zająć się tym co trzeba
struct vertex                                                           //struktura wierzchołka grafu dla listy następników (pierwsza pozycja)
{
    int id;             //"numer" wierzchołka
    vneigh* next;       //wskaźnik na sąsiada
};

//i wracamy do określenia czym jest vneigh
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


        //vector<vector<bool> > graf(liczba,vector<bool>(liczba));      //tworzymy graf jako macierz liczba*liczba; jest to wektor w wektorze

        int **graf = new int*[liczba];                          //tworzymy graf jako macierz liczba*liczba
        for(int x=0;x<liczba;x++)
        {
            graf[x]=new int[liczba];            //jest to dynamiczna tablica
        }

        //zapełnianie macierzy danymi
        for(int i=0;i<liczba;i++)       //rząd
        {
            for(int j=0;j<liczba;j++)   //kolumna
            {
                //graf jest acykliczny jeżeli macierz sąsiedztwa jest górnotrójkątna
                if(i<j)    graf[i][j]=1;       //górny trójkąt ma same 1; dzięki temu graf jest spójny i spełnia warunki gęstości
                else if(i==j)        //dla przekątnej wartości mogą być 0 lub 1
                {
                    graf[i][j]=rand()%2;
                }
                else graf[i][j]=0;      //dla reszty musi być 0
            }
        }

        //wypisywanie grafu na konsoli
        for(int i=0;i<liczba;i++)       //rząd
        {
            for(int j=0;j<liczba;j++)   //kolumna
            {
                cout<<graf[i][j]<<" ";
            }
            cout<<endl;
        }




        //to poniżej do modyfikacji aby odzwierciedlało graf z macierzy
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












        //zwalnianie pamięci
        for (int x=0;x<liczba;x++)          //zwalniamy pamięć po kolumnach tablicy
        delete [] graf[x];

        delete [] graf;                     //i w końcu cały graf
    }


    return 0;
}
