/*
 * datetime.hpp
 *
 *  Created on: 12 de jul de 2022
 *      Author: maquine
 */

#ifndef INCLUDES_DATETIME_HPP_
#define INCLUDES_DATETIME_HPP_

#include "date.h"

class DateTime : public Date
{
public:
	DateTime();

	int hour() const { return _hr; }
	int minute() const { return _mi; }
	int year() const { return _se; }

	void hour( int hr ) { _hr = hr; }
	void minute( int mi ) { _mi = mi;}
	//void se

private:
	int _hr, _mi, _se;
};
// aula 2 - Implementar todos os metodos que estao faltando
// o mais importante eh o <

#endif /* INCLUDES_DATETIME_HPP_ */
