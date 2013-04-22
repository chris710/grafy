/** ------------------------------------------------
 autor: Krzesimir Samborski, Paweł Kusz,
 uwagi: do wykonania zostalo jeszcze:
  # sortowanie topologiczne,
  # pomiar czasu 
  pomiar czasu jest pokius tylko trzeba zrobic sortowanie topologiczne, 
  zobacz to co napisalem i napisz mi jakie masz uwagi i jakie pomysly co do sortowania,
  jak zrobimy calosc to zadbamy o estetyke i przyspieszenie podzial na biblioteki i inne skladowe pliki ok ? ;D 
  na razie skupmy się na poprawnosci.
  P.S nie irytuj sie jak bedziesz czytał kod staralem sie wszystko komentować ;D
------------------------------------------------ **/

#include <stdio.h>
#include <stdlib.h>


// do biblioteki
#define MEASURMENT 10
#define AMOUNT 7

/** struktura listy sasiedztwa **/
//==================================================================
struct AdjList
{
    struct AdjListNode *head;  // wskazuje na 1 elementy list odchodzacych od naszej głownej listy(tablicy wskaznikow) sasiedztwa
};
//===================================================================



/**-----------------------------------------------------------------
    struktura wierzcholkow grafu znajdujacych sie na listach
    odchodzacyh od głownej listy sasiedztwa (tablicy wskaznikow)
------------------------------------------------------------------**/
//==================================================================
struct AdjListNode
{
    int myId;  // zawieria "imie" wierzcholka  bedącego nastepnikiem rozwazanego wierzcholka  np [0] -> 3 (myId)
   // int whereMyNext; // zawiera id w ktore mowi nam gdzie szukac nastepnikow danego wierzcholka -- nie potrzebne ale moze sie myle dlatego nie usuwam
    struct AdjListNode* next; // wskazuje na nastepnego nastepnika
};
//====================================================================



//=====================================================================
/** ------------  Funckje obslugujące listę sasiedztwa ----------  **/
//=====================================================================

            struct AdjList* createAdjList(int);             // tworzenie pustej listy sasiedztwa, zwraca wskaznik na tablice wskaznikow
            struct AdjListNode* createAdjListNode(int);     // tworzenie nastepnika od dodania zwraca wskaznik na nowy wierzcholek
            void addToAdjList(struct AdjList*,int, int);    // dodawanie nastepnika do listy na poczatek, przyjmuje adres tablicy wskaznikow -
                                                            // do ktorej ma dodac, w ktore miejsce ma dodac i co ma dodac

            void printAdjList(struct AdjList*, int);          // drukowanie listy sasiedztwa na ekran
            void freeAdjList(struct AdjList*, int);           // zwalnianie pamięci zajmowanej przez listy nastepników

//======================================================================
/** ------------  Funckje obslugujące listę krawedzi ----------  **/
//=====================================================================

/* *********************************************************************
                    ////////////////////////
                    ////////////////////////
                    ////////////////////////

*************************************************************************/



