#pragma once

#include<iostream>

using namespace std;

template<typename T> class Comparator
{
public:
	int operator() (const T& value1, const T& value2) 
	{
		if (value1 > value2)
			return 1;
		else if (value1 < value2) 
			return -1;
		else return 0; // return 0 daca cele 2 valori sunt egale
	}
};


template<>
class Comparator<double>
{
public:
	int operator () (const double& value1, const double& value2)
	{
		if (value1 - int(value1) > value2 - int(value2))
			return 1;
		else if (value1 - int(value1) < value2 - int(value2))
			return -1;
		else return 0;
	}
};
