#include<iostream>
#include<cstdlib>
//#include<vector>            //do macierzy sąsiedztwa      //walić to, zrobimy to na tablicy
#include<list>              //w końcu działamy na listach c'nie?
#include<time.h>            //do liczb pseudolosowych

using namespace std;




bool *visited;      //deklaracja tablicy odwiedzonych

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



void sortm (int v, int liczba,int **graf)                                            //sortowanie topologiczne dla macierzy sąsiedztwa
{
    visited[v] = true;                  //oznaczamy wierzchołek jako odwiedzony
    //cout << v << " ";                   //i wyświetlamy go na konsoli

    for(int i=0; i<liczba; i++)     //poruszanie sie po kolumnach
    {
        if(!visited[i] && graf[v][i]==1)
            sortm(i,liczba,graf); //jesli istnieje połączenie i następny jest nieodwiedzony
                                 //to wywolaj rekurencyjnie sortowanie dla następnika
    }
}



void sortn (int v, int liczba,vertex* pierwszy)                                     //sortowanie topologiczne dla listy następników
{
    visited[v]=true;                //oznaczamy wierzchołek jako odwiedzony
    //cout<<v<<" ";                   //wyświetlamy element

    vneigh *temp=pierwszy[v].next;  //ustawiamy tymczasowy wierzchołek na pierwszego nastepnika
    while(temp->next)                     //dopóki jeest jakiś sąsiad to go odwiedzamy
    {
        if(!visited[temp->id->id]) sortn(temp->id->id,liczba,pierwszy); //jesli nastepnik nie byl odwiedzony to odwiedzamy
        temp=temp->next; //kolejny nastepnik
    }
}



void sortk (int v, int liczba, int arches, arch* drugi)                              //sortowanie topologiczne dla listy krawędzi
{
    visited[v] = true;             //oznaczamy jako odwiedzony
    //cout << v << " ";              //wypisujemy element

    for(int i=0; i<arches; i++) //sprawdzanie wiersza
    {
        if (//((drugi[v].prev->id)==v) &&
             (!visited[drugi[v].next->id]))
            sortk(drugi[v].next->id,liczba,arches,drugi);
    }
}



////////////////////////////////////////////////////////
//
//                  MAIN
//
////////////////////////////////////////////////////////
int main()
{
    srand(NULL);
    clock_t start;
    clock_t end;
    float czas;

    bool dalej=true;    //flaga dla pętli programu; jeżeli staje się false to program zostaje przerwany


    while (dalej)       //pętla programu, dzięki temu można wykonać parę operacji bez wielokrotnego włączania programu
    {
        int arches=0;         //liczba łuków w tworzonym grafie
        int liczba;         //liczba wierzchołków w tworzonym grafie

        cout<<"Podaj liczbe wierzcholkow grafu"<<endl;      //prosimy użytkownika o liczbę danych
        cin>>liczba;


        visited = new bool[liczba];                  //tworzenie tablicy odwiedzonych wierzcholkow
        for(int i = 0; i<liczba; i++)
            visited[i] = false;                     //czyścimy tablicę odwiedzonych


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

        /*//wypisywanie grafu na konsoli
        cout<<"Macierz sasiedztwa:"<<endl;
        for(int i=0;i<liczba;i++)       //rząd
        {
            for(int j=0;j<liczba;j++)   //kolumna
            {
                cout<<graf[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;*/

        start=clock();
        //sortowanie topologiczne dla macierzy sąsiedztwa
        for(int i=0;i<liczba;i++) //do wypisywania nieodwiedzonych wierzcholkow (sprawdzanie grafu skierowanego)
        {
            if (!visited[i])        //jeżeli nie odwiedziliśmy jeszcze wierzchołka
                sortm(i,liczba,graf);    //to go wypisujemy
        }
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        cout<<endl<<"Czas: "<<czas;
        cout<<endl<<endl;



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

        /*//wyświetlanie listy następników
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
        cout<<endl;*/

        start=clock();
        //sortowanie topologiczne listy następników
        for(int i = 0; i<liczba; i++)
            visited[i] = false;                     //czyścimy tablicę odwiedzonych
        for(int i=0;i<liczba;i++)
        {
            if(!visited[i])
            sortn(i,liczba,pierwszy);
        }
        end=clock();
        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        cout<<endl<<"Czas: "<<czas;
        cout<<endl<<endl;


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

        /*//wyświetlanie listy krawędzi
        cout<<"Lista krawedzi: "<<endl;
        for(int i=0;i<arches;i++)
        {
                cout<<drugi[i].prev->id;       //początek krawędzi (z tego wierzchołka ona wychodzi
                cout<<"->"<<drugi[i].next->id;      //koniec krawędzi (wartość wierzchołka, do którego ona wchodzi)
                cout<<endl;
        }
        cout<<endl;*/

        start=clock();
        //sortowanie topologiczne listy krawędzi
        for(int i = 0; i<liczba; i++)
            visited[i] = false;                     //czyścimy tablicę odwiedzonych
        sortk(0,liczba,arches,drugi);
        end=clock();

        czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyświetlanie czasu
        cout<<endl<<"Czas: "<<czas;
        cout<<endl<<endl;


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
        delete [] visited;                  //usuwamy listę odwiedzonych
    }


    return 0;
}