int main()
{

    //======================================================================
    /** ------------ zmienne lokalne  ----------  **/
    //=====================================================================

    int **AdjMatrix;    //deklaracja tablicy sąsiedztwa
    int **EdgeMatrix;   // deklaracja tablicy krawedzi
    int measurment;     // zmienna pomocnicza przy petli pomiarowej




    //=================================================================================
    /** rozpoczecie pętli pomiarowej **/
    //==================================================================================

    for(measurment=0;measurment<MEASURMENT;measurment++) // rozpoczecie petli pomiarowej
    {

        int vertex,edges,edges_count,one;
        int i,j;                    // zmienne pomocnicze przy tworzeniu macierzy sasiedztwa


        vertex=measurment+AMOUNT;   // definicja liczby wierzcholkow
        edges=vertex*(vertex-1)/4;  // wspolczynnik zageszczenie
        edges_count=0;              // liczba krawedzi
        one=1;
        for(i=0;i<80;i++)
            putchar('-');

            AdjMatrix=(int**)malloc(vertex*sizeof(int *));      // rezerwacja miejsca w pamieci

            for(i=0; i<vertex; i++)
                AdjMatrix[i]=(int*)malloc(vertex*sizeof(int));  // rezerwacja miejsca w pamieci na kolumny

        // w wyniku tych rezerwacji mamy macierz vertex x vertex którą zaraz uzupelnimy w taki sposób by powstał graf skierowany, spojny, acykliczny

            for(i=0;i<vertex;i++)       // rozpoczecie petli odpowiedzialnej za wiersze
            {

                for(j=0;j<vertex;j++)   // rozpoczecie petli odpowiedzialnej za kolumny
                    {

                      if(i<j && one && edges_count<=edges)  // sprawdzenie czy wstawic 1 czy 0,

                      //==================================================================================================
                      /**-------------------------------------------------------------------------------------------------
                            i<j -warunek macierzy gornotrójkatnej,
                            one -wstawic 1 czy 0 zeby zachowac 50% nasycenia,
                            edges_count - sprwadza czy liczba juz wstawionych krawedzi nie jest wieksz niz 50% nasycenia
                      ------------------------------------------------------------------------------------- ------------**/
                     //===================================================================================================

                            {
                            printf("1 ");       //potrzebne przy testach poprawnosci
                            AdjMatrix[i][j]=1;
                            one=0;
                            edges_count++;
                            }
                         else
                         {
                            printf("0 ");       //potrzebne przy testach poprawnosci
                            AdjMatrix[i][j]=0;
                            one=1;
                         }
                    }                 // zakonczenie petli odpowiedzialnej za kolumny

                    putchar('\n');    // odstep dla nastepnego wiersza

            }                         // zakonczenie petli odpowiedzialnej za wiersze

            putchar('\n');            // odstep dla estetyki
            putchar('\n');            // odstep dla estetyki


            //==============================================================================
            /** ---------------tworzenie listy sasiedztwa -------------------------------**/
            //==============================================================================

            struct AdjList* array=createAdjList(vertex); // tworzenie tablicy wskaznikow do list nastepnikow



            //==============================================================================
            /** ---------------Wstawianie nastepników w odpowiednie miejsce----------- **/
            //==============================================================================

            for(i=0;i<vertex;i++)
                for(j=0;j<vertex;j++)
                {
                    if(AdjMatrix[i][j])             // sprawdzamy ktore pole macierzy sasiedztwa ma wartosc 1
                        addToAdjList(array,i,j);    // wstawiamy krawedz w odpowiednie miejsce
                }

            printAdjList(array,vertex);             // drukowanie listy nastepników
            putchar('\n');




            //==============================================================================
            /** ---------------tworzenie listy krawedzi (tablicy) ------------------------**/
            //==============================================================================

            EdgeMatrix=(int**)malloc((edges+1)*sizeof(int*));

            for(i=0;i<=edges;i++)
                EdgeMatrix[i]=(int*)malloc(2*sizeof(int));

            // powyzsze dzialanie zbudowalo nam tablice edgex x 2

            // teraz czas na uzupelnienie jej danymi ;)

            // czas budowania nie jest wazny w zadaniu wiec zbudujemy ja na podstawie macierze sasiedzywa

            int k=0; // pomocnicza zmienna do zaplaniania naszej nowej tablic

            // metoda wolniejsza niz szczytanie z listy ale mam nadzieje ze dziala jak bedzie czas to sprawdzimy szczytanie z listy

            for(i=0;i<vertex;i++)
                {
                    for(j=0;j<vertex;j++)
                        if(AdjMatrix[i][j])
                        {
                            EdgeMatrix[k][0]=i;
                            EdgeMatrix[k][1]=j;
                            k++;
                        }
                }
            // drukowanie naszej tablicy krawedzi

             for(i=0;i<=edges;i++)
                {
                    for(j=0;j<2;j++)
                        printf("%5d |", EdgeMatrix[i][j]);
                    putchar('\n');
                }




            //==============================================================================
             /** --------------- zwalnianie pamieci listy krawedzi -------------------**/
            //==============================================================================

             for(i=0; i<=edges; i++)   // zwalnianie pamieci wierszy listy (tablicy ) nastepników
                free(EdgeMatrix[i]);

            free(EdgeMatrix);   // zwalnianie calej pamieci po tej tablicy


            //==============================================================================
             /** --------------- zwalnianie pamieci listy nastepnikow  -------------------**/
            //==============================================================================

            freeAdjList(array, vertex); // zwalnianie pamieci zajmowanej przezy listy
            free(array); // zwolnienie  pamiecie zajmowanej przez przez tablice wskazników


            //==============================================================================
             /** --------------- zwalnianie pamiecie macierzy sasiedztwa------------------**/
            //==============================================================================

            for(i=0; i<vertex; i++)   // zwalnianie pamieci wierszy macierzy sasiedztwa
                free(AdjMatrix[i]);

            free(AdjMatrix);          // zwalnianie pamieci po calej macierzy sasiedztwa



    }
    //==================================================================================
    /** -------------------------- zakończenie pętli pomiarowej -----------------------**/
    //==================================================================================
    return 0;
}





/**  tworzenie tablicy wskaznikow do list nastepnikow  **/
//////////////////////////////////////////////////////////////////////////////////////////
struct AdjList* createAdjList(int V)
    {
      struct AdjList* array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
      int i;
      for (i = 0; i < V; ++i)
      array[i].head = NULL;
      return array;
    }

//////////////////////////////////////////////////////////////////////////////////////////


/** dodawanie utworzonego wierzcholka do listy nastepnikow **/
//////////////////////////////////////////////////////////////////////////////////////////
void addToAdjList(struct AdjList* array,int i, int j)
    {
        struct AdjListNode* newNode = createAdjListNode(j);
        newNode->next = array[i].head;
        array[i].head = newNode;
    }
//////////////////////////////////////////////////////////////////////////////////////////

/** tworzenie wierzcholka do dodania do listy **/
//////////////////////////////////////////////////////////////////////////////////////////
struct AdjListNode* createAdjListNode(int j)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->myId = j;
    // newNode->whereMyNext=j; // to wlasciwie jest nie potrzebne bo jego nastepniki znajduja sie w wierszu pod wartoscia jego idenfikatora
    newNode->next = NULL;
    return newNode;
}
//////////////////////////////////////////////////////////////////////////////////////////

/** drukowanie listy nastepnikow **/
//////////////////////////////////////////////////////////////////////////////////////////
void printAdjList(struct AdjList* array, int V)
{
    int i;
    for (i = 0; i <V; i++)
    {
        struct AdjListNode* tmp = array[i].head;
        printf("%d",i);
        while (tmp)
        {
            printf("-> %d", tmp->myId);
            tmp = tmp->next;
        }
        printf("-> / \n");
    }
}
//////////////////////////////////////////////////////////////////////////////////////////

/** zwalnianie pamieci zajmowanej przez listy nastepnikow **/
//////////////////////////////////////////////////////////////////////////////////////////
void freeAdjList(struct AdjList* array, int V)
{
    int i;
    for(i=0;i<V;i++)
    {
        struct AdjListNode* tmp = array[i].head;
        while(tmp)
        {
         struct AdjListNode* help=tmp;
         tmp=tmp->next;
         free(help);
        }

    }
    //puts("Now AdjList is empty");
}

/** tworzenie listy krawedzi **/
//////////////////////////////////////////////////////////////////////////////////////////
