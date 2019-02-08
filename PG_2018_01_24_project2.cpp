//POP 2017-01-24 projekt 2 Kus Mateusz IBM 2 172120

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
const string sz1 = "@author"; //zmienne z zawartosci¹ znaczników
const string sz2 = "@date";
const string sz3 = "@brief";
const string sz4 = "@param";
const string sz5 = "@retval";
const string sz6 = "*";


struct dane  //strunktura przechowujaca informacje o funkcji
{
	string author, date, brief, name, opis;
	string param[10], retval[5];
};


void szukajFraz(ifstream &plik, dane &baza, int &licznikPar, int &licznikRet) //szuka znacznikow w tekscie
{
	
	string tekst;
	licznikPar = 0; //ilosc parametrow
	licznikRet = 0; //ilosc zwracanych wartosci
	int dlugosc;
	
	bool zrobiono = false;
	baza.opis = "";
	do {
		getline(plik, tekst);
		
		if (tekst.find(sz1) != string::npos)
		{	
				dlugosc = sz1.length() + 3; 
				tekst.erase(0, dlugosc); //wymazanie znacznika z pobranego tekstu
				baza.author = tekst;
				
		}
		else if (tekst.find(sz2) != string::npos)
		{
			dlugosc = sz2.length() + 3;
			tekst.erase(0, dlugosc);
			baza.date = tekst;
			
		}
		else if (tekst.find(sz3) != string::npos)
		{
			dlugosc = sz3.length() + 3;
			tekst.erase(0, dlugosc);
			baza.brief = tekst;
			
		}
		else if (tekst.find(sz4) != string::npos)
		{
			dlugosc = sz4.length() + 3;
			tekst.erase(0, dlugosc);
			baza.param[licznikPar] = tekst;
			licznikPar++;
		}
		else if (tekst.find(sz5) != string::npos)
		{
			dlugosc = sz5.length() + 3;
			tekst.erase(0, dlugosc);
			baza.retval[licznikRet] = tekst;
			licznikRet++;
		}
		else if (tekst.find("@") == string::npos && tekst.find(" */") == string::npos)
		{
			
			tekst.erase(0, 3);
			tekst += " ";
			baza.opis += tekst;

		}
		else if (tekst.find(" */") != string::npos) //koniec opisu funkcji
		zrobiono = true;
		
	} while (!zrobiono);
}


void wypiszBaze(dane &baza, int licznik, int licznikPar, int licznikRet) //wypisuje dane o funkcji
{
	
	baza.name.erase(baza.name.find("("), baza.name.length()); //czysci pobrany tekst zeby sotala tylko nazwa funkcji

	cout << licznik << " . Funkcja " << baza.name << " - " << baza.brief << endl;

	cout << "Przyjmuje " << licznikPar << " parametrow:" << endl;
	for (int i = 0; i < licznikPar; i++)
	{
		cout << " - " << baza.param[i] << endl;
	}

	cout << "Zwraca " << licznikRet << " wartosci:" << endl;
	for (int i = 0; i < licznikRet; i++)
	{
		cout << " - " << baza.retval[i] << endl;
	}

	cout << "Czas powstania funkcji: : " << baza.date << " r. ";
	cout << "Autor: " << baza.author << endl;
	cout <<"Funkcjonalnosc: "<< baza.opis << endl;
	cout << endl;
}



int main()
{
	ifstream plik;
	int licznik = 0, licznikPar, licznikRet;
	dane baza;
	plik.open("test.txt", ios::in); // otwarcie pliku wejœciowego
	if (!plik) {
		cerr << "Nieudane otwarcie pliku ";
		system("pause");
		return 1;
	}

	string bufor;
	do
	{
		getline(plik, bufor);

		if (bufor.find("/**")!= string::npos) //szuka poczatku opisu funkcji
		{
			licznik++; //jesli znajdzie to zwieksza licznik ilosci funkcji w pliku
			szukajFraz(plik, baza, licznikPar, licznikRet);
			plik >> bufor;
			plik >> bufor;
			baza.name = bufor;
			wypiszBaze(baza, licznik, licznikPar, licznikRet);
		}
	} while (getline(plik, bufor));

	plik.close();

    return 0;
}


