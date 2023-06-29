#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;


template<typename T>
struct Dynamic_array
{
	int rozmiar = 1;
	int licznik = 0;

	float wspolczynnik = 2;

	T* array;
	Dynamic_array()
	{
		array = new T[rozmiar];
	}
	~Dynamic_array() { delete[] array; }

	void powieksz()
	{
		int n = rozmiar * wspolczynnik;
		T* temp = new T[n];
		for (int i = 0; i < licznik; i++)temp[i] = array[i];
		delete[] array;
		array = temp;
		rozmiar = rozmiar * wspolczynnik;

	}
	bool dodaj_end(T dodawany)
	{
		if (licznik == rozmiar)
			powieksz();
		array[licznik] = dodawany;
		++licznik;
		return 1;
	}
	T get_data_dynam(int indeks)
	{
		if (0 <= indeks && indeks < rozmiar)
		{
			return array[indeks];
		}
		else
			return NULL;
	}
	T get_data_stat(int indeks)
	{
		if (0 <= indeks && indeks < rozmiar)
		{
			return array[indeks];
		}
		else
		{
			T pustyobiekt = T();
			return pustyobiekt;
		}
	}
	bool insert_data(int indeks, T dodawany)
	{
		if (licznik == rozmiar)
		{
			powieksz();
		}
		if (indeks == licznik)
		{
			array[licznik] = dodawany;
			++licznik;
			return 1;
		}
		if ((0 <= indeks) && (indeks < licznik))
		{
			for (int i = licznik; i != indeks; i--)
			{
				array[i] = array[i - 1];
			}
			array[indeks] = dodawany;
			++licznik;
			return 1;
		}
		return 0;
	}
	void kontrola_rozmiaru()
	{
		if (rozmiar != 1)
		{
			if (licznik <= rozmiar / wspolczynnik)
			{
				int n = rozmiar / wspolczynnik;
				T* temp = new T[n];
				for (int i = 0; i < licznik; i++)temp[i] = array[i];
				delete[] array;
				array = temp;
				rozmiar = rozmiar / wspolczynnik;
			}
		}
	}
	void wypisz_dynam()
	{
		for (int i = 0; i < licznik; i++)
			cout << array[i]->field_1 << " " << array[i]->field_2 << " rozmiar: " << rozmiar << endl;
	}
	void wypisz_dynam_zindeksem()
	{
		for (int i = 0; i < licznik; i++)
			cout << i << ": " << array[i]->field_1 << " " << array[i]->field_2 << endl;
	}
	void wypisz_dynam_skrot()
	{
		for (int i = 0; i < licznik; i++)
		{
			if (i == 10)
				break;
			cout << i << ": " << array[i]->field_1 << " " << array[i]->field_2 << endl;
		}
	}
	void wypisz_stat()
	{
		for (int i = 0; i < licznik; i++)
		{
			array[i].wypisz();
			cout << " rozmiar: " << rozmiar << endl;
		}
	}
	void wypisz_stat_skrot()
	{
		for (int i = 0; i < licznik; i++)
		{
			if (i == 10)
				break;
			cout << i << ": " << array[i].field_1 << " " << array[i].field_2 << endl;
		}
	}
	void wypisz_stat_zindeksem()
	{
		for (int i = 0; i < licznik; i++)
			cout << i << ": " << array[i].field_1 << " " << array[i].field_2 << endl;
	}
	void czyszczenie()
	{
		delete[] array;
		array = new T[rozmiar];
		rozmiar = 1;
		licznik = 0;
	}
	int zamien(int ind1, int ind2)
	{
		if (ind2 >= licznik || ind2 < 0)
		{
			cout << "blad" << endl; return 0;
		}
		else if (ind1 >= licznik || ind1 < 0)
		{
			cout << "blad" << endl; return 0;
		}
		else
		{
			T temp = array[ind1];
			array[ind1] = array[ind2];
			array[ind2] = temp;
			return 1;
		}
	}
};

int losuj_numer()
{
	int wylosnum = rand() % 100 + 1;
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
	for (int i = 0; i < 3; i++)
		str.push_back(losuj_znak());
	return str;
}




#include <iostream>
#include <cmath>
 

struct Some_object
{
	int field_1;
	char field_2;
	Some_object() {}
	Some_object(int f1, char f2) : field_1(f1), field_2(f2) {}
	void wypisz()
	{
		cout << field_1 << " " << field_2;
	}
};

template<typename P>
int some_object_cmp_field1(P* so1, P* so2)
{
	int diff = so1->field_1 - so2->field_1;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
}
template<typename P>
int some_object_cmp_field1(P so1, P so2)
{
	int diff = so1.field_1 - so2.field_1;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
}

