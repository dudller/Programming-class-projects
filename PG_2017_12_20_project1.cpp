//POP 2017-12-20 projekt 1 Kus Mateusz IBM 2 172120 œrodowisko DEV-C++ 5.11
#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <cstdlib>


using namespace std;

const int kartywTalii = 52;
const int monetyNaPoczatku = 30;
const int lg = 3; //liczba graczy
const int kwr = 2;//karty w rece
const int kns = 3;//karty na stole

struct karta
{
	int wartosc;
	string kolor;
	string figura;
};

void liczPule(int stawka, int &pula)
{
	pula = stawka * lg;
}

void wypiszStan(int stawka, int &pula)
{
	liczPule(stawka, pula);
	cout << "stawka: " << stawka << "  |  " << "pula: " << pula << endl;
	cout << "######################################" << endl;
}


class gracz
{

	karta *reka;
	int monety;
	int identyfikator;
	bool zwiekszono; //informuje czy gracz zwiêksza³ stawkê

public:
	bool aktywny = true; //informuje czy gracz pasowa³
	int monetywGrze;

	gracz(int m)
	{

		identyfikator = m;
		reka = new karta[kwr + kns];
		monetywGrze = 0;
		monety = monetyNaPoczatku;
	}

	void usun()
	{
		delete[] reka;
	}

	void reset()
	{
		zwiekszono = false;
	}

	void reset(int liczba)
	{
		zwiekszono = false;
		aktywny = true;
		monetywGrze = 0;
	}

	void rozdajKarty(karta losowe[])
	{
		int j = 2;
		reka[0] = losowe[identyfikator - 1];
		reka[1] = losowe[identyfikator - 1 + lg];
		for (int i = (lg*kwr) + 2; i > (lg*kwr) - 1; i--)
		{
			reka[j] = losowe[i];
			j++;
		}
	}

	void wypiszGracza(int tura)
	{
		cout << "Monety: " << monety << endl << "Karty :" << endl;
		if ((tura % 2) == 0)
		{
			for (int i = 0; i < kwr; i++)
			{
				cout << reka[i].kolor << "  " << reka[i].figura << endl;
			}
		}
		else
			for (int i = 0; i < (kwr + kns); i++)
			{
				cout << reka[i].kolor << "  " << reka[i].figura << endl;
			}
	}

	void wypiszKarty(int p)
	{
		if (p == 508) cout << "Poker krolewki!" << endl;
		else if (p > 500)
		{
			for (int i = 0; i < (kwr + kns); i++)
			{
				cout << reka[i].figura << "  ";
			}
			cout << "Poker!" << endl;
		}
		else if (p > 400)
		{
			for (int i = 0; i < (kwr + kns); i++)
			{
				cout << reka[i].figura << "  ";
			}
			cout << "Kareta!" << endl;
		}
		else if (p > 300)
		{
			for (int i = 0; i < (kwr + kns); i++)
			{
				cout << reka[i].figura << "  ";
			}
			cout << "Full!" << endl;
		}
		else if (p > 200)
		{
			for (int i = 0; i < (kwr + kns); i++)
			{
				cout << reka[i].figura << "  ";
			}
			cout << "Dwie pary!" << endl;
		}
		else if (p > 100)
		{
			for (int i = 0; i < (kwr + kns); i++)
			{
				cout << reka[i].figura << "  ";
			}
			cout << "Para!" << endl;
		}
		else
		{
			for (int i = 0; i < (kwr + kns); i++)
			{
				cout << reka[i].figura << "  ";
			}
			cout << endl;
		}
		cout << "###############################" << endl << endl;
	}

	bool czyBankrut(int stawka)
	{
		if (monety < stawka)return true;
		else return false;
	}

	void zwiekszPule(int &tura, int &stawka, int &pula)
	{
		stawka++;
		monety = monety - (stawka - monetywGrze);
		monetywGrze = stawka;
		zwiekszono = true;
		cout << "Gracz " << identyfikator << " zwikeksza stawke." << endl;
	}

	void sprawdz(int &tura, int stawka, int &pula)
	{
		monety = monety - (stawka - monetywGrze);
		monetywGrze = stawka;
		cout << "Gracz " << identyfikator << " sprawdza." << endl;
	}

	void pass(int &tura)
	{
		aktywny = false;
		cout << "Gracz " << identyfikator << " pasuje." << endl;
	}

