/*
 * main.cpp
 *
 *  Created on: 5 de jul de 2022
 *      Author: maquine
 */
#include <iostream>

#include "date.h"

using namespace std;

template< typename T >

void troca( T &a, T &b)
{
	T t = a;
	a = b;
	b = t;
}

int main(int argc, char **argv)
{
	int year = 2024;
	Date d(28,2,year);

	if( d.isLeapYear() )
		std::cout << d << " eh bissexto";
	else
		std::cout << d << " nao eh bissexto";

	return 0;
}

