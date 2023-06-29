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
	int rozmiar = 0;

	Wezel<T>* czolo = NULL;
	Wezel<T>* ogon = NULL;
	Linked_list() {}
	~Linked_list() { delete czolo; delete ogon; }
	void add_front(T dodawany)
	{
		Wezel<T>* temp = new Wezel<T>(dodawany);
		if (rozmiar == 0)
		{
			czolo = ogon = temp;
		}
		else
		{
			czolo->poprzedni = temp;
			temp->nastepny = czolo;
			czolo = temp;
		}
		rozmiar++;
	}
	void add_end(T dodawany)
	{
		Wezel<T>* temp = new Wezel<T>(dodawany);
		if (rozmiar == 0)
		{
			czolo = ogon = temp;
		}
		else
		{
			temp->poprzedni = ogon;
			ogon->nastepny = temp;
			ogon = temp;
		}
		rozmiar++;
	}
	void usun_end()
	{
		if (rozmiar == 0)return;
		else if (rozmiar == 1)
		{
			czolo = ogon = NULL;
			rozmiar--;
		}
		else
		{
			Wezel<T>* temp = ogon;
			ogon->poprzedni->nastepny = NULL;
			ogon = ogon->poprzedni;
			delete temp;
			rozmiar--;
		}

	}
	void usun_front()
	{
		if (rozmiar == 0)return;
		else if (rozmiar == 1)
		{
			czolo = ogon = NULL;
			rozmiar--;
		}
		else
		{
			Wezel<T>* temp = czolo;
			czolo->nastepny->poprzedni = NULL;
			czolo = czolo->nastepny;
			delete temp;
			rozmiar--;
		}
	}
	T get_dane(int indeks)
	{
		if (0 <= indeks && indeks < rozmiar)
		{
			Wezel<T>* temp = czolo;
			for (int i = 0; i < indeks; i++)
			{
				temp = temp->nastepny;
			}
			return temp->dana;
		}
		//zwracam niepowodzenie
		else return NULL;
	}
	bool set_dane(int indeks, T nowe_dane)
	{

		if ((0 <= indeks) && (indeks < rozmiar))
		{
			Wezel<T>* temp = czolo;
			for (int i = 0; i < indeks; i++)
			{
				temp = temp->nastepny;
			}
			temp->dana = nowe_dane;
			return true;

		}
		//niepowodzenie 
		else return false;

	}
	Wezel<T>* comp_wyszukanie(T dane_wzorcowe, int (*foo)(T, T))
	{
		Wezel<T>* temp = czolo;
		int wynik;

		for (int i = 0; i < (rozmiar); i++)
		{
			wynik = foo(dane_wzorcowe, temp->dana);
			if (wynik == 0) return temp;
			temp = temp->nastepny;

		}
		return NULL;
	}
	bool add_wymusz_porzadku(T dodawany, int (*foo)(T, T))
	{
		Wezel<T>* temp = czolo;
		int wynik;

		for (int i = 0; i < rozmiar; i++)
		{
			wynik = foo(dodawany, temp->dana);
			//wstawiam przed czyms
			if (wynik < 0)
			{
				//dodaj przed 
				if (temp == czolo)
				{
					add_front(dodawany);
					return true;

				}
				else if (temp == ogon)
				{
					//stworzenie dodawanego elementu
					Wezel<T>* stworzony = new Wezel<T>(dodawany); //wstawiam przed temp

					stworzony->nastepny = ogon;
					stworzony->poprzedni = ogon->poprzedni;
					ogon->poprzedni = stworzony;
					stworzony->poprzedni->nastepny = stworzony;
					rozmiar++;
					return true;
				}
				else
				{
					Wezel<T>* stworzony = new Wezel<T>(dodawany); //wstawiam przed temp

					stworzony->nastepny = temp;
					stworzony->poprzedni = temp->poprzedni;
					temp->poprzedni = stworzony;
					stworzony->poprzedni->nastepny = stworzony;
					rozmiar++;
					return true;
				}

			}
			else if (wynik == 0)
			{
				//dodaj przed 
				if (rozmiar == 1)
				{
					add_front(dodawany);
					return true;
				}
				if (temp == czolo)
				{
					add_front(dodawany);
					return true;
				}
				else if (temp == ogon)
				{
					//stworzenie dodawanego elementu
					Wezel<T>* stworzony = new Wezel<T>(dodawany); //wstawiamy przed temp

					stworzony->nastepny = ogon;
					stworzony->poprzedni = ogon->poprzedni;
					ogon->poprzedni = stworzony;
					stworzony->poprzedni->nastepny = stworzony;
					rozmiar++;
					return true;
				}
				else
				{
					Wezel<T>* stworzony = new Wezel<T>(dodawany); //wstawiamy przed temp

					stworzony->nastepny = temp;
					stworzony->poprzedni = temp->poprzedni;
					temp->poprzedni = stworzony;
					stworzony->poprzedni->nastepny = stworzony;
					rozmiar++;
					return true;
				}
			}
			else if (rozmiar == 1)
			{
				add_end(dodawany);
				return true;
			}
			//zaden warunek nie zrealizowany wiec wynik porownania dodatni petla dalej szuka elementu ktory jest wiekszy od dodawanego
			temp = temp->nastepny;
		}
		//jesli nie znaleziono mniejszego elementu przy dlugosci wiekszej niz jeden wezel
		add_end(dodawany);
		return true;
	}
	bool znajdz_i_usun(T dane_wzorcowe, int (*foo)(T, T))
	{
		auto zwrocone = comp_wyszukanie(dane_wzorcowe, foo);


		if (zwrocone == NULL) return false;    //nie znaleziono

		else if (zwrocone == ogon)
		{
			usun_end();
			return true;
		}
		else if (zwrocone == czolo)
		{
			usun_front();
			return true;
		}
		else
		{
			zwrocone->poprzedni->nastepny = zwrocone->nastepny;
			zwrocone->nastepny->poprzedni = zwrocone->poprzedni;

			delete zwrocone;
			rozmiar--;
			return true;

		}
	}
	//dla dynamicznego parametru szablonu
	void wypisz_dynam() //pierowtny formt wypisz dynam w wypisz stat
	{
		Wezel<T>* temp = czolo;
		for (int i = 0; i < rozmiar; i++)
		{
			cout << temp->dana->field_1 << " ";
			cout << temp->dana->field_2 << "    ";
			temp = temp->nastepny;
		}
	}
	void wypisz_int()//dynam
	{
		Wezel<T>* temp = czolo;
		for (int i = 0; i < rozmiar; i++)
		{
			cout << temp->dana << " ";

			temp = temp->nastepny;
			//cout << endl;
		}
		cout << endl;
	}

	void czyszczenie()
	{
		Wezel<T>* temp = czolo;
		while (czolo != NULL)
		{
			usun_front();
		}
	}
};



