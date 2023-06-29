#include <iostream>
#include <list>
#include <iterator>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <string.h>
using namespace std;

struct Some_object
{
    int klucz;
    Some_object(int k) :klucz(k) {}
};
//dynamiczny komparator
template<typename T>
int some_object_cmp(T* so1, T* so2)
{
    int diff = so1->klucz - so2->klucz;
    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else if (diff == 0)
        return 0;
}
//statyczny komparator
template<typename T>
int some_object_cmp(T so1, T so2)
{
    int diff = so1.klucz - so2.klucz;
    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else if (diff == 0)
        return 0;
}


template <typename T>
struct Wezel
{
    T dane;
    Wezel<T>* rodzic = NULL;
    Wezel<T>* lewy = NULL;
    Wezel<T>* prawy = NULL;
    int kolor;
    int identyfikator = 0;  //pierwszy to 1

    Wezel<T>(T d) : dane(d) {}
    void rbt_f_wew_dowypisz_dynamic()
    {
        cout << "ID: " << identyfikator << "[ ";
        if (kolor == 1)cout << "czerwony";
        else if (kolor == 0)cout << "czarny";
        cout << ", p: ";
        if (rodzic == NULL)cout << "NULL";
        else cout << rodzic->dane->klucz;
        cout << ", l: ";
        if (lewy == NULL)cout << "NULL";
        else cout << lewy->dane->klucz;
        cout << ", p: ";
        if (prawy == NULL)cout << "NULL";
        else cout << prawy->dane->klucz;
        cout << " ]" << "dane: " << dane->klucz << endl;
    }
    void rbt_f_wew_dowypisz_static()
    {
        cout << "ID: " << identyfikator << "[ ";
        if (kolor == 1)cout << "czerwony";
        else if (kolor == 0)cout << "czarny";
        cout << ", p: ";
        if (rodzic == NULL)cout << "NULL";
        else cout << rodzic->dane.klucz;
        cout << ", l: ";
        if (lewy == NULL)cout << "NULL";
        else cout << lewy->dane.klucz;
        cout << ", p: ";
        if (prawy == NULL)cout << "NULL";
        else cout << prawy->dane.klucz;
        cout << " ]" << "dane: " << dane.klucz << endl;
    }
};

template <typename T>
struct Red_black_tree
{
    int rozmiar = 0;
    Wezel<T>* root = NULL;

