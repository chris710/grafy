grafy
=====

Zadanie trzecie (Algorytmy grafowe)
Termin zaliczenia zadania + wykres - 24.04.2013; sprawozdanie mailem (pdf)- 28.04.2013 
Wygeneruj spójny skierowany graf acykliczny o n wierzchołkach; każdy wierzchołek odpowiada jednemu zadaniu
 - zdefiniuj ograniczenia kolejnościowe pomiędzy zadaniami z grafu 
 - istnienie łuku pomiędzy dwoma zadaniami a i b oznacza, że a musi zostać wykonane przed b 
 - współczynnik nasycenia łukami w grafie powinien być równy 50% (czyli 50% z n(n-1)/2)
Graf jest reprezentowany poprzez  macierz sąsiedztwa, listę następników oraz listę krawędzi (zaimplementowaną jako tabelę). Dla chętnych również macierz grafu. 
Zaimplementuj algorytm sortowania topologicznego (zgodnie z algorytmem przeszukiwania w głąb) 
 - dokonaj pomiaru czasu działania algorytmu dla każdej reprezentacji grafu 
 - ogólna idea algorytmu, ma być taka sama dla różnych reprezentacji grafu
 - nie należy upraszczać algorytmu ze względu na przygotowanie danych wejściowych (np. macierz sąsiedztwa jest górnotrójkątna)
Pomiary czasu przedstaw na wykresie t=f(n), dla 10 różnych wartości n 
W sprawozdaniu, oprócz wykresów:
 - dla każdej z badanych reprezentacji grafu podaj złożoność: pamięciową, znalezienia pojedynczej krawędzi oraz znalezienia wszystkich następników wierzchołka
 - oszacuj złożoność obliczeniową algorytmu sortowania topologicznego (jak się zmienia w zależności od reprezentacji grafu)
 - które grafy można sortować topologiczne?
 Sortowanie topologiczne grafu skierowanego polega na utworzeniu takiej permutacji p wszystkich wierzchołków w grafie, aby każdy wierzchołek posiadający
następników znalazł się przed nimi w tej permutacji. Tzn. jeśli jest krawędz wychodząca z x do y, to wierzchołek x musi się znalezć w permutacji p przez wierzchołkiem y.
