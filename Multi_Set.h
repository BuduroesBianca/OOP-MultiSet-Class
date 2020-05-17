#pragma once

#include<iostream>
#include "Comparator.h"
#include "Node.h"

using namespace std;

template<typename T, typename Comparator> class Multi_Set
{
    node<T>* start;
    node<T>* end;
    int length;
    Comparator compare;

    void RemoveNode(int); // sterge un element de pe o anumita pozitie
    void makeDistinct(); // transforma un multiset intr-un set
    
public:

    Multi_Set():length(0), start(NULL), end(NULL) {} // constructor fara parametri
    Multi_Set(Multi_Set& s); // constructor de copiere
    Multi_Set(node<T>*);
    ~Multi_Set(); // destructor
    node<T>* getStart() const { return this->start; }
    int getLength() const { return this->length; }

    void Insert(T); // insereaza in Multi_Set o anumita valoare
    void DeleteFirst(T); // sterge doar o aparitie a unei valori date
    void Delete(T); // sterge toate aparitiile unei valori
    int GetNrOfAparitions(T); // returneaza numarul aparitiilor unei valori
    int NrOfDistinctElements() ; // returneaza numarul de valori distincte
    int Search(T) ; // cauta o valoare in Multi_Set (-1 daca nu exista, altfel returneaza pozitia)

    friend ostream& operator << <>(ostream&, const Multi_Set<T,Comparator>&);
    Multi_Set<T,Comparator>& operator = (Multi_Set<T,Comparator>&);
};

template<typename T, typename Comparator> // constructor
inline Multi_Set<T, Comparator>::Multi_Set(node<T>* n)
{
    this->start = n;
    this->end = n;
}

template<typename T, typename Comparator> // constructor de copiere
inline Multi_Set<T, Comparator>::Multi_Set(Multi_Set& M)
{
    node* p = M.start;
    start = new node(p->getInfo(), NULL);
    length = 1;
    node* q = start;
    p = p->getNext();

    while (p->getNext() != NULL) 
    {
        node* aux = new node(p->getInfo(), NULL);
        q->setNext(aux);
        q = q->getNext();
        length++;
        p = p->getNext();
    }
    end = new node(p->getInfo(), NULL);
    q->setNext(end);
    length++;
}

template<typename T, typename Comparator> 
inline Multi_Set<T, Comparator>::~Multi_Set() //destructor
{
    node<T>* p = start;
    while (p != NULL) 
    {
        node<T>* q = p;
        p = p->getNext();
        delete q;
    }
    start = end = NULL;
    length = 0;
}

template<typename T, typename Comparator>
inline void Multi_Set<T, Comparator>::Insert(T value) // metoda de insertie
{
    if (length == 0) // daca lista este goala insereaza pe prima pozitie
    {
        start = end = new node<T>(value, NULL);
        length = 1;
    }
    else // daca nu insereaza la final
    {
        end->setNext(new node<T>(value, NULL));
        end = end->getNext();
        length++;
    }
}

template<typename T, typename Comparator>
inline void Multi_Set<T, Comparator>::DeleteFirst(T value) // sterge prima aparitie
{
    if (this->Search(value) != -1) // daca valoarea este in lista
    {
        int poz = this->Search(value); // aflu pozitia de pe care sterg
        RemoveNode(poz); // sterg elementul
    }

}

template<typename T, typename Comparator>
inline void Multi_Set<T, Comparator>::Delete(T value) // sterge toate aparitiile valorii
{
    while (this->Search(value) != -1) // cat timp elementul inca exista
    {
        int poz = this->Search(value); // aflu pozitia
        RemoveNode(poz); // sterg elementul de pe pozitia aflata
    }
}

template<typename T, typename Comparator>
inline void Multi_Set<T, Comparator>::RemoveNode(int i) // metoda de stergere de pe o anumita pozitie
{
    if (i < 0 || i >= length)  // daca pozitia nu este una acceptabila
    {
        return;
    }
    node<T>* p = start;

    if (i == 0) // daca e vorba de prima pozitie
    {
        if (length == 1 || length == 0)
        {
            end = start = NULL; 
        }
        else // daca nu
        {
            start = start->getNext();
            delete p;
        }
    }
    else 
    {
        for (int j = i; j > 1; j--) 
        {
            p = p->getNext();
        }
        node<T>* o = p->getNext();
        p->setNext(o->getNext());
        delete o;
    }
    length--;
}


template<typename T, typename Comparator>
inline int Multi_Set<T, Comparator>::Search(T value) // cauta un element in Multi_Set
{
    node<T>* p = start;

    if (p != NULL) // daca Multi_Setul nu e vid
    {
        for (int i = 0; i < length; i++)
        {
            if (compare(p->getInfo(),value) == 0) // daca am gasit
                return i; // ii returnez pozitia         
            p = p->getNext();
        }
    }
    return -1;
}

template<typename T, typename Comparator>
inline int Multi_Set<T, Comparator>::GetNrOfAparitions(T value)  // returneaza nr aparitiilor unei valori
{
    node<T>* current = this->start;
    int count = 0;
    while (current != NULL) 
    {
        if (compare(current->getInfo(),value) == 0)
            count++;
        current = current->getNext();
    }
    return count;
}

template<typename T, typename Comparator>
inline int Multi_Set<T, Comparator>::NrOfDistinctElements() 
{
    this->makeDistinct();
    return this->length;
}


template<typename T, typename Comparator>
void Multi_Set<T, Comparator>::makeDistinct()
{
    if (this->length >= 2)
    {
        int i = 0;
        node<T>* aux = this->start;
        while (this->GetNrOfAparitions(aux->getInfo()) > 1)
        {
            RemoveNode(i);
            aux = this->start;
        }
        i++;
        while (i < this->length)
        {
            if (aux->getNext() != NULL && this->GetNrOfAparitions(aux->getNext()->getInfo()) > 1)
                RemoveNode(i);
            else
            {
                aux = aux->getNext();
                i++;
            }
        }
    }
}

template<typename T, typename Comparator>
inline Multi_Set<T, Comparator>& Multi_Set<T, Comparator>::operator = (Multi_Set<T, Comparator>& M)
{
    if (this != &M)
    {
        node<T>* aux = M.start;
        int iterator = 0;
        while (iterator < M.length)
        {
            Insert(aux->getInfo());
            aux = aux->getNext();
            iterator++;
        }
        length = M.length;
    }
    return *this;
}

template<typename T, typename Comparator>
inline ostream& operator << <>(ostream& out, const Multi_Set<T, Comparator>& M)
{
    if (M.length > 0)
    {
        node<T>* aux = M.start; int i = 1;
        while (i <= M.length)
        {
            out << aux->getInfo() << ' ';
            aux = aux->getNext();
            i++;
        }
    }
    else out << "Multi_Set vid";
    return out;
}