	void rozgranie(int &tura, int &stawka, int &pula)
	{
		if (aktywny && !czyBankrut(stawka))
		{
			char ruchc;
			cout << "Twoj ruch " << endl;
			wypiszGracza(tura);
			cout << "Wybierz dzialanie:" << endl;
			if (!zwiekszono)
			{
				cout << "1 - zwieksz pule" << endl;
				cout << "2 - sprawdz" << endl;
				cout << "3 - pass" << endl;
				cin >> ruchc;
				int ruch = ruchc;
				switch (ruch)
				{
				case 49:
					zwiekszPule(tura, stawka, pula);
					wypiszStan(stawka, pula);
					break;
				case 50:
					sprawdz(tura, stawka, pula);
					wypiszStan(stawka, pula);
					break;
				default:
					pass(tura);
					wypiszStan(stawka, pula);
				}
			}
			else
			{
				cout << "2 - sprawdz" << endl;
				cout << "3 - pass" << endl;
				cin >> ruchc;
				int ruch = ruchc;
				switch (ruch)
				{
				case 50:
					sprawdz(tura, stawka, pula);
					wypiszStan(stawka, pula);
					break;
				default:
					pass(tura);
					wypiszStan(stawka, pula);
				}
			}
		}
		else
		{
			pass(tura);
			cout << "Spasowales w tej rozgrywce, lub nie stac Cie na dalsz¹ gre." << endl;
			cin.get();
		}

	}

	void rozgranieSi(int &tura, int &stawka, int &pula)
	{
		if (aktywny && !czyBankrut(stawka))
		{
			srand(time(NULL));
			int ruch = rand() % 300;
			if (!zwiekszono)
			{
				if (ruch > 140)  zwiekszPule(tura, stawka, pula);
				else if (ruch >= 20) sprawdz(tura, stawka, pula);
				else pass(tura);
			}
			else
			{
				if (ruch >= 20) sprawdz(tura, stawka, pula);
				else pass(tura);
			}
			wypiszStan(stawka, pula);
		}
		else pass(tura);
	}

	void wygrana(int stawka, int pula, bool &wygrana)
	{
		monety += pula;
		wygrana = true;
	}

	void konfiguracja() //sortuje karty dostêpne dla gracza
	{
		karta bufor;
		for (int j = 0; j < (kwr + 3); j++)
		{
			for (int i = 0; i < (kwr + 2); i++)
			{
				if (reka[i].wartosc > reka[i + 1].wartosc)
				{
					bufor = reka[i + 1];
					reka[i + 1] = reka[i];
					reka[i] = bufor;
				}
			}
		}
	}

	bool czykolor()
	{
		if (reka[0].kolor == reka[1].kolor && reka[0].kolor == reka[2].kolor && reka[0].kolor == reka[3].kolor && reka[0].kolor == reka[4].kolor) return true;
		else return false;
	}

	int punkty()
	{

		int licznik = 0;
		for (int n = 0; n < (kwr + 3); n++)
		{
			for (int i = 0; i < (kwr + 3); i++)
			{
				if (reka[i].wartosc == reka[n].wartosc) licznik++;
			}
		}
		if (licznik == 5) return czyPoker();
		else if (licznik == 7) return (wyznaczWartosc()) + 100;
		else if (licznik == 10) return (wyznaczWartosc()) + 200;
		else if (licznik == 13) return reka[2].wartosc + 300;
		else if (licznik == 17) return reka[2].wartosc + 400;

	}

	int wyznaczWartosc()
	{
		for (int n = 0; n < (kwr + 3); n++)
		{
			for (int i = n + 1; i < (kwr + 3); i++)
			{
				if (reka[i].wartosc == reka[n].wartosc) return reka[n].wartosc;
			}
		}
		return 0;
	}

	int czyPoker()
	{
		if (czykolor())
		{
			if (reka[4].wartosc == (reka[3].wartosc + 1) && reka[3].wartosc == (reka[2].wartosc + 1) && reka[2].wartosc == (reka[1].wartosc + 1) && reka[1].wartosc == (reka[0].wartosc + 1))return reka[0].wartosc + 500;
		}
		else return reka[4].wartosc;
	}
};


void remis(int &stawka, int &pula, bool &wygrana, gracz &g1, gracz &g2)
{
	int przyrost = pula / 2;
	g1.wygrana(stawka, przyrost, wygrana);
	przyrost = pula / 2;
	g2.wygrana(stawka, przyrost, wygrana);
	wygrana = true;
}

void remis(int &stawka, int &pula, bool &wygrana, gracz &g1, gracz &g2, gracz &g3)
{
	int przyrost = pula / 3;
	g1.wygrana(stawka, przyrost, wygrana);
	przyrost = pula / 3;
	g2.wygrana(stawka, przyrost, wygrana);
	przyrost = pula / 3;
	g3.wygrana(stawka, przyrost, wygrana);
	wygrana = true;
}


