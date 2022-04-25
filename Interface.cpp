#include "Interface.h"
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <chrono>
using namespace std;

//FUNKCJA WCZYTUJE GRAF Z PLIKU
void Wczytaj(Graph *&_Graph)
{
	int Krawedzie;
	int Wierzcholki;
	int Start;
	int wierz_poccz;
	int wierz_kon;
	int waga;
	string nazwa_pliku;

	ifstream plik;
	printf("podaj nazwe pliku \n");
	cin >> nazwa_pliku;


	plik.open(nazwa_pliku.c_str());

	if (plik.good())
	{
		plik >> Krawedzie;
		plik >> Wierzcholki;
		plik >> Start;
		_Graph = new Graph(Wierzcholki, Krawedzie, Start);
		while (!plik.eof())
		{
			plik >> wierz_poccz;
			plik >> wierz_kon;
			plik >> waga;

			_Graph->dodaj_krawedz(wierz_poccz, wierz_kon, waga);
		}

	}
	else
	{
		printf("zla nazwa pliku \n");
	}
	plik.close();


}

//FUNKCJA ODPOWIADAJACA ZA TWORZENIE GRAFU
//NALEZY PODAC ILOSC WIERZCHOLKOW, GESTOSC, ORAZ WIERZCHOLEK STARTOWY
void generuj()
{
	int Krawedzie;
	int Wierzcholki;
	int Start;
	int licznik=0;
	double gestosc;
	string nazwa_pliku;
	ofstream plik;
	int waga;
	printf("podaj nazwe pliku \n");
	cin >> nazwa_pliku;

	plik.open(nazwa_pliku.c_str());
	printf("Podaj liczbe wierzcholkow, gestosc (0-1) np 0.2, wierzcholek startowy \n");
	cin >>Wierzcholki >> gestosc>> Start;

	Krawedzie = ((Wierzcholki*(Wierzcholki - 1)) / 2)*gestosc;

		plik << Krawedzie << " " << Wierzcholki << " " << Start << endl;

		for (int i = 0; i < Wierzcholki; i++)
			for (int j = i; j < Wierzcholki; j++)
			{

				if (i != j && licznik< Krawedzie)
				{
					waga = rand() % 50 + 1;
					plik << i << " " << j << " " << waga << endl;
					plik << j << " " << i << " " << waga << endl;
					licznik++;
				}
			}

	plik.close();

}

//MENU UZYTKOWNKIA DO KOMUNIKACJI Z PROGRAMEM
//MOZNA WYBIERAC CO CHCEMY ZROBIC Z PROGRAMEM
// STWORZYC GRAF, WCZYTAC Z PLIKU, WYSWIETLIC, ALBO PODDAC ALGORYTMOWI DIJKSTRA DLA LISTY I MACIERZY
void menu()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    double time = 0;
	clock_t start, stop;
	char opcja;
	Graph *_Graph = NULL;
	dane* tab;
	cout.precision(6);
	while (1)
	{
		cout << "1 - Generuj" << endl;
		cout << "2 - Wczytaj" << endl;
		cout << "3 - Wyswietlanie grafu" << endl;
		cout << "4 - Macierz sasiedztwa" << endl;
		cout << "5 - Lista sasiedztwa" << endl;
		cout << "6 - Aby zakonczyc" << endl;

		cout << "podaj opcje" << endl;

		cin >> opcja;

		switch (opcja)
		{
		case '6':
			return;
		case '1':
			generuj();
			break;
		case '2':
			Wczytaj(_Graph);
			break;
        case '3':
			cout << "Macierz:" << endl;
			_Graph->wyswietl();

			cout << endl << "Lista:" << endl;
			_Graph->wyswietl_liste();
			break;
		case '4':
		{
			auto t1 = high_resolution_clock::now(); //POCZATEK ZLICZANIA CZASU DZIALANIA ALGORYTMU
			for (int i = 0; i < 100; i++)
			{
				 tab = _Graph->Dijkstra();
			}
			auto t2 = high_resolution_clock::now();
				duration<double, std::milli> ms_double = t2 - t1;
				cout << endl << "Czas dzialania algorytmu: " << ms_double.count() << " ms." << endl;

			_Graph->zapisz(tab);
		}
		break;
		case '5':
		{

			auto t1 = high_resolution_clock::now();								//POCZATEK ZLICZANIA CZASU DZIALANIA ALGORYTMU
			for (int i = 0; i < 100; i++)
			{
				 tab = _Graph->Dijkstra_Lista();
			}
			auto t2 = high_resolution_clock::now();
				duration<double, std::milli> ms_double = t2 - t1;
				cout << endl << "Czas dzialania algorytmu: " << ms_double.count() << " ms." << endl;
			_Graph->zapisz(tab);
		}
		break;
		}
	}
}