    int insert(T podane_dane, int (*foo)(T, T))
    {
        Wezel<T>* poprzedni = NULL;
        Wezel<T>* p = root;

        while (p != NULL)
        {

            if (foo(p->dane, podane_dane) == 0)return 0;
            poprzedni = p;

            if (foo(p->dane, podane_dane) == -1)
            {
                p = p->prawy;
            }
            else
            {
                p = p->lewy;
            }
        }

        Wezel<T>* nowy_wezel = new Wezel<T>(podane_dane);


        ++rozmiar;
        nowy_wezel->identyfikator = rozmiar;

        if (poprzedni == NULL)
        {

            root = nowy_wezel;
            root->rodzic = NULL;
            return 1;
        }
        if (foo(poprzedni->dane, podane_dane) == -1)
        {
            poprzedni->prawy = nowy_wezel;
            nowy_wezel->rodzic = poprzedni;
        }
        else
        {
            poprzedni->lewy = nowy_wezel;
            nowy_wezel->rodzic = poprzedni;
        }
        return 1;
    }
    void przejdz_inorder(Wezel<T>* wezel, list<Wezel<T>*>* lista)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            przejdz_inorder(wezel->lewy, lista);
            lista->push_back(wezel);
            przejdz_inorder(wezel->prawy, lista);
        }
        return;
    }
    void rotate_right(Wezel<T>* dziecko) 
    { 
        auto ojciec = dziecko->rodzic;
        auto dziadek = ojciec->rodzic;
        if (dziadek != NULL)
        {
            if (dziadek->prawy == ojciec)
            {
                dziadek->prawy = dziecko;
            }
            else
            {
                dziadek->lewy = dziecko;
            }
        }
        else
            root = dziecko;
        auto temp = dziecko->prawy;
        dziecko->prawy = ojciec;
        ojciec->lewy = temp;
        if (temp != NULL) temp->rodzic = ojciec;
        dziecko->rodzic = dziadek;
        ojciec->rodzic = dziecko;
    }
    void rotate_left(Wezel<T>* dziecko)   
    {
        auto ojciec = dziecko->rodzic;
        auto dziadek = ojciec->rodzic;
        if (dziadek != NULL)
        {
            if (dziadek->prawy == ojciec)
            {
                dziadek->prawy = dziecko;
            }
            else
            {
                dziadek->lewy = dziecko;
            }
        }
        else
            root = dziecko;
        auto temp = dziecko->lewy;
        dziecko->lewy = ojciec;
        ojciec->prawy = temp;
        if (temp != NULL)temp->rodzic = ojciec;
        dziecko->rodzic = dziadek;
        ojciec->rodzic = dziecko;       
    }
    Wezel<T>* find(T obiekt, int (*foo)(T, T))
    {
        auto p = root;
        
        
        while (p != NULL)
        {
            if (foo(p->dane, obiekt) == 0)
            {
                  return p;
            }
   
            if (foo(obiekt, p->dane) == -1)p = p->lewy;
            else
            {
                p = p->prawy;
            }
        }
        
        return NULL;
    }
    int rbt_insert(T podane_dane, int (*foo)(T, T))
    {
        auto wstawiaono = insert(podane_dane, foo);  
        if (wstawiaono == 0)return 0;
        Wezel<T>* x = find(podane_dane, foo);
        
        x->kolor = 1;
        while ((x != root) && (x->rodzic->kolor == 1))
        {
            if (x->rodzic == x->rodzic->rodzic->lewy)
            {
                Wezel<T>* y = x->rodzic->rodzic->prawy;   
                if ((y == NULL) || (y->kolor == 0))   
                {
                    if (x == x->rodzic->prawy)
                    {
                        rotate_left(x);
                        x = x->lewy; 
                    }
                    x->rodzic->kolor = 0;
                    x->rodzic->rodzic->kolor = 1;
                    rotate_right(x->rodzic);
                }
                else if (y->kolor == 1)
                {
                    x->rodzic->kolor = 0;
                    y->kolor = 0;
                    x->rodzic->rodzic->kolor = 1;
                    x = x->rodzic->rodzic;
                }
            }
            else
            {
                Wezel<T>* y = x->rodzic->rodzic->lewy;
                if ((y == NULL) || (y->kolor == 0)) 
                {
                    if (x == x->rodzic->lewy)
                    {
                        rotate_right(x);
                        x = x->prawy;                       
                    }                  
                    x->rodzic->kolor = 0;
                    x->rodzic->rodzic->kolor = 1;
                    rotate_left(x->rodzic);
                }
                else 
                {
                    x->rodzic->kolor = 0;
                    y->kolor = 0;
                    x->rodzic->rodzic->kolor = 1;
                    x = x->rodzic->rodzic;
                }
            }
        }
        root->kolor = 0;
        return 1;
    }
    void przejdz_preorder(Wezel<T>* wezel)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            przejdz_preorder(wezel->lewy);
            przejdz_preorder(wezel->prawy);
        }
    }
    int czyszczenie(Wezel<T>* wezel)    
    {
        if (root == NULL)return 0;
        if (root != NULL)
        {
            przejdz_preorder(wezel->lewy);
            przejdz_preorder(wezel->prawy);
            delete wezel;
        }
        root = NULL;
        rozmiar = 0;
        return 1;
    }
    int wzrost(Wezel <T>* wezel)
    {
        if (wezel == NULL)
            return 0;
        int ll = wzrost(wezel->lewy);
        int pp = wzrost(wezel->prawy);
        if (ll > pp)
            return ll + 1;
        else
            return pp + 1;
    }
    void rbt_wypisz_preorder_dynamic(Wezel<T>* wezel)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            wezel->rbt_f_wew_dowypisz_dynamic();
            rbt_wypisz_preorder_dynamic(wezel->lewy);
            rbt_wypisz_preorder_dynamic(wezel->prawy);
        }
    }
    void rbt_wypisz_preorder_static(Wezel<T>* wezel)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            wezel->rbt_f_wew_dowypisz_static();
            rbt_wypisz_preorder_static(wezel->lewy);
            rbt_wypisz_preorder_static(wezel->prawy);
        }
    }
    void wypisz_dynamic()
    {
        cout << "size: " << rozmiar << endl;
        cout << "height: " << wzrost(root) << endl;
        cout << "{" << endl;
        rbt_wypisz_preorder_dynamic(root);
        cout << "}" << endl;
    }
    void wypisz_static()
    {
        cout << "size: " << rozmiar << endl;
        cout << "height: " << wzrost(root) << endl;
        cout << "{" << endl;
        rbt_wypisz_preorder_static(root);
        cout << "}" << endl;
    }
    void wypisz_skrot()
    {
        cout << "size: " << rozmiar << endl;
        cout << "height: " << wzrost(root) << endl;
    }
};

