#include "Nag³ówek.h"

/** \brief Funkcja sprawdza czy plik jest pusty, uzywajac do tego funkcji getline(), jesli linia sprawdzajaca do ktorej jest przypisany getline, bedzie pusta, to funkcja zwróci true.
*/
bool CzyPlikJestPusty(char* nazwaPliku)
{
	std::fstream plik;
	plik.open(nazwaPliku, std::ios::in);
	std::string LiniaSprawdzajaca;
	std::getline(plik, LiniaSprawdzajaca);
	if (LiniaSprawdzajaca.empty())
	{
		std::cout << "Plik " << nazwaPliku << " Jest pusty, nastepuje zamkniecie programu!" << "\n";
		return true;
	}
	return false;
	plik.close();

};

bool CzyPlikJestPusty(std::string arg)
{
	std::fstream plik;
	plik.open(arg, std::ios::in);
	std::string LiniaSprawdzajaca;
	std::getline(plik, LiniaSprawdzajaca);
	if (LiniaSprawdzajaca.empty())
	{
		std::cout << "Plik " << arg << " Jest pusty, nastepuje zamkniecie programu!" << "\n";
		return true;
	}
	return false;
	plik.close();

};

/** \brief Funkcja pobiera atrybuty z pliku tekstowego. Atrybuty sa dodawane do wektora, o ile znajduje sie komentarz to nie jest brany pod uwage.
*/
std::vector<std::string> PobierzAtrybuty(std::string liniaAtrybutow)
{
	std::vector<std::string> znalezioneAtrybuty;
	size_t pozycjaBialegoZnaku=1;
	ZnajdzIUsunKomentarz(liniaAtrybutow);
	for (;;)
	{
		pozycjaBialegoZnaku = 0;
		pozycjaBialegoZnaku = liniaAtrybutow.find(" ", pozycjaBialegoZnaku);
		if (pozycjaBialegoZnaku == -1)
		{
			znalezioneAtrybuty.push_back(liniaAtrybutow);//Jezeli mamy ostatni wyraz w linii, tzn. w tym przypadku, wyskok, po ktorym nie ma spacji, to dorzucamy ten wyraz do kontenera, bo w petli to nie zostanie wykonane
			break;
		}
			
		znalezioneAtrybuty.push_back(liniaAtrybutow.substr(0, pozycjaBialegoZnaku));//Pobiera ciag do szukanego znaku;
		liniaAtrybutow.erase(0, pozycjaBialegoZnaku + 1);
		

	}
	return znalezioneAtrybuty;

};
/** \brief Funkcja usuwa komentarz po znaku "%" az do konca tej linii.
*/
void ZnajdzIUsunKomentarz(std::string& komentarz)
{
	int pozycja = komentarz.find("%");
	if (pozycja != -1)
		komentarz.erase(pozycja - 1);
	return;


};
/** \brief Funkcja zwraca ciag znakow, do szukanego symbolu.
*
* Znaleziony ciag znakow jest kasowany z podanej linii tekstu.
* Jezeli symbol nie zostal znaleziony, to zostaje zwrocony pusty ciag. 
*/
std::string WytnijNastepnyElement(std::string& liniaTekstu, const char& SzukanySymbol)
{
	int pozycjaSzukanegoZnaku = liniaTekstu.find(SzukanySymbol);
	std::string wycietyCiag="";
	if (pozycjaSzukanegoZnaku != -1)
	{
		wycietyCiag = liniaTekstu.substr(0, pozycjaSzukanegoZnaku);
		liniaTekstu.erase(0, pozycjaSzukanegoZnaku + 1);
		

	}
	return wycietyCiag;
};
/** \brief Funkcja wycina nastepny znak w podanej linii tekstu i go wycina z linii tekstu.
*/
char WytnijNastepnyElement(std::string& liniaTekstu)
{
	char wycietyZnak=' ';
	if (!liniaTekstu.empty())
	{
		wycietyZnak = liniaTekstu[0];
		liniaTekstu.erase(0, 1);
	}
	return wycietyZnak;
};
/** \brief Funkcja przeszukuje podana linie tekstu w poszukiwaniu znakow konczacych, a nastepnie je¿eli znajdzie no to wycina do znalezionego znaku.
*/
std::string WytnijNastepnyElementBezUsuwaniaSymbolu(std::string& liniaTekstu, std::vector<char> znakiKonczace)
{
	std::vector<char>::iterator iterator = znakiKonczace.begin();
	int pozycjaSzukanegoZnaku;
	std::string WycietyCiag = "";
	do 
	{
		pozycjaSzukanegoZnaku = liniaTekstu.find(*iterator);
		iterator++;

	} while (pozycjaSzukanegoZnaku==-1&&iterator!=znakiKonczace.end());

	if (pozycjaSzukanegoZnaku != -1)
	{
		WycietyCiag = liniaTekstu.substr(0, pozycjaSzukanegoZnaku);
		liniaTekstu.erase(0,pozycjaSzukanegoZnaku);
	}
	std::cout << WycietyCiag<<std::endl;
	return WycietyCiag;
	
};