template<typename P>
struct Binary_heap
{
	Dynamic_array<P>* tab = new Dynamic_array<P>();
	~Binary_heap()
	{
		delete tab;
	}
	int BH_dodaj_end(P dod, int (*komparator)(P, P))
	{
		tab->dodaj_end(dod);
		auto dod_indeks = tab->licznik - 1;
		przekopc_gora(dod_indeks, komparator);
		return 1;
	}
	P poll_dynam(int (*komparator)(P, P))
	{
		if (tab->licznik == 0)
			return NULL;
		else
		{
			P odlaczony = tab->array[0];
			tab->array[0] = tab->array[tab->licznik - 1];
			tab->array[tab->licznik - 1] = P();
			--tab->licznik;
			przekopc_dol(0, komparator);
			tab->kontrola_rozmiaru();
			return odlaczony;
		}

	}
	P poll_stat(int (*komparator)(P, P))
	{
		if (tab->licznik == 0)
			return P();
		else
		{
			P odlaczony = tab->array[0];
			tab->array[0] = tab->array[tab->licznik - 1];
			tab->array[tab->licznik - 1] = P();
			--tab->licznik;
			przekopc_dol(0, komparator);
			tab->kontrola_rozmiaru();
			return odlaczony;
		}
	}
	int przekopc_gora(int ind, int (*komparator)(P, P))
	{
		int rodzic = rodzic_ind(ind);
		if (rodzic == -1)return 1;
		int wynik_porownania = komparator(tab->array[ind], tab->array[rodzic]);
		if (wynik_porownania == 1)
			tab->zamien(ind, rodzic);
		przekopc_gora(rodzic, komparator);
	}
	void przekopc_dol(int ind, int (*komparator)(P, P))
	{
		int lewyind = lewy_ind(ind);
		int leftflag = 0;
		if (lewyind < tab->licznik && komparator(tab->array[ind], tab->array[lewyind]) == -1)
			leftflag = 1;

		int prawyind = prawy_ind(ind);
		int rightflag = 0;
		if (prawyind < tab->licznik && komparator(tab->array[ind], tab->array[prawyind]) == -1)
			rightflag = 1;

		if (leftflag == 1 || rightflag == 1)
		{
			int wiekszy;
			if (!(prawyind < tab->licznik))
			{
				wiekszy = lewyind;
			}
			else
			{
				if (komparator(tab->array[lewyind], tab->array[prawyind]) == -1)
					wiekszy = prawyind;
				else
					wiekszy = lewyind;
			}
			tab->zamien(wiekszy, ind);
			przekopc_dol(wiekszy, some_object_cmp_field1);
		}
	}
	int rodzic_ind(int indeks)
	{
		if (indeks <= 0 || indeks > (tab->licznik - 1))
			return -1;
		else
			return (indeks - 1) / 2;
	}
	int lewy_ind(int indeks)
	{
		return 2 * indeks + 1;
	}
	int prawy_ind(int indeks)
	{
		return 2 * indeks + 2;
	}
	void BH_czyszczenie()
	{
		tab->czyszczenie();
	}
};
int main()
{
	srand(time(NULL));
	const int MAX_ORDER = 7;
	Binary_heap <Some_object*>* bh = new Binary_heap <Some_object* >();
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		cout << "========================   " << o << "   =========================" << endl;
		cout << endl;
		const int n = pow(10, o);

		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			Some_object* so = new Some_object(losuj_numer(), losuj_znak());
			bh->BH_dodaj_end(so, some_object_cmp_field1);
		}
		clock_t t2 = clock();

		double time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "czas calkowity dodawania: " << time_calkowity << " sekund" << endl;
		cout << "czas sredni dodawnia: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;
		cout << "=======================  SKROT  ========================" << endl;
		bh->tab->wypisz_dynam_skrot();


		t1 = clock();
		for (int i = 0; i < n; i++) {
			Some_object* polled = bh->poll_dynam(some_object_cmp_field1);
			if (n < 11)
			{
				cout << "pop: "; polled->wypisz(); cout << endl;
			}
			delete polled;
		}
		t2 = clock();
		// wypis na ekran aktualnej postaci kopca ( kopiec pusty ) oraz pomiarow czasowych

		time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "czas calkowity poll: " << time_calkowity << " sekund" << endl;
		cout << "czas sredni poll: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;
		cout << "=======================  CALOSC ========================" << endl;
		bh->tab->wypisz_dynam_zindeksem();
		bh->BH_czyszczenie();
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
	}
	delete bh;

	return 0;
}