int losuj_numer()
{
    int wylosnum = rand() % 1000 + 1;
    return wylosnum;
}

int main()
{
    // W KOMENTARZU MOZLIWOSC TESTOWANIA KONKRETNYCH DODAWANYCH DANYCH
    /*
    srand(time(NULL));

    Red_black_tree<Some_object*>* drzewo = new Red_black_tree<Some_object*>();
    Some_object* o1 = new Some_object(losuj_numer());
    Some_object* o2 = new Some_object(losuj_numer());
    Some_object* o3 = new Some_object(losuj_numer());
    Some_object* o4 = new Some_object(losuj_numer());
    Some_object* o5 = new Some_object(losuj_numer());
    Some_object* o6 = new Some_object(losuj_numer());
    Some_object* o7 = new Some_object(losuj_numer());
    Some_object* o8 = new Some_object(losuj_numer());
    Some_object* o9 = new Some_object(losuj_numer());
    Some_object* o10 = new Some_object(losuj_numer());

    
    cout << o1->klucz << endl;
    cout << o2->klucz << endl;
    cout << o3->klucz << endl;
    cout << o4->klucz << endl;
    cout << o5->klucz << endl;
    cout << o6->klucz << endl;
    cout << o7->klucz << endl;
    cout << o8->klucz << endl;
    cout << o9->klucz << endl;
    cout << o10->klucz << endl;
    cout << "KONIEC" << endl;
   
    drzewo->rbt_insert(o1, some_object_cmp);
    drzewo->rbt_insert(o2, some_object_cmp);
    drzewo->rbt_insert(o3, some_object_cmp);
    drzewo->rbt_insert(o4, some_object_cmp);
    drzewo->rbt_insert(o5, some_object_cmp);
    drzewo->rbt_insert(o6, some_object_cmp);
    drzewo->rbt_insert(o7, some_object_cmp);
    drzewo->rbt_insert(o8, some_object_cmp);
    drzewo->rbt_insert(o9, some_object_cmp);
    drzewo->rbt_insert(o10, some_object_cmp);
     
    

   
    drzewo->wypisz_dynamic();



    drzewo->czyszczenie(drzewo->root);
    cout << "wyczyszczno"<<endl;
    drzewo->rbt_wypisz_preorder_dynamic(drzewo->root);
    delete drzewo;
    */



    
    srand(time(NULL));

    const int MAX_ORDER = 7;
    Red_black_tree<Some_object*>* rbt = new Red_black_tree<Some_object*>();

    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            Some_object* so = new Some_object(losuj_numer());
            rbt->rbt_insert(so, some_object_cmp); //  
        }
        clock_t t2 = clock();

        double wysokosc = (rbt->wzrost(rbt->root));
        cout << "stosunek wysokosc/rozmiar = " << wysokosc / n << endl;

        cout << "log2 z rozmiaru dodawanych danych: " << log2(n) << endl;
        cout << "wysokosc/log2 z rozmiaru dodawanych danych " << wysokosc / log2(n) << endl;

        double time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;

        rbt->wypisz_skrot();
        cout << "czas calkowity dodawania: " << time_calkowity << " sekund" << endl;
        cout << "czas sredni dodawnaia: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;

        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();
        for (int i = 0; i < m; i++)
        {
            Some_object* so = new Some_object(losuj_numer());
            auto result = rbt->find(so, some_object_cmp);
            if (result != NULL)
                hits++;
            delete so;
        }
        t2 = clock();

        time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
        rbt->wypisz_skrot();
        cout << "czas calkowity szukania: " << time_calkowity << " sekund" << endl;
        cout << "czas sredni szukania: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;

        cout << "TRAFIENIA: " << hits << endl;

        rbt->czyszczenie(rbt->root);
        cout << endl;
    }
    delete rbt;

    
    
    return 0;
}




