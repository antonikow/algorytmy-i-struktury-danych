#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
using namespace std;

struct Some_object
{
	int field_1;
	char field_2;
	Some_object(){}
	Some_object(int f1, char f2) : field_1(f1), field_2(f2) {}
	void wypisz()
	{
		cout << field_1 << " " << field_2;
	}

};

template<typename T>
int some_object_cmp_field1(T* so1, T* so2)
{
	int diff = so1->field_1 - so2->field_1;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
	diff = so1->field_2 - so2->field_2;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
}
template<typename T>
int some_object_cmp_field1(T so1, T so2)
{
	int diff = so1.field_1 - so2.field_1;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
	diff = so1.field_2 - so2.field_2;
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else if (diff == 0)
		return 0;
}

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
	~Dynamic_array() { delete [] array; }
	 
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
	T get_data(int indeks)
	{
		if (0 <= indeks && indeks < rozmiar)
		{
			return array[indeks];

		}
		else
			return NULL;

	}
	bool set_data(int indeks, T dodawany)
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
	void bubble_sort(int (*foo)(T, T))
	{
		for (int i = 0; i < licznik - 1; i++)
		{
			for (int j = 0; j < licznik - i - 1 ; j++)
			{
				auto wynik = foo(array[j], array[j + 1]);
				if (wynik == 1)
					swap(array[j], array[j + 1]);
			}
		}
	}
	void wypisz_dynam()
	{
		for (int i = 0; i < licznik; i++)
			cout << array[i]->field_1 << " " << array[i]->field_2 << " rozmiar: " << rozmiar << endl;

	}
	void wypisz_stat()
	{
		for (int i = 0; i < licznik; i++)
		{
			array[i].wypisz();
			cout << " rozmiar: " << rozmiar << endl;
		}
	}
	void czyszczenie()
	{
		 
		delete [] array;
		array = new T[rozmiar];
		rozmiar = 1;
		licznik = 0;
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

int main()
{
	Dynamic_array <Some_object*>* da = new Dynamic_array<Some_object*>();
	/*Some_object* o1 = new Some_object(1, 'a');
	Some_object *o2 = new Some_object(2, 'b');
	Some_object *o3 =new Some_object(3, 'c');
	Some_object *o4 = new Some_object(99, 'y');

	da->dodaj_end(o3);
	da->dodaj_end(o3);
	da->dodaj_end(o3);


	da->wypisz_dynam();
	da->set_data(2, o4);
	cout << endl;
	da->wypisz_dynam();
	cout << endl;
	da->set_data(0, o3);
	da->wypisz_dynam();
	cout << endl;
	da->dodaj_end(o1);
	da->wypisz_dynam();
	cout << endl;
	da->set_data(8,o1);
	da->wypisz_dynam();
	cout << endl;
	da->bubble_sort(some_object_cmp_field1);
	da->wypisz_dynam();
	da->czyszczenie();
	da->wypisz_dynam();
	da->wypisz_dynam();
	*/
	const int order = 7; 
	const int n = pow(10, order);


	clock_t t1 = clock();
	double max_time_per_element = 0.0; 
	vector<float> czas;
	for (int i = 0; i < n; i++)
	{
		Some_object* so = new Some_object(losuj_numer(), losuj_znak()); 

		clock_t t1 = clock();
		da->dodaj_end(so);
		clock_t t2 = clock();
		double time_per_element = (t2 - t1) / (double)CLOCKS_PER_SEC; 
		if (time_per_element > max_time_per_element)
		{
			max_time_per_element = time_per_element; 
			
			czas.push_back(max_time_per_element);
			cout <<  "pod indeksem: " << i << endl;
		}
		
	}

	clock_t t2 = clock();//...
	double czas_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
	
	 
	
	cout << endl;
	cout << "rozmiar: " << da->rozmiar << " ilosc elementow: " << da->licznik << endl;
	cout << endl;
	cout << "czas calkowity: " << czas_calkowity << endl;
	cout << "czas zamortyzowany: " << endl;
	for(auto i = czas.begin(); i != czas.end();i++)
		cout << *i << endl;

	//da->bubble_sort(some_object_cmp_field1);
	//da->wypisz_dynam();


	da->czyszczenie();
	delete da;

	return 0;
}
