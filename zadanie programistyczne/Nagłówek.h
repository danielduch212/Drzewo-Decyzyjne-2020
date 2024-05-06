#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Nag³ówek.h"
#include <string>
#include <unordered_map>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>

struct ElementDrzewa;
void ZnajdzIUsunKomentarz(std::string& komentarz);
std::vector<std::string> PobierzAtrybuty(std::string argument);
std::string WytnijNastepnyElement(std::string& liniaTekstu, const char& SzukanySymbol);
char WytnijNastepnyElement(std::string& liniaTekstu);
std::string WytnijNastepnyElementBezUsuwaniaSymbolu(std::string& liniaTekstu, std::vector<char> znakiKonczace);
std::vector<ElementDrzewa> PobierzDrzewo(std::string argv);
bool CzyPlikJestPusty(char* arg);
std::vector<std::string> FormatujParametryWejsciowe(char* argv[]);
bool CzyPlikJestPusty(std::string arg);

/** \brief Struktura ElementDrzewa przechowuje najwa¿niejsze informacje o wêŸle drzewa.
*/
struct ElementDrzewa
{
	int indeks=0; 
	std::string AtrybutDoPorownania; 
	char symbolPorownania;
	std::string etykietaWyjsciaNIE="";
	std::string etykietaWyjsciaTAK="";
	float wartoscDoPorownania;

};
/** \brief Klasa Drzewo operuje na vectorze Elementów Drzewa, interpretuj¹c wprowadzone przez funkcjê argumenty.
* 
* Wynik operacji InterpretujDane przechowywany jest w obiekcie do czasu ponownego wywo³ania funkcji.
* Klucze Wynikowe to vector etykiet u¿ytych w Elementach Drzewa.
*/
class Drzewo
{
	std::unordered_map<std::string, float> wartosc;
	std::vector<ElementDrzewa> ElementyDrzewa;
public:
	Drzewo(std::vector<ElementDrzewa> ElementyDrzewa);
	std::unordered_map < std::string, std::vector < std::vector <float>>> InterpretujDane(std::vector < std::unordered_map<std::string, float>> wartosci, std::vector<std::string> kluczeAtrybutow);
	std::string InterpretujNastepnyElement(int indeksLiscia);
	bool PorownajDane(ElementDrzewa Element);
	bool CzyJestIndeksem(const std::string& linia);
	std::unordered_map<std::string, std::vector<std::vector<float>>> wynik;
	std::vector<std::string> kluczeWynikowe;
};


