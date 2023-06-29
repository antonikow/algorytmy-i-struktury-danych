#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

template<typename T>
struct Wezel
{
	Wezel<T>* poprzedni = NULL;
	T dana;
	Wezel<T>* nastepny = NULL;
	Wezel(T podana) { dana = podana; }
};

template<typename T>
struct Linked_list
{
	int rozmiarlisty = 0;

	Wezel<T>* czolo = NULL;
	Wezel<T>* ogon = NULL;
	Linked_list() {}
	~Linked_list() { czyszczenie(); delete czolo; delete ogon; }
	void add_front(T dodawany) //dodaj element
	{
		Wezel<T>* temp = new Wezel<T>(dodawany);
		if (rozmiarlisty == 0)
		{
			czolo = ogon = temp;
		}
		else
		{
			czolo->poprzedni = temp;
			temp->nastepny = czolo;
			czolo = temp;
		}
		rozmiarlisty++;
	}
	void add_end(T dodawany)
	{
		Wezel<T>* temp = new Wezel<T>(dodawany);
		if (rozmiarlisty == 0)
		{
			czolo = ogon = temp;
		}
		else
		{
			temp->poprzedni = ogon;
			ogon->nastepny = temp;
			ogon = temp;
		}
		++rozmiarlisty;
	}
	void usun_end()
	{
		if (rozmiarlisty == 0)return;
		else if (rozmiarlisty == 1)
		{
			czolo = ogon = NULL;
			rozmiarlisty--;
		}
		else
		{
			Wezel<T>* temp = ogon;
			ogon->poprzedni->nastepny = NULL;
			ogon = ogon->poprzedni;
			delete temp;
			rozmiarlisty--;
		}
	}
	void usun_front()
	{
		if (rozmiarlisty == 0)return;
		else if (rozmiarlisty == 1)
		{
			czolo = ogon = NULL;
			rozmiarlisty--;
		}
		else
		{
			Wezel<T>* temp = czolo;
			czolo->nastepny->poprzedni = NULL;
			czolo = czolo->nastepny;
			delete temp;
			rozmiarlisty--;
		}
	}
	T get_dane(int indeks)
	{
		if (0 <= indeks < rozmiarlisty)
		{
			Wezel<T>* temp = czolo;
			for (int i = 0; i < indeks; i++)
			{
				temp = temp->nastepny;
			}
			return temp->dana;
		}
		else
			return NULL;
	}
	bool usun_wezel(Wezel<T>* w)
	{
		w->poprzedni->nastepny = w->nastepny;
		w->nastepny->poprzedni = w->poprzedni;
		delete w;
		rozmiarlisty--;
		return true;
	}
	void wypisz_lista()
	{
		Wezel<T>* temp = czolo;
		for (int i = 0; i < rozmiarlisty; i++)
		{
			temp->dana->wypisz();
			temp = temp->nastepny;
			if (i != rozmiarlisty - 1)cout << " -> ";
		}
	}
	void czyszczenie()
	{
		while (czolo != NULL)
		{
			usun_end();
		}
	}
};






#include <iostream>
#include <time.h>
#include <cstdlib>
#include<typeinfo>
#include <string>
#include <math.h>

using namespace std;

template<typename K>
struct Obiekt
{
	string klucz;
	K wartosc;
	Obiekt() {}
	Obiekt(string f1, K f2) : klucz(f1), wartosc(f2) {}
	void wypisz()
	{
		cout << klucz << " " << wartosc;
	}
};


template<typename K>
struct Hash_table
{
	int rozmiar = 1;
	int ilosc_calkowita = 0;
	float wspolczynnik = 2.0;
	float napelnienie = 0.75;

	Linked_list<Obiekt<K>*>* array;
	Hash_table()
	{
		array = new Linked_list<Obiekt<K>*>[rozmiar];
	}
	~Hash_table() { delete[] array; }

	void rehash()
	{
		//cout << "POWIEKSZ ilosc obiektow: "<<ilosc_calkowita << endl;
		rozmiar = rozmiar * wspolczynnik;
		Linked_list<Obiekt<K>*>* temp = new Linked_list<Obiekt<K>*>[rozmiar];
		for (int i = 0; i < rozmiar / 2; i++)
		{
			Wezel<Obiekt<K>*>* node = array[i].czolo;
			for (int j = 0; j < array[i].rozmiarlisty; j++)
			{
				int indeks = hash_function(node->dana->klucz);
				temp[indeks].add_end(node->dana);
				node = node->nastepny;
			}
		}
		delete[] array;
		array = temp;
	}


	void hash_dodaj(Obiekt<K>* dodawany)
	{
		if (rozmiar * napelnienie <= ilosc_calkowita) // potem spr czy nie mozna usunac 2 elem war
			rehash();
		int indeks = hash_function(dodawany->klucz);

		auto temp = array[indeks].czolo;
		for (int i = 0; i < array[indeks].rozmiarlisty; i++)
		{
			if (temp->dana->klucz.compare(dodawany->klucz) == 0)
			{
				temp->dana->wartosc = dodawany->wartosc;
				return;
			}
			temp = temp->nastepny;
		}
		array[indeks].add_end(dodawany);	//zwieksza licznik rozmiarlisty	
		++ilosc_calkowita;
	}

	Wezel<Obiekt<K>*>* znajdz(string szukany_klucz)
	{
		int pozycja = hash_function(szukany_klucz);
		auto temp = array[pozycja].czolo;
		for (int i = 0; i < array[pozycja].rozmiarlisty; i++)
		{
			if (temp->dana->klucz.compare(szukany_klucz) == 0) return temp;
			temp = temp->nastepny;
		}
		return NULL;
	}
	bool usun(string szukany_klucz)
	{
		auto wezel = znajdz(szukany_klucz);
		if (wezel == NULL)return 0;
		int pozycja = hash_function(szukany_klucz);
		if (wezel == array[pozycja].czolo) array[pozycja].usun_front();
		else if (wezel == array[pozycja].ogon)array[pozycja].usun_end();
		else
			array[pozycja].usun_wezel(wezel);
		return 1;
	}