bool czyWylosowana(int liczby[], int liczba, int j)
{
	int licznik = 0;
	while (licznik < j)
	{
		if (liczby[licznik] == liczba) return true;
		else licznik++;
	}
	return false;

}

void losowanie(karta losowe[], karta talia[])
{
	srand(time(NULL));
	int j = 0;
	int liczby[(kwr*lg) + 3];
	do
	{

		int liczba = (rand() % 52);
		if (!czyWylosowana(liczby, liczba, j))
		{
			losowe[j] = talia[liczba];
			liczby[j] = liczba;
			j++;
		}

	} while (j < ((lg * kwr)) + 3);
}


void generowanieTalii(karta talia[])
{
	for (int i = 0; i < kartywTalii; i++)
	{
		switch (i % 4)
		{
		case 0: talia[i].kolor = "Trefl";
			break;
		case 1: talia[i].kolor = "Kier";
			break;
		case 2: talia[i].kolor = "Karo";
			break;
		default: talia[i].kolor = "Pik";
		}
		for (int i = 0; i < kartywTalii; i++)
		{
			switch (i % 13)
			{
			case 0: talia[i].figura = "2";
				talia[i].wartosc = 1;
				break;
			case 1: talia[i].figura = "3";
				talia[i].wartosc = 2;
				break;
			case 2: talia[i].figura = "4";
				talia[i].wartosc = 3;
				break;
			case 3: talia[i].figura = "5";
				talia[i].wartosc = 4;
				break;
			case 4: talia[i].figura = "6";
				talia[i].wartosc = 5;
				break;
			case 5: talia[i].figura = "7";
				talia[i].wartosc = 6;
				break;
			case 6: talia[i].figura = "8";
				talia[i].wartosc = 7;
				break;
			case 7: talia[i].figura = "9";
				talia[i].wartosc = 8;
				break;
			case 8: talia[i].figura = "D";
				talia[i].wartosc = 9;
				break;
			case 9: talia[i].figura = "W";
				talia[i].wartosc = 10;
				break;
			case 10: talia[i].figura = "Q";
				talia[i].wartosc = 11;
				break;
			case 11: talia[i].figura = "K";
				talia[i].wartosc = 12;
				break;
			default: talia[i].figura = "A";
				talia[i].wartosc = 13;
			}
		}
	}
}


void wypiszKartyNaStol(karta losowe[])
{
	for (int i = (lg*kwr) + 2; i > (lg*kwr) - 1; i--)
	{
		cout << losowe[i].figura << " " << losowe[i].kolor << endl;
	}
}

void kartyNaStol(gracz &czlowiek, gracz &si1, gracz &si2, karta losowe[], int &stawka, int &pula, int &tura, bool &wygrana)
{
	czlowiek.reset();
	si1.reset();
	si2.reset();
	if (czlowiek.aktywny && !si1.aktywny && !si2.aktywny)
	{
		czlowiek.wygrana(stawka, pula, wygrana);
		cout << "Wygrales! Pozostali gracze spasowali." << endl;
		tura += 2;
	}
	else if (!czlowiek.aktywny && si1.aktywny && !si2.aktywny)
	{
		si1.wygrana(stawka, pula, wygrana);
		cout << "Wygral Gracz 2! Pozostali gracze spasowali." << endl;
		tura += 2;
	}
	else if (!czlowiek.aktywny && !si1.aktywny && si2.aktywny)
	{
		si2.wygrana(stawka, pula, wygrana);
		cout << "Wygral Gracz 3! Pozostali gracze spasowali." << endl;
		tura += 2;
	}
	else
	{
		cout << "Karty na stole: " << endl;

		wypiszKartyNaStol(losowe);
		czlowiek.konfiguracja();
		si1.konfiguracja();
		si2.konfiguracja();
		tura++;
	}
	delete[] losowe;
	cout << "######################################" << endl;
}


