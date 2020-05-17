#include <iostream>
#include"Comparator.h"
#include"Multi_Set.h"
#include<cassert>

using namespace std;

void Tests_Multi_Set()
{
    Multi_Set<int, Comparator<int>> M, N;

    M.Insert(5);
    M.Insert(7);
    M.Insert(6);
    M.Insert(5);
    M.Insert(5);
    M.Insert(8);

    assert(M.Search(6)); // verific daca exista 6 in M
    assert(M.GetNrOfAparitions(5) == 3); // verific daca 5 pare de 3 ori in M
    
    M.DeleteFirst(5);
    assert(M.GetNrOfAparitions(5) == 2); // verific daca a fost eliminat 5 o data

    assert(M.NrOfDistinctElements() == 4); // verific daca numara corect elementele distincte

    M.Insert(8);
    M.Delete(8);
    assert(M.Search(8) == -1); // verific daca l-a eliminat complet pe 8
    assert(M.GetNrOfAparitions(8) == 0);

    N = M;

    assert(N.NrOfDistinctElements() == M.NrOfDistinctElements());
    assert(N.NrOfDistinctElements() == 3); // verific daca operatorul de atribuire functioneaza corect

    Multi_Set<double, Comparator<double>> X;

    X.Insert(3.14);
    X.Insert(8.54);
    X.Insert(5.14);
    X.Insert(3.14);
    X.Insert(3.14);



    assert(X.Search(8.54)); // verific daca exista 8.54 in X
    assert(X.GetNrOfAparitions(3.14) == 3); // verific daca 3.14 pare de 2 ori in X

    X.DeleteFirst(3.14);
    assert(X.GetNrOfAparitions(3.14) == 2); // verific daca a fost eliminat 3.14 o data

    assert(X.NrOfDistinctElements() == 3); // verific daca numara corect elementele distincte

    X.Delete(3.14);
    assert(X.Search(3.14) == -1); // verific daca l-a eliminat complet pe 3.14

}

int main()
{
    Tests_Multi_Set();
    cout << "Testele au trecut!" << endl;

    return 0;
}

