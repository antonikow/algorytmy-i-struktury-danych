#include <iostream>
#include <list>
#include <iterator>
#include <time.h>
#include <cstdlib>
#include <math.h>
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
    int identyfikator = 0;  //pierwszy to 1

    Wezel<T>(T d) : dane(d){}

    void wypisz_dynamic()
    {
        cout << "ID: " << identyfikator << " klucz: " << dane->klucz << endl;
    }
    void wypisz_static()
    {
        cout << "ID: " << identyfikator << " klucz: " << dane.klucz << endl;
    }

    friend struct Binar_search_tree;
    void f_wew_dowypisz_dynamic()
    {
        cout << "ID: " << identyfikator << "[ " << "p: ";
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
    void f_wew_dowypisz_static()
    {
        cout << "ID: " << identyfikator << "[ " << "p: ";
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
struct Binary_search_tree
{
    int rozmiar = 0;
    Wezel<T>* root = NULL;//ostatnia zmiana ze NULL
    Binary_search_tree() { root = NULL; }
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
    void wypisanie_drzewa_dynamic(Wezel<T>* wezel)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            wezel->wypisz_dynamic();
            wypisanie_drzewa_dynamic(wezel->lewy);
            wypisanie_drzewa_dynamic(wezel->prawy);
        }
        return;
    }
    void wypisanie_drzewa_static(Wezel<T>* wezel)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            wezel->wypisz_static();
            wypisanie_drzewa_static(wezel->lewy);
            wypisanie_drzewa_static(wezel->prawy);
        }
        return;
    }
    void scan_preorder_dynamic(Wezel<T>* wezel, list<Wezel<T>*>* lista)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            lista->push_back(wezel);
            scan_preorder_dynamic(wezel->lewy, lista);
            scan_preorder_dynamic(wezel->prawy, lista);
        }
        return;
    }
    void scan_preorder_static(Wezel<T>* wezel, list<Wezel<T>*>* lista)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            lista->push_back(wezel);
            scan_preorder_static(wezel->lewy, lista);
            scan_preorder_static(wezel->prawy, lista);
        }
        return;

    }
    void wypisz_preorder_dynamic(Wezel<T>* wezel)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            wezel->f_wew_dowypisz_dynamic();
            wypisz_preorder_dynamic(wezel->lewy);
            wypisz_preorder_dynamic(wezel->prawy);
        }

    }
    void wypisz_preorder_static(Wezel<T>* wezel)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            wezel->f_wew_dowypisz_static();
            wypisz_preorder_static(wezel->lewy);
            wypisz_preorder_static(wezel->prawy);
        }


    }
    void przejdz_preorder_dynamic(Wezel<T>* wezel)
    {
        if (wezel != NULL && rozmiar != 0)
        {

            przejdz_preorder_dynamic(wezel->lewy);
            przejdz_preorder_dynamic(wezel->prawy);
        }

    }
    void przejdz_preorder_static(Wezel<T>* wezel)
    {
        if (wezel != NULL && rozmiar != 0)
        {

            przejdz_preorder_static(wezel->lewy);
            przejdz_preorder_static(wezel->prawy);
        }

    }
    void scan_inorder_dynamic(Wezel<T>* wezel, list<Wezel<T>*>* lista)
    {
        if (wezel != NULL && rozmiar != 0)
        {
            scan_inorder_dynamic(wezel->lewy, lista);
            lista->push_back(wezel);
            scan_inorder_dynamic(wezel->prawy, lista);
        }
        return;
    }
    void scan_inorder_static(Wezel<T>* wezel, list<Wezel<T>*>* lista)//ostatnio zaktualizowane static
    {
        if (wezel != NULL && rozmiar != 0)
        {
            scan_inorder_static(wezel->lewy, lista);
            lista->push_back(wezel);
            scan_inorder_static(wezel->prawy, lista);
        }
        return;

    }
    Wezel<T>* find_dynamic(T obiekt, int (*foo)(T, T))
    {
        auto p = root;


        Wezel<T>* temp = new Wezel<T>(obiekt);
        Wezel<T>* poprzedni = NULL;



        while (p != NULL)
        {
            if (foo(p->dane, temp->dane) == 0)
            {
                return p; delete temp;
            }
            poprzedni = p;
            if (foo(temp->dane, p->dane) == -1)p = p->lewy;
            else
            {
                p = p->prawy;
            }
        }
        delete temp;

        return NULL;
    }
    Wezel<T>* find_static(T obiekt, int (*foo)(T, T))
    {

        Wezel<T>* temp = new Wezel<T>(obiekt);
        Wezel<T>* poprzedni = NULL;
        auto p = root;
        while (p != NULL)
        {
            if (foo(p->dane, temp->dane) == 0)
            {
                return p; delete temp;
            }
            poprzedni = p;
            if (foo(temp->dane, p->dane) == -1)p = p->lewy;
            else
            {
                p = p->prawy;
            }
        }
        delete temp;

        return NULL;
    }
    int usun_dynamic(T obiekt, int (*foo)(T, T))
    {

        auto znaleziony = find_dynamic(obiekt, foo);

        if (znaleziony == NULL)return 0;

        if (stopien(znaleziony) == 0)
        {
            //cout << "stopien: " << stopien(znaleziony) << " klucz: " << znaleziony->dane->klucz << endl;
            if (znaleziony == root)
            {
                //dziwna korekta nwm czemu NULL naprawia
                root = NULL;
                --rozmiar;
                return 1;

            }

            else
            {
                if (znaleziony->dane->klucz < znaleziony->rodzic->dane->klucz)//jest po lewej
                {
                    znaleziony->rodzic->lewy = NULL;
                    delete znaleziony;

                    --rozmiar;
                    return 1;
                }

                if (znaleziony->dane->klucz > znaleziony->rodzic->dane->klucz)//jest po prawej
                {
                    znaleziony->rodzic->prawy = NULL;
                    delete znaleziony;
                    --rozmiar;
                    return 1;
                }
            }
        }
        if (stopien(znaleziony) == 1)
        {
            // cout <<"stopien: "<<stopien(znaleziony)<<" klucz: "<<  znaleziony->dane->klucz << endl;
            if (znaleziony == root)
            {
                if (znaleziony->lewy == NULL)
                {
                    root = znaleziony->prawy;
                    root->rodzic = NULL;
                    delete znaleziony;
                    --rozmiar;
                    return 1;
                }
                if (znaleziony->prawy == NULL)
                {
                    root = znaleziony->lewy;
                    root->rodzic = NULL;
                    delete znaleziony;
                    --rozmiar;
                    return 1;
                }
            }
            else
            {
                if (znaleziony->prawy == NULL)
                {
                    znaleziony->lewy->rodzic = znaleziony->rodzic;
                    if (znaleziony->lewy->dane->klucz < znaleziony->rodzic->dane->klucz)
                    {
                        znaleziony->rodzic->lewy = znaleziony->lewy;
                        delete znaleziony;
                        --rozmiar;
                        return 1;
                    }
                    if (znaleziony->lewy->dane->klucz > znaleziony->rodzic->dane->klucz)
                    {
                        znaleziony->rodzic->prawy = znaleziony->lewy;
                        delete znaleziony;
                        --rozmiar;
                        return 1;
                    }


                }
                if (znaleziony->lewy == NULL)
                {
                    znaleziony->prawy->rodzic = znaleziony->rodzic;
                    if (znaleziony->prawy->dane->klucz < znaleziony->rodzic->dane->klucz)
                    {
                        znaleziony->rodzic->lewy = znaleziony->prawy;
                        delete znaleziony;
                        --rozmiar;
                        return 1;
                    }
                    if (znaleziony->prawy->dane->klucz > znaleziony->rodzic->dane->klucz)
                    {
                        znaleziony->rodzic->prawy = znaleziony->prawy;
                        delete znaleziony;
                        --rozmiar;
                        return 1;
                    }

                }
            }
        }

        if (stopien(znaleziony) == 2)
        {
            //cout << "stopien: " << stopien(znaleziony) << " klucz: " << znaleziony->dane->klucz << endl;
            list<Wezel<T>*> wewlist;
            scan_inorder_dynamic(root, &wewlist);
            auto nastepnik = zwroc_nastepny_dynamic(obiekt, &wewlist);

            if (stopien(nastepnik) == 0)
            {
                znaleziony->dane->klucz = nastepnik->dane->klucz;
                znaleziony->identyfikator = nastepnik->identyfikator;
                if (nastepnik->rodzic->lewy == nastepnik)
                {
                    nastepnik->rodzic->lewy = NULL;
                }
                if (nastepnik->rodzic->prawy == nastepnik)
                {

                    nastepnik->rodzic->prawy = NULL;
                }
                delete nastepnik;
                --rozmiar;
                return 1;
            }
            if (stopien(nastepnik) == 1)
            {
                if (root->dane->klucz < nastepnik->dane->klucz)
                {



                    if (nastepnik->dane->klucz < nastepnik->rodzic->dane->klucz)
                    {
                        nastepnik->rodzic->lewy = nastepnik->lewy;
                        nastepnik->prawy->rodzic = nastepnik->rodzic;



                        znaleziony->dane->klucz = nastepnik->dane->klucz;
                        znaleziony->identyfikator = nastepnik->identyfikator;
                        delete nastepnik;
                        --rozmiar;
                        return 1;
                    }

                    if (nastepnik->dane->klucz > nastepnik->rodzic->dane->klucz)
                    {
                        znaleziony->prawy = nastepnik->prawy;
                        znaleziony->prawy->rodzic = znaleziony;



                        znaleziony->dane->klucz = nastepnik->dane->klucz;
                        znaleziony->identyfikator = nastepnik->identyfikator;
                        delete nastepnik;
                        --rozmiar;
                        return 1;
                    }
                }
                if (root->dane->klucz > nastepnik->dane->klucz)
                {
                    if (nastepnik->dane->klucz < nastepnik->rodzic->dane->klucz)
                    {
                        nastepnik->rodzic->lewy = nastepnik->prawy;
                        nastepnik->prawy->rodzic = nastepnik->rodzic;

                        znaleziony->dane->klucz = nastepnik->dane->klucz;
                        znaleziony->identyfikator = nastepnik->identyfikator;
                        delete nastepnik;
                        --rozmiar;
                        return 1;
                    }
                    if (nastepnik->dane->klucz > nastepnik->rodzic->dane->klucz)
                    {

                        znaleziony->prawy = nastepnik->prawy;
                        znaleziony->prawy->rodzic = znaleziony;

                        znaleziony->dane->klucz = nastepnik->dane->klucz;
                        znaleziony->identyfikator = nastepnik->identyfikator;
                        delete nastepnik;
                        --rozmiar;
                        return 1;
                    }
                }
            }
        }

    }
    int usun_static(T obiekt, int (*foo)(T, T))
    {

        auto znaleziony = find_static(obiekt, foo);

        if (znaleziony == NULL)return 0;

        if (stopien(znaleziony) == 0)
        {
            //cout << "stopien: " << stopien(znaleziony) << " klucz: " << znaleziony->dane->klucz << endl;
            if (znaleziony == root)
            {
                //delete znaleziony powoduje bledy NULL nie
                root = NULL;
                --rozmiar;
                return 1;

            }

            else
            {
 
                if (znaleziony->dane.klucz < znaleziony->rodzic->dane.klucz)//jest po lewej
                {
                    znaleziony->rodzic->lewy = NULL;
                    delete znaleziony;

                    --rozmiar;
                    return 1;
                }

                if (znaleziony->dane.klucz > znaleziony->rodzic->dane.klucz)//jest po prawej
                {
                    znaleziony->rodzic->prawy = NULL;
                    delete znaleziony;
                    --rozmiar;
                    return 1;
                }


            }



        }
        if (stopien(znaleziony) == 1)
        {
            // cout <<"stopien: "<<stopien(znaleziony)<<" klucz: "<<  znaleziony->dane->klucz << endl;
            if (znaleziony == root)
            {
                //cout << "root!!" << endl;
                if (znaleziony->lewy == NULL)
                {
                    //cout << "lewy" << endl;
                    root = znaleziony->prawy;
                    root->rodzic = NULL;
                    delete znaleziony;
                    --rozmiar;
                    return 1;
                }
                if (znaleziony->prawy == NULL)
                {
                    //cout << "prawy" << endl;
                    root = znaleziony->lewy;
                    root->rodzic = NULL;
                    delete znaleziony;
                    --rozmiar;
                    return 1;
                }
            }
            else
            {
                //cout << "nie root" << endl;
                if (znaleziony->prawy == NULL)
                {
                    //cout << "lewy" << endl;
                    znaleziony->lewy->rodzic = znaleziony->rodzic;
                    if (znaleziony->lewy->dane.klucz < znaleziony->rodzic->dane.klucz)
                    {
                        znaleziony->rodzic->lewy = znaleziony->lewy;
                        delete znaleziony;
                        --rozmiar;
                        return 1;


                    }
                    if (znaleziony->lewy->dane.klucz > znaleziony->rodzic->dane.klucz)
                    {
                        znaleziony->rodzic->prawy = znaleziony->lewy;
                        delete znaleziony;
                        --rozmiar;
                        return 1;
                    }


                }
                if (znaleziony->lewy == NULL)
                {
                    //cout << "prway" << endl;
                    znaleziony->prawy->rodzic = znaleziony->rodzic;
                    if (znaleziony->prawy->dane.klucz < znaleziony->rodzic->dane.klucz)
                    {
                        znaleziony->rodzic->lewy = znaleziony->prawy;
                        delete znaleziony;
                        --rozmiar;
                        return 1;
                    }
                    if (znaleziony->prawy->dane.klucz > znaleziony->rodzic->dane.klucz)
                    {
                        znaleziony->rodzic->prawy = znaleziony->prawy;
                        delete znaleziony;
                        --rozmiar;
                        return 1;
                    }

                }
            }
        }

        if (stopien(znaleziony) == 2)
        {
            //cout << "stopien: " << stopien(znaleziony) << " klucz: " << znaleziony->dane->klucz << endl;

            list<Wezel<T>*> wewlist;
            scan_inorder_staticc(root, &wewlist);
            auto nastepnik = zwroc_nastepny_static(obiekt, &wewlist);

            if (stopien(nastepnik) == 0)
            {
                znaleziony->dane.klucz = nastepnik->dane.klucz;
                znaleziony->identyfikator = nastepnik->identyfikator;
                if (nastepnik->rodzic->lewy == nastepnik)
                {
                    nastepnik->rodzic->lewy = NULL;
                }
                if (nastepnik->rodzic->prawy == nastepnik)
                {

                    nastepnik->rodzic->prawy = NULL;
                }
                delete nastepnik;
                --rozmiar;
                return 1;
            }
            if (stopien(nastepnik) == 1)
            {
                if (root->dane.klucz < nastepnik->dane.klucz)
                {

                    if (nastepnik->dane.klucz < nastepnik->rodzic->dane.klucz)
                    {
                        nastepnik->rodzic->lewy = nastepnik->lewy;
                        nastepnik->prawy->rodzic = nastepnik->rodzic;



                        znaleziony->dane.klucz = nastepnik->dane.klucz;
                        znaleziony->identyfikator = nastepnik->identyfikator;
                        delete nastepnik;
                        --rozmiar;
                        return 1;
                    }

                    if (nastepnik->dane.klucz > nastepnik->rodzic->dane.klucz)
                    {
                        znaleziony->prawy = nastepnik->prawy;
                        znaleziony->prawy->rodzic = znaleziony;



                        znaleziony->dane.klucz = nastepnik->dane.klucz;
                        znaleziony->identyfikator = nastepnik->identyfikator;
                        delete nastepnik;
                        --rozmiar;
                        return 1;
                    }
                }
                if (root->dane.klucz > nastepnik->dane.klucz)
                {
                    if (nastepnik->dane.klucz < nastepnik->rodzic->dane.klucz)
                    {
                        nastepnik->rodzic->lewy = nastepnik->prawy;
                        nastepnik->prawy->rodzic = nastepnik->rodzic;

                        znaleziony->dane.klucz = nastepnik->dane.klucz;
                        znaleziony->identyfikator = nastepnik->identyfikator;
                        delete nastepnik;
                        --rozmiar;
                        return 1;
                    }
                    if (nastepnik->dane.klucz > nastepnik->rodzic->dane.klucz)
                    {

                        znaleziony->prawy = nastepnik->prawy;
                        znaleziony->prawy->rodzic = znaleziony;

                        znaleziony->dane.klucz = nastepnik->dane.klucz;
                        znaleziony->identyfikator = nastepnik->identyfikator;
                        delete nastepnik;
                        --rozmiar;
                        return 1;
                    }
                }
            }
        }

    }
    Wezel<T>* zwroc_poprzedni_dynamic(T obiekt, list<Wezel<T>*>* lista)
    {
        for (auto it = lista->begin(); it != lista->end(); ++it)
        {
            // cout<<(*it)->dane->klucz<<endl;

        }
        for (auto it = lista->begin(); it != lista->end(); ++it)
        {

            if ((*it)->dane->klucz == obiekt->klucz)
            {

                return *(--it);
            }
        }
        return NULL;
    }
    Wezel<T>* zwroc_poprzedni_static(T obiekt, list<Wezel<T>*>* lista)
    {
        for (auto it = lista->begin(); it != lista->end(); ++it)
        {
            //cout << (*it)->dane.klucz << endl;

        }
        for (auto it = lista->begin(); it != lista->end(); ++it)
        {

            if ((*it)->dane.klucz == obiekt->klucz)
            {

                return *(--it);
            }
        }
        return NULL;
    }
    Wezel<T>* zwroc_nastepny_dynamic(T obiekt, list<Wezel<T>*>* lista)
    {
        for (auto it = lista->begin(); it != lista->end(); ++it)
        {
            // cout << (*it)->dane->klucz << endl;

        }
        for (auto it = lista->begin(); it != lista->end(); ++it)
        {

            if ((*it)->dane->klucz == obiekt->klucz)
            {

                return *(++it);
            }
        }
        return NULL;
    }
    Wezel<T>* zwroc_nastepny_static(T obiekt, list<Wezel<T>*>* lista)
    {
        for (auto it = lista->begin(); it != lista->end(); ++it)
        {
            //cout << (*it)->dane.klucz << endl;

        }
        for (auto it = lista->begin(); it != lista->end(); ++it)
        {

            if ((*it)->dane.klucz == obiekt->klucz)
            {

                return *(++it);
            }
        }
        return NULL;
    }
    int stopien(Wezel<T>* wezel)
    {
        int stopien = 0;
        if (wezel->lewy != NULL)stopien++;
        if (wezel->prawy != NULL)stopien++;
        return stopien;
    }
    int czyszczenie_dynamic()
    {
        if (root == NULL)return 0;

        if (root != NULL)
        {
            przejdz_preorder_dynamic(root->lewy);
            przejdz_preorder_dynamic(root->prawy);
            delete root;
            root = NULL;
        }
        rozmiar = 0;
        return 1;

    }
    int czyszczenie_static()
    {
        if (root == NULL)return 0;

        if (root != NULL)
        {
            przejdz_preorder_static(root->lewy);
            przejdz_preorder_static(root->prawy);
            delete root;
            root = NULL;
        }
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

    void wypisz_eksperyment_dynamic()
    {
        cout << "size: " << rozmiar << endl;
        cout << "height: " << wzrost(root) << endl;
        cout << "{" << endl;


        wypisz_preorder_dynamic(root);

        cout << "}" << endl;
    }
    void wypisz_eksperyment_static()
    {
        cout << "size: " << rozmiar << endl;
        cout << "height: " << wzrost(root) << endl;
        cout << "{" << endl;


        wypisz_preorder_static(root);

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
    int wylosnum = rand() % 10000 + 1;
    return wylosnum;
}

int main()
{
    srand(time(NULL));

    const int MAX_ORDER = 7;  
    Binary_search_tree<Some_object*>* bst = new Binary_search_tree<Some_object*>();

    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o);  
         
        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            Some_object* so = new Some_object(losuj_numer());
            bst->insert(so, some_object_cmp); //  
        }
        clock_t t2 = clock();

        double wysokosc = (bst->wzrost(bst->root));
        cout << "stosunek wysokosc/rozmiar = " << wysokosc / n << endl;

        cout << "log2 z rozmiaru dodawanych danych: " << log2(n) << endl;
        cout << "wysokosc/log2 z rozmiaru dodawanych danych " << wysokosc / log2(n) << endl;

        double time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;

        bst->wypisz_skrot();
        cout << "czas calkowity dodawania: " << time_calkowity << " sekund" << endl;
        cout << "czas sredni dodawnaia: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;
         
        const int m = pow(10, 4);  
        int hits = 0;  
        t1 = clock();
        for (int i = 0; i < m; i++)
        {
            Some_object* so = new Some_object(losuj_numer()); 
            auto result = bst->find_dynamic(so, some_object_cmp);
            if (result != NULL)
                hits++;
            delete so;
        }
        t2 = clock();

        time_calkowity = (t2 - t1) / (double)CLOCKS_PER_SEC;
        bst->wypisz_skrot();
        cout << "czas calkowity szukania: " << time_calkowity << " sekund" << endl;
        cout << "czas sredni szukania: " << (time_calkowity / n) * 1000000 << " mikrosekundy/operacje" << endl;

        cout << "TRAFIENIA: " << hits << endl;

        bst->czyszczenie_dynamic();
        cout << endl;
    }
    delete bst;
    return 0;
}




