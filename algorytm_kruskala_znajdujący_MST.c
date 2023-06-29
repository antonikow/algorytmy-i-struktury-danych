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
            temp->dana->wypisz();
            temp = temp->nastepny;
        }
    }
    void wypisz_lista_skrotowo()
    {
        Wezel<T>* temp = czolo;
        for (int i = 0; i < 10; i++)
        {
            temp->dana->wypisz();
            temp = temp->nastepny;
        }
        cout << "..." << endl;
    }
    float suma_wag()
    {
        Wezel<T>* temp = czolo;
        float suma = 0;
        for (int i = 0; i < rozmiar; i++)
        {
            suma = suma + temp->dana->waga;
            temp = temp->nastepny;
        }
        return suma;
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
#include <string>
#include <sstream>
#include <time.h>
#include <cstdlib>



using namespace std;

template<typename P>
int komparator(P* so1, P* so2)
{
    float diff = so1->waga - so2->waga;
    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else if (diff == 0)
        return 0;
}
template<typename P>
int komparator(P so1, P so2)
{
    float diff = so1.waga - so2.waga;
    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else if (diff == 0)
        return 0;
}
struct Node
{
    float x, y;
    Node(){}
    Node(float xx, float yy): x(xx), y(yy){}
    void wypisz()
    {
        cout << x << " " << y << endl;
    }
};
struct Edge
{
    int i, j;
    float waga;
    Edge(){}
    Edge(int ii, int jj, float wagaa) : i(ii), j(jj), waga(wagaa){}
    void wypisz()
    {
        cout << i << " " << " " << j << " " << waga << endl;
    }

};
struct Graph
{
    int l_wezlow, l_krawedzi;

    Node** wezly;
    Edge** krawedzie;

    Graph(int lw, int lk ,Node ** nodearray, Edge **edgearray)
    {
        l_wezlow = lw;
        l_krawedzi = lk;
        wezly = nodearray;
        krawedzie = edgearray;     
    }
    
};

struct Union_Find
{
    int* parent;
    int* rank;
    int l_wezlow;
    int licznik=0;
    Union_Find(int n)
    {
        l_wezlow = n;
        parent = new int[l_wezlow];
        rank = new int[l_wezlow];
        for (int i = 0; i < l_wezlow; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    ~Union_Find()
    {
        delete parent;
        delete rank;
    }
    void join(int i_root, int j_root)
    {
        parent[i_root] = j_root;
    }
    void join_by_rank(int i_root, int j_root)
    {
        if (rank[i_root] < rank[j_root])
            parent[i_root] = parent[j_root];
        else if (rank[j_root] < rank[i_root])
        {
            parent[j_root] = parent[i_root];
        }
        else
        {
            parent[i_root] = j_root;
            rank[j_root]++;
        }
    }
    int find(int i)
    {
        licznik++;
        if (i == parent[i])
            return i;
        return find(parent[i]);
    }
    int find_with_compression(int i)
    {
        licznik++;
        if (i == parent[i])
            return i;
        parent[i] = find_with_compression(parent[i]);
        return parent[i];
    }
};
 
Linked_list<Edge*>* Kruskal(Graph * g, bool path_compression, bool by_rank)
{
    Linked_list<Edge*> *mst = new Linked_list<Edge*>();
    Union_Find* uf = new Union_Find(g->l_wezlow); 
    clock_t t1 = clock();
    Binary_heap < Edge*>* bh = new Binary_heap < Edge*>(g->krawedzie, g->l_krawedzi, komparator, true);
    bh->sort(g->krawedzie, komparator, g->l_krawedzi);
    clock_t t2 = clock();
    double time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
    cout << "CZAS SORTOWANIA: " << time_calkowity * 1000000 << " ms" << endl;
    delete bh;

    clock_t t3 = clock();
    for (int it = 0; it < g->l_krawedzi; it++) 
    {
        if (path_compression)
        {
            if (uf->find_with_compression(g->krawedzie[it]->i) != uf->find_with_compression(g->krawedzie[it]->j)) 
            {
                if (by_rank)
                {
                    mst->add_end(g->krawedzie[it]);
                    uf->join_by_rank(uf->find_with_compression(g->krawedzie[it]->i), uf->find_with_compression(g->krawedzie[it]->j));
                }
                else
                {
                    mst->add_end(g->krawedzie[it]);
                    uf->join(uf->find_with_compression(g->krawedzie[it]->i), uf->find_with_compression(g->krawedzie[it]->j));
                }
            }
        }
        else
        {
            if (uf->find(g->krawedzie[it]->i) != uf->find(g->krawedzie[it]->j)) 
            {
                if (by_rank) 
                {
                    mst->add_end(g->krawedzie[it]);
                    uf->join_by_rank(uf->find(g->krawedzie[it]->i), uf->find(g->krawedzie[it]->j));
                }
                else
                {
                    mst->add_end(g->krawedzie[it]);
                    uf->join(uf->find(g->krawedzie[it]->i), uf->find(g->krawedzie[it]->j));
                }       
            }
        }    
    }
    clock_t t4 = clock();
    time_calkowity = (t4 - t3) / (double)CLOCKS_PER_SEC;
    cout << "CZAS TRWANIA GLOWNEJ PETLI: " << time_calkowity * 1000000 << " ms" << endl;
    cout << "LICZBA WYKONAN OPERACJI FIND: " << uf->licznik << endl;
    delete uf;
    return mst;
}
 
int main()
{
    ifstream plik;
    string sciezka, linia;
    float fragment;
    sciezka = "C:/Users/antoni/Desktop/alg8_pliki_tekstowe/g1.txt";
    

    int l_wezlow, l_krawedzi;
    int nr_linii=0;

    plik.open(sciezka);
    while (getline(plik, linia))
    {
        if (nr_linii == 0)
            l_wezlow = stoi(linia);
        else if (nr_linii == l_wezlow + 1)
            l_krawedzi = stoi(linia);
   
        nr_linii++;
    }
    plik.close();


    Node** wezly = new Node*[l_wezlow];
    Edge** krawedzie = new Edge*[l_krawedzi];
    //wlasciwe wczytanie
    plik.open(sciezka);
    nr_linii = 0;
    int itwezlow = 0;
    int itkrawedzi = 0;
    while (getline(plik, linia))
    {
        if(nr_linii > 0 && nr_linii <= l_wezlow)
        {
            istringstream ss(linia);
            float wspolrzedne[2];
            ss >> fragment;
            wspolrzedne[0] = fragment;
            ss >> fragment;
            wspolrzedne[1] = fragment;

            Node* wezel = new Node(wspolrzedne[0], wspolrzedne[1]);
            wezly[itwezlow] = wezel;
            itwezlow++;
        }
        else if(nr_linii != 0 && nr_linii != l_wezlow + 1)
        {
            istringstream ss(linia);
            float argkrawedzi[3];
            for (int i = 0; i < 3; i++)
            {
                ss >> fragment;
                argkrawedzi[i] = fragment;
            }
            Edge* krawedz = new Edge(argkrawedzi[0], argkrawedzi[1], argkrawedzi[2]);
            krawedzie[itkrawedzi] = krawedz;
            itkrawedzi++;
        }
        nr_linii++;  
    }
    plik.close();
    

    Graph* g = new Graph(l_wezlow, l_krawedzi, wezly, krawedzie);
    Linked_list<Edge*> *mst =  Kruskal(g,true,true);
    cout <<"SUMA WAG MST: "<< mst->suma_wag() << endl;
    cout << endl;
    cout << "LICZBA KRAWEDZI MST: " << mst->rozmiar << endl;
    cout << "SKROTOWE WYPISANIE MST " << endl;
    mst->wypisz_lista_skrotowo();


    for (int i = 0; i < l_wezlow; i++)
    {
        delete wezly[i];
    }
    delete[] wezly;
    for (int i = 0; i < l_krawedzi; i++)
    {
        delete krawedzie[i];
    }
    delete[] krawedzie;
    delete g;

    return 0;
}