void wynik(int &stawka, int &pula, int &tura, bool &wygrana, gracz &czlowiek, gracz &si1, gracz &si2)
{
	if (czlowiek.aktywny && !si1.aktywny && !si2.aktywny) { czlowiek.wygrana(stawka, pula, wygrana); cout << "Wygrales! Pozostali gracze spasowali." << endl; }
	else if (!czlowiek.aktywny && si1.aktywny && !si2.aktywny) { si1.wygrana(stawka, pula, wygrana); cout << "Wygral gracz 2! Pozostali gracze spasowali." << endl; }
	else if (!czlowiek.aktywny && !si1.aktywny && si2.aktywny) { si2.wygrana(stawka, pula, wygrana); cout << "Wygral gracz 3! Pozostali gracze spasowali." << endl; }

	else
	{

		int cp = czlowiek.punkty(), s1p = si1.punkty(), s2p = si2.punkty();

		if (cp == s1p && cp == s2p && czlowiek.aktywny && si1.aktywny && si2.aktywny) { remis(stawka, pula, wygrana, czlowiek, si1, si2); cout << "Wszyscy gracze zremisowali kazdy dostaje " << pula / 3 << endl; }
		else
		{
			if (cp >= s1p && czlowiek.aktywny)
			{
				if (cp == s1p && cp >= s2p && si1.aktywny) { remis(stawka, pula, wygrana, czlowiek, si1); cout << "Remis! Ty i Gracz 2 otrzymujecie: " << pula / 2 << endl; }
				else if (cp >= s2p)
				{
					if (cp == s2p && si2.aktywny) { remis(stawka, pula, wygrana, czlowiek, si2); cout << "Remis! Ty i Gracz 2 otrzymujecie " << pula / 2 << endl; }
					else { czlowiek.wygrana(stawka, pula, wygrana); cout << "Wygrywasz!" << endl; }
				}
				else { si2.wygrana(stawka, pula, wygrana); cout << "Wygrywa Gracz 3" << endl; }
			}
			else if (si1.aktywny)
			{
				if (s1p == s2p) { remis(stawka, pula, wygrana, si1, si2); cout << "Remis! Gracz 2 i Gracz 3 otrzymuja " << pula / 2 << endl; }
				else if (s1p > s2p) { si1.wygrana(stawka, pula, wygrana); cout << "Wygrywa Gracz 2!" << endl; }
				else { si2.wygrana(stawka, pula, wygrana); cout << "Wygrywa Gracz 3!" << endl; }
			}
		}
		czlowiek.reset(1);
		si1.reset(1);
		si2.reset(1);
		tura++;
		cout << "######################################" << endl;
	}
}


bool czyRowno(gracz g1, gracz g2, gracz g3) //sprawdza czy ka¿dy aktywny gracz obstawi³ równo
{
	if (g1.aktywny && g2.aktywny && g3.aktywny)
	{
		if (g1.monetywGrze == g2.monetywGrze && g1.monetywGrze == g3.monetywGrze) return true;
		else return false;
	}
	else if (g1.aktywny && g2.aktywny)
	{
		if (g1.monetywGrze == g2.monetywGrze) return true;
		else return false;
	}
	else if (g1.aktywny && g3.aktywny)
	{
		if (g1.monetywGrze == g3.monetywGrze) return true;
		else return false;
	}
	else if (g3.aktywny && g2.aktywny)
	{
		if (g3.monetywGrze == g2.monetywGrze) return true;
		else return false;
	}
	else return true;
}

int main()
{

	karta* talia = new karta[kartywTalii];
	generowanieTalii(talia);
	gracz czlowiek(1);
	gracz si1(2);
	gracz si2(3);
	char odpowiedz; //znak wpisywany na koniec rozgrywki

	do {
		bool wygrana = false; //nie pad³a wygrana
		karta* losowe;
		losowe = new karta[(lg*kwr) + 3];
		losowanie(losowe, talia);
		czlowiek.rozdajKarty(losowe);
		si1.rozdajKarty(losowe);
		si2.rozdajKarty(losowe);
		int tura = 0;
		int stawka = 1, pula = 0;

		do {
			czlowiek.rozgranie(tura, stawka, pula);
			si1.rozgranieSi(tura, stawka, pula);
			si2.rozgranieSi(tura, stawka, pula);
		} while (!czyRowno(czlowiek, si1, si2));

		kartyNaStol(czlowiek, si1, si2, losowe, stawka, pula, tura, wygrana);

		if (!wygrana)
		{
			do {
				czlowiek.rozgranie(tura, stawka, pula);
				si1.rozgranieSi(tura, stawka, pula);
				si2.rozgranieSi(tura, stawka, pula);
			} while (!czyRowno(czlowiek, si1, si2));

			cout << "###############################" << endl;
			cout << "Ty: " << endl;
			czlowiek.wypiszKarty(czlowiek.punkty());
			cout << "Gracz 2: " << endl;
			si1.wypiszKarty(si1.punkty());
			cout << "Gracz 3: " << endl;
			si2.wypiszKarty(si2.punkty());

			wynik(stawka, pula, tura, wygrana, czlowiek, si1, si2);
		}

		czlowiek.reset(1);
		si1.reset(1);
		si2.reset(1);

		cout << "Czy chcesz grac dalej? (tak=t)";
		cin >> odpowiedz;
	} while (odpowiedz == 't' || odpowiedz == 'T');

	delete[] talia;
	czlowiek.usun();
	si1.usun();
	si2.usun();
	return 0;
}

