/*
 * Date.cpp
 *
 *  Created on: 10 de jul de 2022
 *      Author: maquine
 */
#include <iostream>

class Date
{
public:
	Date() : _dy(1), _mo(1), _yr(1) { }
	Date(int day, int month, int year)
	{
		if( day > 0 && day < 32 ) _dy = day;
		if( month > 0 && month < 13 ) _mo = month;
		if( year != 0 ) _yr = year;
	}

	Date( Date const &other) : _dy(other._dy), _mo(other._mo), _yr(other._yr)
	{ }


	int day() const { return _dy; }
	int month() const { return _mo; }
	int year() const { return _yr; }

	void day( int day )
	{
		if ( day > 0 && day < 32)
			_dy = day;
	}

	void month ( int month )
	{
		if( month > 0 && month < 13 )
		_mo = month;
	}

	void year ( int year )
	{
		if( year != 0)
			_yr = year;
	}

	bool bissexto()
	{
		return ( _yr % 400 == 0 || ( _yr % 4 == 0 && ( _yr % 100 != 0 )) );
	}

	Date& operator =(Date const &other)
	{
		_dy = other._dy;
		_mo = other._mo;
		_yr = other._yr;
		return *this;
	}

	bool operator ==( Date const &other) const
	{
		return _dy == other._dy && _mo == other._mo && _yr == other._yr;
	}

	bool operator <(Date const &other) const
	{
		return _yr < other._yr ||
				(( _yr == other._yr && _mo < other._mo ) ||
				( _mo == other._mo && _dy < other._dy));
	}

	Date& operator ++()
	{
		_dy++;
		return *this;
	}

	std::ostream& operator <<(std::ostream os, Date const &d)
	{
		os << d.day() << '/' << d.month() << '/' << d.year() << std::endl;
		return os;
	}

	//implementar +=

private:
	int _dy, _mo, _yr;
};
