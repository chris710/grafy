#include<iostream>
#include<cstdlib>
//#include<vector>            //do macierzy sąsiedztwa      //walić to, zrobimy to na tablicy
#include<list>              //w końcu działamy na listach c'nie?
#include<time.h>            //do liczb pseudolosowych

using namespace std;



//          DO ZROBIENIA:
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
    vertex* id;         //wskaźnik na sąsiada (od niego będziemy brać wartość); dzięki temu wyszukiwanie będzie znacznie szybsze
    vneigh* next;       //wskaźnik na kolejnego sąsiada
};

struct arch                                                             //struktura łuku, do listy krawędzi
{
    vertex* prev;       //wskaźnik na źródło łuku
    vertex* next;       //wskaźnik na ujście łuku
};


int main()                                                              //main
{
    srand(NULL);

    bool dalej=true;    //flaga dla pętli programu; jeżeli staje się false to program zostaje przerwany

    while (dalej)       //pętla programu, dzięki temu można wykonać parę operacji bez wielokrotnego włączania programu
    {
        int arches=0;         //liczba łuków w tworzonym grafie
        int liczba;         //liczba wierzchołków w tworzonym grafie

        cout<<"Podaj liczbe wierzcholkow grafu"<<endl;      //prosimy użytkownika o liczbę danych
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
                    //graf[i][j]=rand()%2;
                    graf[i][j]=0;
                }
                else graf[i][j]=0;      //dla reszty musi być 0
            }
        }

        //wypisywanie grafu na konsoli
        cout<<"Macierz sasiedztwa:"<<endl;
        for(int i=0;i<liczba;i++)       //rząd
        {
            for(int j=0;j<liczba;j++)   //kolumna
            {
                cout<<graf[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;



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
                    arches++;           //to do listy krawędzi; zwiększamy już tutaj, bo zaraz będzie potrzebne
                    nnext->id=&pierwszy[j];     //nadajemy wskaźnik na element, do którego idzie łuk
                    nnext->next= new vneigh;        //tworzymy nową pozycję na liście następników
                    nnext=nnext->next;      //zmieniamy wskaźnik na kolejną pozycję
                }
            }
            if(nnext) nnext->next=NULL;     //ostatni element nullujemy żeby nie robił rozpierduchy przy wypisywaniu
        }

        //wyświetlanie listy następników
        cout<<"Lista nastepnikow: "<<endl;
        for(int i=0;i<liczba;i++)
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
        cout<<endl;



        ////////////////////////////////////////////////////////
        //      LISTA KRAWĘDZI
        ////////////////////////////////////////////////////////

        arch* drugi = new arch[arches];       //tworzymy graf "drugi"; jest to "arches"-elementowa lista struktur
        int luk=0;      //zmienna określająca numer łuku; MUSI być zerowana za każdym razem!!!

        //dane do grafu pobieramy z listy następników
        for(int i=0;i<liczba;i++)
        {
            vneigh* nnext=pierwszy[i].next;       //wskaźnik na sąsiada wierzchołka
            while(nnext->next!=NULL)        //dopóki na liście następników jest sąsiad twórz kolejne łuki
            {
                drugi[luk].prev=&pierwszy[i];       //przypisujemy źródło łuku
                drugi[luk].next=nnext->id;          //i jego ujście
                nnext=nnext->next;
                luk++;                              //przechodzimy do następnego łuku
            }
        }

        //wyświetlanie listy krawędzi
        cout<<"Lista krawedzi: "<<endl;
        for(int i=0;i<arches;i++)
        {
                cout<<drugi[i].prev->id;       //początek krawędzi (z tego wierzchołka ona wychodzi
                cout<<"->"<<drugi[i].next->id;      //koniec krawędzi (wartość wierzchołka, do którego ona wchodzi)
                cout<<endl;
        }
        cout<<endl;



        ////////////////////////////////////////////////////////
        //      ZWALNIANIE PAMIĘCI
        ////////////////////////////////////////////////////////
        for (int x=0;x<liczba;x++)          //zwalniamy pamięć listy    następników
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

        delete [] drugi;                    //zwalniamy pamięć listy krawędzi;tu jest prosto, bo każda lista ma tylko 1 element, więc
                                            //starczy usunąć tablicę struktur

        for (int x=0;x<liczba;x++)          //zwalniamy pamięć po kolumnach tablicy
            delete [] graf[x];
        delete [] graf;                     //i w końcu cały graf
    }


    return 0;
}
