/*
 * main.cpp
 *
 *  Created on: 5 de jul de 2022
 *      Author: maquine
 */
#include <iostream>
#include "Date.cpp"

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
	int year = 2022;
	Date d(1,1,year);

	if( d.bissexto() )
		std::cout << year << " eh bissexto";
	else
		std::cout << year << " nao eh bissexto";

	return 0;
}