#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
using namespace std;

template<typename P>
struct Binary_heap
{
	Binary_heap() {}
	Binary_heap(P* arr, int r, int (*komparator)(P, P), bool top_down)
	{
		if (top_down)
			for (int i = 0; i < r; i++)
				heapup_in_constructor(arr, i, komparator);
		else
			for (int i = r - 1; i >= 0; i--)
				heapdown_in_constructor(arr, i, komparator, r);
	}
	void sort(P* arr, int (*komparator)(P, P), int r)
	{
		int temp_rozmiar = r;
		for (int i = 0; i < r; i++)
		{
			zamien(0, temp_rozmiar - 1, arr);
			temp_rozmiar--;
			heapdown_in_constructor(arr, 0, komparator, temp_rozmiar);
		}
	}
	void zamien(int i1, int i2, P* arr)
	{
		P temp = arr[i1];
		arr[i1] = arr[i2];
		arr[i2] = temp;
	}

	void heapup_in_constructor(P* arr, int ind, int (*komparator)(P, P))
	{
		int rodzic = rodzic_ind(ind);
		int wynik_porownania = komparator(arr[ind], arr[rodzic]);
		if (wynik_porownania == 1)
		{
			zamien(ind, rodzic, arr);
			heapup_in_constructor(arr, rodzic, komparator);
		}
	}
	void heapdown_in_constructor(P* arr, int ind, int (*komparator)(P, P), int rr)
	{
		int lewyind = lewy_ind(ind);
		int leftflag = 0;
		if (lewyind < rr && komparator(arr[ind], arr[lewyind]) == -1)
			leftflag = 1;

		int prawyind = prawy_ind(ind);
		int rightflag = 0;
		if (prawyind < rr && komparator(arr[ind], arr[prawyind]) == -1)
			rightflag = 1;

		if (leftflag == 1 || rightflag == 1)
		{
			int wiekszy;
			if (!(prawyind < rr))
			{
				wiekszy = lewyind;
			}
			else
			{
				if (komparator(arr[lewyind], arr[prawyind]) == -1)
					wiekszy = prawyind;
				else
					wiekszy = lewyind;
			}
			zamien(wiekszy, ind, arr);
			heapdown_in_constructor(arr, wiekszy, komparator, rr);
		}
	}
	int rodzic_ind(int indeks)
	{
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
};


#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <vector>
 
using namespace std;

struct Some_object
{
	double field_1;
	char field_2;
	Some_object() {}
	Some_object(double f1, char f2) : field_1(f1), field_2(f2) {}
	void wypisz()
	{
		cout << field_1 << " " << field_2;
	}
};

template<typename P>
int some_object_cmp_field1(P* so1, P* so2)
{
	double diff = so1->field_1 - so2->field_1;
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
	double diff = so1.field_1 - so2.field_1;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
}

int int_cmp(int o1, int o2)
{
	int diff = o1 - o2;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
}


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
void counting_sort(int* arr, int n, int m)
{
	int *counts = new int[m];
	for (int i = 0; i < m; i++)
	{
		counts[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		counts[arr[i]]++;
	}
	int k = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < counts[i]; j++)
		{
			arr[k++]=i;
		}
	}
	delete [] counts;
}

