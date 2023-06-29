#include <iostream>
#include <cmath>
#include <string>
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
    ~Linked_list() { czyszczenie(); delete czolo; delete ogon; }

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
        else
            return false;
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
    void wypisz_lista()
    {
        Wezel<T>* temp = czolo;
        for (int i = 0; i < rozmiar; i++)
        {
            cout << temp->dana << endl;
            temp = temp->nastepny;
        }
    }
    T get_dane_idx(int indeks)
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
        else return NULL;
    }
    T ostatni()
    {
        return ogon->dana;
    }
    T przedostatni()
    {
        Wezel<T>* temp = ogon;
        temp = temp->poprzedni;
        return temp->dana;
    }
    T przedprzedostatni()
    {
        Wezel<T>* temp = ogon;
        temp = temp->poprzedni->poprzedni;
        return temp->dana;
    }
    bool usun_przedostatni()
    {
        if (rozmiar >= 2)
        {
            Wezel<T>* przedost = ogon->poprzedni;
            ogon->poprzedni->poprzedni->nastepny = ogon;
            ogon->poprzedni = ogon->poprzedni->poprzedni;
            delete przedost;
            rozmiar--;
            return true;
        }
        else
            return false;
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
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <time.h>


using namespace std;

struct Punkt
{
    double x, y;
    int idx;
    Punkt(){}
    Punkt(double xx, double yy, int idxx): x(xx), y(yy), idx(idxx){}
    void wypisz()
    {
        cout << x << " " << y << endl;
    }
    void wypisz_z_idx()
    {
        cout <<"["<<idx<<"]: "<< x << " " << y << endl;
    }
    Punkt operator-(Punkt p2)
    {
        Punkt temp;
        temp.x = x - p2.x;
        temp.y = y - p2.y;
        return temp;
    }
};
int komparator(Punkt *p1, Punkt *p2)
{
    double diff = p2->x * p1->y - p1->x * p2->y;
    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else if (diff == 0)
        return 0; 
}

int komparator(Punkt p1, Punkt p2)
{
    double diff = p2.x * p1.y - p1.x * p2.y;
    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else if (diff == 0)
        return 0;
}
Linked_list<Punkt*>* wczytaj(string sciezka)
{
    ifstream plik;
    string linia;

    plik.open(sciezka);
    int nr_linii = 0;
    double fragment;
    Linked_list<Punkt*>* points = new Linked_list<Punkt*>();
    while (getline(plik, linia))
    {
        if (nr_linii != 0)
        {
            istringstream ss(linia);
            double wspolrzedne[2];
            ss >> fragment;
            wspolrzedne[0] = fragment;
            ss >> fragment;
            wspolrzedne[1] = fragment;
            Punkt* pkt = new Punkt(wspolrzedne[0], wspolrzedne[1], nr_linii);
            points->add_end(pkt);
        }
        nr_linii++;
    }
    return points;
}
int znajdz_punkt_poczatkowy(Linked_list<Punkt*> *points)
{
    double min_y = points->get_dane_idx(0)->y;
    int current_root_idx = 0;
    for (int i = 1; i < points->rozmiar; i++)
    {
        if (min_y > points->get_dane_idx(i)->y)
        {
            min_y = points->get_dane_idx(i)->y;
            current_root_idx = i;
        }
        else if (min_y == points->get_dane_idx(i)->y)
        {
            if (points->get_dane_idx(current_root_idx)->x > points->get_dane_idx(i)->x)
            {
                current_root_idx = i;
            }
        }
    }
    return current_root_idx;
}
Punkt** posortuj_wg_kata(Linked_list<Punkt*>* points, int root_idx)
{
    Punkt** sortowane = new Punkt * [points->rozmiar-1];
    double root_x = points->get_dane_idx(root_idx)->x;
    double root_y = points->get_dane_idx(root_idx)->y;
    int byl_punkt_srodkowy = 0;
    
    for (int i = 0; i < points->rozmiar; i++)
    {
        if (i == root_idx)
        {
            byl_punkt_srodkowy = 1;
            continue;
        }
        else if (byl_punkt_srodkowy == 1)
        {
            sortowane[i-1] = new Punkt(points->get_dane_idx(i)->x - root_x, points->get_dane_idx(i)->y - root_y, i);
        }
        else
        {
            sortowane[i] = new Punkt(points->get_dane_idx(i)->x - root_x, points->get_dane_idx(i)->y - root_y, i);
        }
    }

    Binary_heap<Punkt*> *bh = new Binary_heap<Punkt*>(sortowane, points->rozmiar-1, komparator, true);
    bh->sort(sortowane, komparator, points->rozmiar-1);
    delete bh;

    Punkt** kopia_punktow = new Punkt * [points->rozmiar ];
    kopia_punktow[0] = new Punkt(points->get_dane_idx(root_idx)->x - root_x, points->get_dane_idx(root_idx)->y - root_y, root_idx);
    for (int i = 1; i < points->rozmiar; i++)
    {
        kopia_punktow[i] = sortowane[i - 1];
    }
    delete[] sortowane;

    return kopia_punktow;
}
Linked_list<int>* graham(Linked_list<Punkt*>* points)
{
    int root_idx = znajdz_punkt_poczatkowy(points);
    clock_t t1 = clock();
    Punkt** kopia = posortuj_wg_kata(points, root_idx);
    clock_t t2 = clock();
    double time_sortowania = (t2 - t1) / (double)CLOCKS_PER_SEC;
    cout << "CZAS SORTOWANIA: " << time_sortowania * 1000000 << " ms    " << time_sortowania * 1000 << " s" << endl;
    Linked_list<int>* powloka = new Linked_list<int>();
    if (points->rozmiar == 0)
    {
        return powloka;
    }
    else if (points->rozmiar == 1)
    {
        powloka->add_end(0);
        return powloka;
    }
    else if (points->rozmiar >= 2)
    {
        powloka->add_end(0);
        powloka->add_end(1);
        t1 = clock();
        for (int i = 2; i < points->rozmiar; i++)
        {
            powloka->add_end(i);
            while (komparator(*(kopia[powloka->ostatni()]) - *(kopia[powloka->przedostatni()]), *(kopia[powloka->przedostatni()]) - *(kopia[powloka->przedprzedostatni()])) <= 0)    // jak rowne to leza wzdluz jednej linii
            {
                powloka->usun_przedostatni();
            }
        }
        t2 = clock();
        double time_petli = (t2 - t1) / (double)CLOCKS_PER_SEC;
        cout << "CZAS GLOWNEJ PETLI: " << time_petli * 1000000 << " ms    " << time_petli*1000 << " s" << endl;
        cout << "CZAS CALKOWITY: " << (time_sortowania + time_petli) * 1000000 << " ms    " << (time_sortowania + time_petli) * 1000 << " s" << endl;
    }
    for (int i = 0; i < powloka->rozmiar; i++)
    {
        int realidx = kopia[powloka->get_dane_idx(i)]->idx;
        powloka->set_dane(i, realidx);
    }
    for (int i = 0; i < points->rozmiar; i++)
    {
        delete kopia[i];
    }
    delete[]kopia;
    return powloka;
}
int main()
{
    string sciezka;
    Linked_list<Punkt*>* punkty;
    Linked_list<int>* powloka_wyjscie;

    sciezka = "C:/Users/antoni/Desktop/alg9_pliki_tekstowe/points1.txt";
    punkty = wczytaj(sciezka);
    powloka_wyjscie = graham(punkty);
    cout << "Liczba punktow w powloce wypuklej: " << powloka_wyjscie->rozmiar << endl;
    cout << "Indeksy punktow powloki wypuklej: " << endl;
    powloka_wyjscie->wypisz_lista();
    delete powloka_wyjscie;
    
    sciezka = "C:/Users/antoni/Desktop/alg9_pliki_tekstowe/points2.txt";
    punkty = wczytaj(sciezka);
    powloka_wyjscie = graham(punkty);
    cout << "Liczba punktow w powloce wypuklej: " << powloka_wyjscie->rozmiar << endl;
    cout << "Indeksy punktow powloki wypuklej: " << endl;
    powloka_wyjscie->wypisz_lista();
    delete powloka_wyjscie;

    sciezka = "C:/Users/antoni/Desktop/alg9_pliki_tekstowe/points3.txt";
    punkty = wczytaj(sciezka);
    powloka_wyjscie = graham(punkty);
    cout << "Liczba punktow w powloce wypuklej: " << powloka_wyjscie->rozmiar << endl;
    cout << "Indeksy punktow powloki wypuklej: " << endl;
    powloka_wyjscie->wypisz_lista();
    delete powloka_wyjscie;

    sciezka = "C:/Users/antoni/Desktop/alg9_pliki_tekstowe/points4.txt";
    punkty = wczytaj(sciezka);
    powloka_wyjscie = graham(punkty);
    cout << "Liczba punktow w powloce wypuklej: " << powloka_wyjscie->rozmiar << endl;
    cout << "Indeksy punktow powloki wypuklej: " << endl;
    powloka_wyjscie->wypisz_lista();
    delete powloka_wyjscie;

    sciezka = "C:/Users/antoni/Desktop/alg9_pliki_tekstowe/points5.txt";
    punkty = wczytaj(sciezka);
    powloka_wyjscie = graham(punkty);
    cout << "Liczba punktow w powloce wypuklej: " << powloka_wyjscie->rozmiar << endl;
    cout << "Indeksy punktow powloki wypuklej: " << endl;
    powloka_wyjscie->wypisz_lista();
    delete powloka_wyjscie;
    
    return 0;
}

