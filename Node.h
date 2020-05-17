#pragma once
#include<iostream>
#include"Comparator.h"
using namespace std;

template<typename T, typename Comparator> class Multi_Set;
template<typename T> class node
{
	T info;
	node* next;

public:

	node() : info(NULL), next(NULL) {}
	node(T i, node* n) : info(i), next(n) {}
	void setInfo(T i) { this->info = i; }
	void setNext(node* n) { this->next = n; }
    T getInfo() const { return this->info; }
	node* getNext() const { return this->next; }
};

