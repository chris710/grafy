#include<iostream>
#include<cstdlib>
//#include<vector>            //do macierzy sąsiedztwa      //walić to, zrobimy to na tablicy
#include<list>              //w końcu działamy na listach c'nie?
#include<time.h>            //do liczb pseudolosowych

using namespace std;



//          DO ZROBIENIA:
//
//  wyświetlać listę następników
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
    vertex* id;         //wskaźnik na sąsiada
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

        ////////////////////////////////////////////////////////
        //      MACIERZ SĄSIEDZTWA
        ////////////////////////////////////////////////////////

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
                //graf jest acykliczny i skierowany jeżeli macierz sąsiedztwa jest górnotrójkątna
                if(i<j)    graf[i][j]=1;       //górny trójkąt ma same 1; dzięki temu graf jest spójny i spełnia warunki gęstości
                else if(i==j)        //dla przekątnej wartości mogą być 0 lub 1, bo są to pętle jednoelementowe
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



        ////////////////////////////////////////////////////////
        //      LISTA NASTĘPNIKÓW
        ////////////////////////////////////////////////////////
        vertex* pierwszy = new vertex[liczba];       //tworzymy graf "pierwszy" zawierający "liczba" wierzchołków; jest to lista struktur

        //generujemy pierwszą kolumnę wierszy; jest to potrzebne, aby mieć odwołania do wszystkich elementów grafu
        for(int i=0;i<liczba;i++)       //zapełniamy graf danymi
        {
            pierwszy[i].id=i;       //każdy wierzchołek dostaje własne id (lecą po kolei od 0)
            pierwszy[i].next=new vneigh;      //chwilowo nie robimy łuków
        }

        //dopiero teraz możemy zabrać się za robienie łuków
        for(int i=0;i<liczba;i++)       //zapełniamy graf danymi
        {
            vneigh* nnext=pierwszy[i].next;       //wskaźnik na sąsiada wierzchołka

            for(int j=0;j<liczba;j++)       //dodajemy łuki dla każdego wierzchołka
            {
                if(graf[i][j])      //dodajemy łuk jeżeli jest połączenie
                {
                    nnext->id=&pierwszy[j];     //nadajemy wskaźnik na element, do którego idzie łuk
                    nnext->next= new vneigh;        //tworzymy nową pozycję na liście następników
                    nnext=nnext->next;      //zmieniamy wskaźnik na kolejną pozycję
                }
            }
            if(nnext) nnext->next=NULL;     //ostatni element nullujemy żeby nie robił rozpierduchy przy wypisywaniu
        }

        for(int i=0;i<liczba;i++)                   //wyświetlanie listy następników
        {
            cout<<i;
            vneigh* nnext=pierwszy[i].next;       //wskaźnik na sąsiada wierzchołka
            while(nnext->next!=NULL)
            {
                cout<<"->"<<nnext->id->id;      //wypisuje wartość sąsiada
                nnext=nnext->next;
            }
            cout<<endl;

        }


        //zwalnianie pamięci
        for (int x=0;x<liczba;x++)          //zwalniamy pamięć listy
        {
            vneigh* nnext=pierwszy[x].next;       //wskaźnik na sąsiada wierzchołka
            while(nnext->next!=NULL)        //póki nie koniec listy usuwaj kolejne jej elementy od początku licząc
            {                               //i tak z każdą listą aż do końca tablicy
                vneigh* tmp=nnext;
                nnext=nnext->next;
                delete tmp;
            }
        }
        delete [] pierwszy;

        for (int x=0;x<liczba;x++)          //zwalniamy pamięć po kolumnach tablicy
            delete [] graf[x];
        delete [] graf;                     //i w końcu cały graf
    }


    return 0;
}
