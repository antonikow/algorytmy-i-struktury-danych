#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

//dana
struct Some_object
{
    int field_1;
    char field_2;

    Some_object(int f1, char f2) :field_1(f1), field_2(f2) {}
};
template<typename T>
struct Wezel
{
    Wezel<T>* poprzedni = NULL;
    T dana;
    Wezel<T>* nastepny = NULL;
    Wezel(T podana) { dana = podana; }
};

//funkcja porownujaca z kluczem field_1 dla dynamicznego parametru szablonu
template<typename T>
int some_object_cmp_field1(T* so1, T* so2)
{
    int diff = so1->field_1 - so2->field_1;
    if (diff != 0)
        return diff;
    return so1->field_2 - so2->field_2;
}
//dla statycznego parametru szablonu
template<typename T>
int some_object_cmp_field1(T so1, T so2)
{
    int diff = so1.field_1 - so2.field_1;
    if (diff != 0)
        return diff;
    return so1.field_2 - so2.field_2;
}


//funkcja porownujaca z kluczem field_2 dla dynamicznego parametru szablonu
template<typename T>
int some_object_cmp_field2(T* so1, T* so2)
{
    int diff = so1->field_2 - so2->field_2;
    if (diff != 0)
        return diff;
    return so1->field_1 - so2->field_1;
}
//dla statycznego parametru szablonu
template<typename T>
int some_object_cmp_field2(T so1, T so2)
{
    int diff = so1.field_2 - so2.field_2;
    if (diff != 0)
        return diff;
    return so1.field_1 - so2.field_1;
}
template<typename T>
struct Linked_list
{
    int rozmiar = 0;

    Wezel<T>* czolo = NULL;
    Wezel<T>* ogon = NULL;
    Linked_list() {}
    ~Linked_list() { delete czolo; delete ogon; }
    //lista zwalnia swoje wezly poprzez swoje metody lub destruktor

    void add_front(T dodawany) //dodaj element
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
        if (0 <= indeks < rozmiar)
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
    void wypisz_dynam()
    {
        Wezel<T>* temp = czolo;
        for (int i = 0; i < rozmiar; i++)
        {
            cout << temp->dana->field_1 << endl;
            cout << temp->dana->field_2 << endl;
            temp = temp->nastepny;
            cout << endl;
        }
    }
    void wypisz_stat()
    {
        Wezel<T>* temp = czolo;
        for (int i = 0; i < rozmiar; i++)
        {
            cout << temp->dana.field_1 << endl;
            cout << temp->dana.field_2 << endl;
            temp = temp->nastepny;
            cout << endl;
        }
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

int losuj_numer()
{

    // zakres 10 000
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
    // DEMONSTACJA DZIALANIA LISTY ZAKOMENTOWANA
    /*
    Linked_list<Some_object*>* lista = new Linked_list<Some_object*>();   //utoworzenie listy

    //dane przechowywane na "zewnatrz" w main

    //utworzenie obiektow
    Some_object* obiekt1 = new Some_object(1,'a');
    Some_object* obiekt2 = new Some_object(2,'b');
    Some_object* obiekt3 = new Some_object(3,'c');
    Some_object* obiekt4 = new Some_object(4,'d');

    //dodanie
    lista->add_end(obiekt3);
    lista->add_end(obiekt2);
    lista->add_end(obiekt1);
    lista->add_end(obiekt1);
    cout << "==========WYPISANIE DODANYCH OBIEKTOW============" << endl;
    lista->wypisz_dynam();


    cout << "==========DEMONSTRACJA METOD============" << endl;
    lista->znajdz_i_usun(obiekt3, some_object_cmp_field1);
    lista->znajdz_i_usun(obiekt3, some_object_cmp_field1);
    lista->znajdz_i_usun(obiekt1, some_object_cmp_field1);

    //indeks spoza zasiegu
    lista->set_dane(11, obiekt2);

    lista->set_dane(1, obiekt2);
    lista->wypisz_dynam();


    cout << "========ADD   WYMUSZ    PORZADKU ======="<< endl;
    lista->add_wymusz_porzadku(obiekt2, some_object_cmp_field1);
    lista->wypisz_dynam();

    lista->czyszczenie();

    //wywolanie danych spoza indeksu/nie istniejacych zwraca wskaznik NULL - niepowodzenie
    lista->get_dane(1);
    delete lista;

    //usuniecie obiektow
    delete obiekt1;
    delete obiekt2;
    delete obiekt3;
    delete obiekt4;
    */
    cout << "=============GLOWNY EKSPERYMENT================" << endl;

    // fragmenty kodu pod //TEST po odkomentowaniu umozliwiaja wglad 
    // w rozmiar, oraz wypisanie listy na roznych etapach wykonania glownego eksperymentu


    srand(time(NULL));
    const int MAX_ORDER = 6;
    Linked_list <Some_object*>* ll = new Linked_list <Some_object* >(); // stworzenie listy
    for (int o = 1; o <= MAX_ORDER; o++) // petla po kolejnych rzedach wielkosci
    {
        cout << endl;

        //TEST
        // cout << "=======NOWA ITERACJA PETLI ========== ROZMIAR: "<<ll->rozmiar << endl; 
        const int n = pow(10, o); // rozmiar danych
        // dodawanie do listy

        double czas_calkowity = 0;
        for (int i = 0; i < n; i++) {
            //n razy dodaje 
            Some_object* so = new Some_object(losuj_numer(), losuj_znak()); // losowe dane
            clock_t t1 = clock();
            ll->add_wymusz_porzadku(so, some_object_cmp_field1);
            clock_t t2 = clock();
            double t = (t2 - t1) / (double)CLOCKS_PER_SEC;
            czas_calkowity += t;
        }


        cout << endl;
        cout << "add_wymusz_porzadku " << n << " razy" << " trwa: " << czas_calkowity << " sekundy "
            << (czas_calkowity / n) * 1000000 << " mikrosekundy" << endl;

        //TEST
        /*
        cout << "ROZMIAR: " << ll->rozmiar << endl;
        ll->wypisz_dynam();
        */
        // wyszukiwanie i usuwanie z listy
        const int m = pow(10, 4); // liczba prob wyszukania
        czas_calkowity = 0;
        for (int i = 0; i < m; i++) {

            // tworzenie losowych rekordow i usuwanie takich samych z listy jesli znajduja sie w niej 
            Some_object* so = new Some_object(losuj_numer(), losuj_znak()); // losowe dane jako wzorzec do wyszukiwania ( obiekt chwilowy )
            clock_t t1 = clock();
            bool dokonano_usuniecia = ll->znajdz_i_usun(so, some_object_cmp_field1);
            clock_t t2 = clock();
            double t = (t2 - t1) / (double)CLOCKS_PER_SEC;
            czas_calkowity += t;

            //TEST
            //if (dokonano_usuniecia) cout << "USUNIETO" << endl;

            delete so;

        }


        cout << endl;
        cout << "znajdz_i_usun " << m << " razy" << " trwa: " << czas_calkowity << " sekundy "
            << (czas_calkowity / m) * 1000000 << " mikrosekundy/operacje" << endl;


        //TEST
        /*
        cout<<"ROZMIAR: " << ll->rozmiar << endl;
        cout << "========AKTUALNA POSTAC LITY========= ROZMIAR: " << ll->rozmiar<<endl;
        ll->wypisz_dynam();
        */

        ll->czyszczenie(); // czyszczenie listy wraz z uwalnianiem pamieci danych     
    }

    delete ll;

    return 0;
}