int cmp_int(int o1, int o2)
{
	int diff = o1 - o2;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
}
void bucket_sort(int* arr, int n, int m)
{
	 
	Linked_list<int>* kubelki = new Linked_list<int>[n];
	if (n == 0)
		return;
	int w = m / n;
	for (int i = 0; i < n; i++)
	{
		int nr_kubelka = floor(arr[i] / w);
		kubelki[nr_kubelka].add_wymusz_porzadku(arr[i], cmp_int);
	}
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < kubelki[i].rozmiar; j++)
		{
			arr[k++] = kubelki[i].get_dane(j);
		}
	}
	for (int i = 0; i < n; i++)
		kubelki[i].czyszczenie();
	delete[] kubelki;
}

template<typename P>
int komp(P zm1, P zm2)
{
	int diff = zm1 - zm2;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
}

template<typename T>
double komp_float_field1(T ob)
{
	return ob->field_1;
}

template<typename T>
void bucket_sort(T* arr, int n, double m, double (*komp_field)(T)    ,  int (*kompsort)(T, T))
{
	Linked_list<T>* kubelki = new Linked_list<T>[n];
	if (n == 0)
		return;
	double w = m / n;
	for (int i = 0; i < n; i++)
	{
		int nr_kubelka = floor(komp_field(arr[i]) / w);
		if (nr_kubelka >= n || nr_kubelka < 0)
		{
			return;
		}
		kubelki[nr_kubelka].add_wymusz_porzadku(arr[i], kompsort);
	}
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < kubelki[i].rozmiar; j++)
		{
			arr[k++] = kubelki[i].get_dane(j);
		}
	}
	for (int i = 0; i < n; i++)
		kubelki[i].czyszczenie();
	delete[] kubelki;
}

