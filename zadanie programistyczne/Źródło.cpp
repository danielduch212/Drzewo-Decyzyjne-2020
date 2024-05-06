#include <iostream>
#include <fstream>
#include <vector>
#include "Nag³ówek.h"
#include <string>
#include <unordered_map>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>
//------------------------TESTOWANIE------------------------------------------------
/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/
//----------------------------------------------------------------------------------

/* @author Daniel Duchnowicz
*/
 
int main(int argc, char* argv[])
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//TESTOWANIE
	std::vector <std::string > atrybuty;
	std::fstream plik;
	
	std::cout << "Ilosc argumentow przyjetych: " << argc << std::endl;
	if (argc != 7 || argc==1)
	{
		std::cout << "Wprowadzono nieprawidlowe parametry" << "\n";
		std::cout << "1- nazwa pliku programu" << "\n";
		std::cout << "2- (-i) plik z danymi wejsciowymi programu" << "\n";
		std::cout << "3- (-t) plik opisujacy strukture drzewa decyzyjnego" << "\n";
		std::cout << "4- (-o) plik wyjsciowy do zapisu danych" << "\n";
		std::cout << "------------------------------------------------------------------------------------------------------------------" << "\n";
		return 0;
	}	

	std::vector<std::string> nazwyPlikow = FormatujParametryWejsciowe(argv);
	std::cout << nazwyPlikow[0] << std::endl;
	std::cout << nazwyPlikow[1] << std::endl;
	std::cout << nazwyPlikow[2] << std::endl;
	plik.open(nazwyPlikow[0], std::ios::in);
	if (plik.good() == false)
	{
		std::cerr << "Nie udalo siê otworzyc pliku.";
		return 0;
	}
	if (argc == 7)
	{
		std::cout << "Podano prawidlowa wartosc argumentow, drzewo decyzyjne podzieli dane do odpowiednich etykiet wyjsciowych" << std::endl;
	}


	if (CzyPlikJestPusty(nazwyPlikow[0]) == true)
	{
		return 0;
	}

	if (CzyPlikJestPusty(nazwyPlikow[1]) == true)
	{
		return 0;
	}


	std::string liniaAtrybutow;
	std::getline(plik, liniaAtrybutow);
	atrybuty = PobierzAtrybuty(liniaAtrybutow);

	for (auto v : atrybuty)
	{
		std::cout << v << "\n";

	}
	
	std::vector < std::unordered_map<std::string, float>> wartosci;
	float tymczasoweDane;

	for (int i = 0; !plik.eof(); i++)
	{
		wartosci.resize(wartosci.size() + 1);

		for (int n = 0; !plik.eof() && n < atrybuty.size(); n++)
		{
			plik >> tymczasoweDane;
			wartosci[i].insert({ atrybuty[n],tymczasoweDane });
		}
		
	}
	plik.close();
	
	for (auto n : wartosci)
	{
		for (auto v : n)
			std::cout << v.first << "\t" << v.second << std::endl;
	}

	Drzewo d1(PobierzDrzewo(nazwyPlikow[1]));
	std::unordered_map < std::string, std::vector < std::vector <float>>>  mapa;
	mapa = d1.InterpretujDane(wartosci, atrybuty);
	plik.open(nazwyPlikow[2], std::ios::out);

	if (plik.good() == false)
	{
		std::cerr << "Nie uda³o siê otworzyæ pliku.";

	}
	for (auto c : d1.kluczeWynikowe)
	{
		plik << c << "\n";
		for (auto d : mapa[c])
		{

			for (int i = 0; i < d.size(); i++)
			{
				plik << d[i] << " ";

			}
			plik << std::endl;
		}
		

	}

	if (CzyPlikJestPusty(nazwyPlikow[2]) == true)
	{
		return 0;
	}

	plik.close();
	
	return 0;
};