	void czyszczenie()
	{
		delete[] array;
		array = new Linked_list<Obiekt<K>*>[rozmiar];
		rozmiar = 1;
		ilosc_calkowita = 0;
	}

	void wypisz_calosc()
	{
		cout << "maksymalny rozmiar: " << rozmiar << endl;
		cout << "ilosc calkowita: " << ilosc_calkowita << endl;
		cout << endl;
		cout << "table:" << endl;
		int min = 1000;
		int max = 0;
		int licz = 0;
		for (int i = 0; i < rozmiar; i++)
		{
			if (array[i].rozmiarlisty == 0)continue;
			++licz;
			if (array[i].rozmiarlisty > max)max = array[i].rozmiarlisty;
			if (array[i].rozmiarlisty < min)min = array[i].rozmiarlisty;
			cout << array[i].rozmiarlisty << ": ";
			array[i].wypisz_lista();
			cout << endl;
		}
		cout << endl;
		cout << "maksymalny rozmiar listy: " << max << endl;
		cout << "minimalny rozmiar listy: " << min << endl;
		cout << "niepuste listy: " << licz << endl;
		cout << "sredni rozmiar listy: " << (float)ilosc_calkowita / licz << endl;

	}
	void wypisz_skrot()
	{
		int licz = 0;
		cout << "table:" << endl;
		for (int i = 0; i < rozmiar; i++)
		{
			if (licz == 5)break;
			if (array[i].rozmiarlisty == 0)continue;
			++licz;
			cout << array[i].rozmiarlisty << ": ";
			array[i].wypisz_lista();
			cout << endl;
		}
		cout << endl;
	}
	void wypisz_info()
	{
		cout << "maksymalny rozmiar: " << rozmiar << endl;
		cout << "ilosc calkowita: " << ilosc_calkowita << endl;

		int min = 1000;
		int max = 0;
		int licz = 0;
		for (int i = 0; i < rozmiar; i++)
		{
			if (array[i].rozmiarlisty == 0)continue;
			++licz;
			if (array[i].rozmiarlisty > max)max = array[i].rozmiarlisty;
			if (array[i].rozmiarlisty < min)min = array[i].rozmiarlisty;
		}
		cout << "maksymalny rozmiar listy: " << max << endl;
		cout << "minimalny rozmiar listy: " << min << endl;
		cout << "niepuste listy: " << licz << endl;
		cout << "sredni rozmiar listy: " << (float)ilosc_calkowita / licz << endl;
	}

	int hash_function(string napis)
	{
		float wynik = 0;
		for (int i = 0; i < napis.length(); i++)
		{
			int zn = napis[i];
			wynik += zn * pow(31, napis.length() - i - 1);
		}
		int zwrot = fmod(wynik, rozmiar);
		//cout << "wynik to : " << zwrot << endl;
		if (zwrot < 0)
			return -1;
		return zwrot;
	}
};


int losuj_numer()
{
	int wylosnum = rand() % 10000 + 1;
	return wylosnum;
}
char losuj_znak()
{
	char znak = 'a' + rand() % 25;
	return znak;
}
string losuj_string()
{
	string str;
	for (int i = 0; i < 4; i++)
		str.push_back(losuj_znak());
	return str;
}

int main()
{
	/*
	//przez zmiany w tworzeniu eksperymentu moze nie dzialac
	Obiekt<int> *o4 = new Obiekt<int>("asd", 4);
	Obiekt<int> *o5 = new Obiekt<int>("ost", 5);


	Obiekt<int>* o6 = new Obiekt<int>("ugcl", 6);
	Obiekt<int> *o7 = new Obiekt<int>("XYZ", 7);
	Hash_table<int> *hashtab = new Hash_table<int>;

	srand(time(NULL));
	for (int i = 0; i < 511; i++)
	{
		Obiekt<int>* o65 = new Obiekt<int>(losuj_string(), losuj_numer());
		hashtab->hash_dodaj(o65);

	}


	hashtab->wypisz_dynam();

	hashtab->czyszczenie();
	*/
	const int MAX_ORDER = 7;
	Hash_table<int>* hashtab = new Hash_table<int>;
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		cout << "========================   " << o << "   =========================" << endl;
		cout << endl;
		const int n = pow(10, o);

		clock_t t1 = clock();
		for (int i = 0; i < n; i++)
		{
			Obiekt<int>* o65 = new Obiekt<int>(losuj_string(), i);
			hashtab->hash_dodaj(o65); // klucze losowe 6- znakowe 
		}
		clock_t t2 = clock();
		double time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "czas calkowity dodawania: " << time_calkowity << " sekund" << endl;
		cout << "czas sredni dodawnia: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;

		cout << "=======================  SKROT  ========================" << endl;
		hashtab->wypisz_skrot();

		const int m = pow(10, 4);
		int hits = 0;
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			Wezel <Obiekt<int>*>* entry = hashtab->znajdz(losuj_string()); // wyszukiwanie wg losowego klucza
			if (entry != NULL)
				hits++;
		}
		t2 = clock();
		cout << "TRAFIENIA: " << hits << endl;
		time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "czas calkowity szykania: " << time_calkowity << " sekund" << endl;
		cout << "czas sredni szukania: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;


		cout << "=====================  STATYSTYKI  =====================" << endl;
		hashtab->wypisz_info();
		hashtab->czyszczenie();
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
	}
	delete hashtab;
	return 0;
}