int main()
{
	
	srand(time(NULL));



	const int MAX_ORDER = 6; // maksymalny rzad wielkosci sortowanych danych
	const int m = (int)pow(10, 7);  
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		cout << "========================   " << o << "   =========================" << endl;
		cout << endl;
		const int n = (int)pow(10, o); // rozmiar tablicy z danymi
		int* array1 = new int[n];
		for (int i = 0; i < n; i++)
		{
			int rand_val = rand() % m; 
				array1[i] = rand_val;
		}


		cout << "=======================  SKROT  ========================" << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << array1[i] << endl;
		}
		int* array2 = new int[n];
		int* array3 = new int[n];
		memcpy(array2, array1, n * sizeof(int)); 
		memcpy(array3, array1, n * sizeof(int)); 


		cout << "=======================  COUNTING SORT  ========================" << endl;
		clock_t t1 = clock();
		counting_sort(array1, n, m);
		clock_t t2 = clock();
		double time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "czas calkowity dodawania: " << time_calkowity << " sekund" << endl;
		cout << "czas sredni dodawnia: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << array1[i] << endl;
		}


		cout << "=======================  HEAP SORT  ========================" << endl;
		t1 = clock();
		Binary_heap <int >* bh = new Binary_heap <int >(array2, n, int_cmp, true); 
		bh->sort(array2, int_cmp, n);
		t2 = clock();
	    time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "czas calkowity dodawania: " << time_calkowity << " sekund" << endl;
		cout << "czas sredni dodawnia: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;
		
		for (int i = 0; i < 10; i++)
		{
			cout << array2[i] << endl;
		}


		cout << "=======================  BUCKET SORT  ========================" << endl;
		t1 = clock();
		bucket_sort(array3, n, m); 
		t2 = clock();
		time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "czas calkowity dodawania: " << time_calkowity << " sekund" << endl;
		cout << "czas sredni dodawnia: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << array3[i] << endl;
		}
		

		int zgodne = 1;
		for (int i = 0; i < n; i++)
		{
			if (array1[i] != array2[i] || array2[i] != array3[i] || array3[i] != array1[i])
			{
				zgodne = 0;
				break;
			}
		}
		if(zgodne)
			cout << "TABLICE SA ZGODNE" << endl;
		else
			cout << "TABLICE NIE SA ZGODNE" << endl;
				
		delete[] array1, array2, array3;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
	}

	
	/*
	srand(time(NULL));
	const int MAX_ORDER = 7; // maksymalny rzad wielkosci sortowanych danych
	const double m_double = (double)RAND_MAX;; // mianownik przy ustalaniu losowej liczby zmiennoprzecinkowej
	const double m = 1.0;

	for (int o = 1; o <= MAX_ORDER; o++)
	{
		cout << "========================   " << o << "   =========================" << endl;
		const int n = (int)pow(10, o); // rozmiar tablicy z danymi
		Some_object** array1 = new Some_object * [n];
		for (int i = 0; i < n; i++)
		{
			Some_object* so = new Some_object();
			so->field_1 = rand() / (double)RAND_MAX; // przykladowy sposob wylosowania pola typu double(ktore bedzie stanowilo klucz sortowania)
			so->field_2 = 'a' + rand() % 26; // przykladowy sposob wylosowania pola typu char
			array1[i] = so;
			if (so->field_1 == 1)
			{
				//cout << "WYLOSOWANO 1 !" << endl;
				so->field_1 = 1 - 0.5;
			}
		}
		cout << "=======================  SKROT  ========================" << endl;
		for (int i = 0; i < 10; i++)
		{
			array1[i]->wypisz();
			cout << endl;

		}
		Some_object** array2 = new Some_object * [n];
		memcpy(array2, array1, n * sizeof(Some_object*)); 

		cout << "=======================  HEAP SORT  ========================" << endl;
		clock_t t1 = clock();
		Binary_heap < Some_object*>* bh = new Binary_heap < Some_object*>(array1, n, some_object_cmp_field1,true); 
		bh->sort(array1, some_object_cmp_field1, n);
		clock_t t2 = clock();
		double time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "czas calkowity dodawania: " << time_calkowity << " sekund" << endl;
		cout << "czas sredni dodawnia: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;
		for (int i = 0; i < 10; i++)
		{
			array1[i]->wypisz();
			cout << endl;

		}
		


		cout << "=======================  BUCKET SORT  ========================" << endl;
		t1 = clock();
		bucket_sort(array2, n, m, komp_float_field1, some_object_cmp_field1);
		t2 = clock();
		time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "czas calkowity dodawania: " << time_calkowity << " sekund" << endl;
		cout << "czas sredni dodawnia: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;
		for (int i = 0; i < 10; i++)
		{
			array2[i]->wypisz();
			cout << endl;

		}

		int zgodne = 1;
		for (int i = 0; i < n; i++)
		{
			if (komp_float_field1(array1[i]) != komp_float_field1(array2[i]))
			{
				zgodne = 0;
				break;
			}
		}
		if (zgodne)
			cout << "TABLICE SA ZGODNE" << endl;
		else
			cout << "TABLICE NIE SA ZGODNE "<< endl;

		delete[] array1, array2;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
	}

	*/
	
	
	return 0;
}