/** \brief 
* 
* Jest to funkcja kluczowa, funkcja jest scisle zwiazana z plikiem opisujacym strukture drzewa, 
*		funkcja tworzy cialo drzewa uzywajac innych funkcji przez przypisanie kolejnych ciagow znakow do skladowych elementu typu ElementDrzewa, uzywamy struktury ElementDrzewa, ktora zostala stworzona.
* @return Zwracamy vector zdefiniowanych Elementow Drzewa;
*/
std::vector<ElementDrzewa> PobierzDrzewo(std::string argv)
{
	std::vector<ElementDrzewa> CialoDrzewa;
	std::fstream plikStruktury;
	plikStruktury.open(argv, std::ios::in);
	if (plikStruktury.good() == false)
	{
		std::cerr << "Nie udalo sie otworzyc pliku plikStruktury" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string linia;
	for (;!plikStruktury.eof();)

	{
		linia = "";
		ElementDrzewa Element;
		std::getline(plikStruktury, linia);
		ZnajdzIUsunKomentarz(linia);
		Element.indeks = stoi(WytnijNastepnyElement(linia, ' '));
		Element.AtrybutDoPorownania = WytnijNastepnyElementBezUsuwaniaSymbolu(linia, std::vector<char>({ '<','>' }));
		Element.symbolPorownania = WytnijNastepnyElement(linia);
		Element.wartoscDoPorownania = stof(WytnijNastepnyElement(linia, ' '));
		Element.etykietaWyjsciaNIE = WytnijNastepnyElement(linia, ' ');
		Element.etykietaWyjsciaTAK = linia;
		CialoDrzewa.push_back(Element);
	}

	return CialoDrzewa;
};
/** \brief Konstruktor klasy Drzewo przyjmuje vector elementow drzewa i inicjalizuje nim obiekt Drzewa.
*/
Drzewo::Drzewo(std::vector<ElementDrzewa> ElementyDrzewa)
{
	this->ElementyDrzewa = ElementyDrzewa;
};

/** \brief Funkcja InterpretujDane - podane wartoœci interpretuje przez funkcje rekurencyjn¹ i zapisuje wynik do mapy etykiet znalezionych w tym drzewie.
* 
* Ka¿dy zinterpretowany element jest zapisywany w mapie, pod etykiet¹ wyjscia. Dodatkowo zapisywane s¹ u¿ywane klucze.
*/
std::unordered_map < std::string, std::vector < std::vector <float>>> Drzewo::InterpretujDane(std::vector < std::unordered_map<std::string, float>> wartosci, std::vector<std::string> kluczeAtrybutow)
{
	std::unordered_map < std::string, std::vector < std::vector <float>>> wynik;
	std::string TymczasowyKlucz;
	for (int i = 0; i < wartosci.size(); i++)
	{
		wartosc = wartosci[i];
		TymczasowyKlucz = InterpretujNastepnyElement(0);
		wynik[TymczasowyKlucz].push_back(std::vector<float>());
		for (int o = 0; o < kluczeAtrybutow.size(); o++)
		{
			wynik[TymczasowyKlucz].back().push_back(wartosci[i][kluczeAtrybutow[o]]);//na sam koniec wektora dwywymiarowego dodajemy dane, wedlug uzyskanych atrybutow

		}
		
	}
	kluczeWynikowe.clear();
	this->wynik = wynik;
	for (std::unordered_map < std::string, std::vector < std::vector <float>>>::iterator iterator=wynik.begin();iterator!=wynik.end();iterator++)
	{
		kluczeWynikowe.push_back(iterator->first);
	}
	return Drzewo::wynik;
};
/** \brief Funkcja rekurencyjnie przeszukuje drzewo po kolejnych wezlach.
* 
* Funkcja porównuje warunek jaki zawarty jest w elemencie drzewa, dodatkowo sprawdza, czy etykieta wyjœcia
* jest indeksem czy s³owem koñcz¹cym decyzjê.
*/
std::string Drzewo::InterpretujNastepnyElement(int indeksLiscia)
{
	if (PorownajDane(ElementyDrzewa[indeksLiscia]))
	{
		if (CzyJestIndeksem(ElementyDrzewa[indeksLiscia].etykietaWyjsciaTAK))
		{
			return InterpretujNastepnyElement(stoi(ElementyDrzewa[indeksLiscia].etykietaWyjsciaTAK));

		}
		else
		{
			return ElementyDrzewa[indeksLiscia].etykietaWyjsciaTAK;
		}
			
	}
	else
	{
		if (CzyJestIndeksem(ElementyDrzewa[indeksLiscia].etykietaWyjsciaNIE))
		{
			return InterpretujNastepnyElement(stoi(ElementyDrzewa[indeksLiscia].etykietaWyjsciaNIE));

		}
		else
		{
			return ElementyDrzewa[indeksLiscia].etykietaWyjsciaNIE;
		}

	}
		
};
/** \brief Funkcja sprawdza czy podana linia sk³ada sie w ca³oœci z liczb.
*/
bool Drzewo::CzyJestIndeksem(const std::string& linia)
{
	for (std::string::const_iterator iterator = linia.begin(); iterator != linia.end(); iterator++)
	{
		if (!isdigit(*iterator))//funkcja sprawdza czy cos jest liczba
			return false;
	}
	return true;

}

/** \brief Sprawdzamy warunek zawarty w elemencie Drzewa.
*/
bool Drzewo::PorownajDane(ElementDrzewa Element)
{

	switch (Element.symbolPorownania)
	{

		case '>':
			if (wartosc[Element.AtrybutDoPorownania] > Element.wartoscDoPorownania)
			{
				return true;
			}
			break;	
		case '<':
			if (wartosc[Element.AtrybutDoPorownania] < Element.wartoscDoPorownania)
			{
				return true;

			}
			break;
		default:
			std::cout << "Nieprawid³owy operator porównania w strukturze drzewa" << "\n";
			exit(EXIT_FAILURE);
			break;
	}
	return false;



};
/** \brief Funkcja formatuje dane ktore sa wpisywane do lini polecen, nazwy plikow moga byc wpisywane w roznej kolejnosci, dlatego tutaj dane sa wprowadzane do odpowiednich miejsc w vectorze.
*/
std::vector<std::string> FormatujParametryWejsciowe(char* argv[])
{
	std::vector<std::string> argumenty;
	std::string linia;

	argumenty.resize(3);
	linia = argv[1];
	if (linia == "-i")
	{
		argumenty[0] = argv[2];
	}
	else if (linia == "-t")
	{
		argumenty[1] = argv[2];
	}
	else if (linia == "-o")
	{
		argumenty[2] = argv[2];
	}
	///////////////////////////////////////////// Pierwszy plik
	linia = argv[3];

	if (linia == "-i")
	{
		argumenty[0] = argv[4];
	}
	else if (linia == "-t")
	{
		argumenty[1] = argv[4];
	}
	else if (linia == "-o")
	{
		argumenty[2] == argv[4];
	}
	//////////////////////////////////////////// Drugi Plik
	
	linia = argv[5];
	if (linia == "-i")
	{
		argumenty[0] = argv[6];
	}
	else if (linia == "-t")
	{
		argumenty[1] = argv[6];
	}
	else if (linia == "-o")
	{
		argumenty[2] = argv[6];
	}
	return argumenty;
	//////////////////////////////////////////////// Trzeci Plik

};


