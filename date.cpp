/*
 * Date.cpp
 *
 *  Created on: 10 de jul de 2022
 *      Author: maquine
 */
#include <iostream>
#include "date.h"

Date::Date() : _dy(1), _mo(1), _yr(1) { }
Date::Date(int dy, int mo, int yr)
{
	year(yr);
	month(mo);
	day(dy);
}

Date::Date( Date const &other) : _dy(other._dy), _mo(other._mo), _yr(other._yr)
{ }

void Date::day( int day )
{
	if( isLeapYear() && _mo == 2 && day > 1 && day < 30)
		_dy = day;
	else if ( day > 0 && day <= _modays[_mo - 1])
		_dy = day;
	else
		_dy = 1;
}

void Date::month ( int month )
{
	if( month > 0 && month < 13)
		_mo = month;
	else
		_mo = 1;
}

void Date::year ( int year )
{
	if( year != 0)
		_yr = year;
	else
		_yr = 1990;
}

bool Date::isLeapYear()
{
	return ( _yr % 400 == 0 || ( _yr % 4 == 0 && ( _yr % 100 != 0 )) );
}

void Date::_add_day( int days )
{
	int diff = 0;

	if( isLeapYear() )
	{

	}else
	{

	}

	if( diff <= 0 )
	{

	}
}

Date& Date::operator =(Date const &other)
{
	_dy = other._dy;
	_mo = other._mo;
	_yr = other._yr;
	return *this;
}

bool Date::operator ==( Date const &other) const
{
	return _dy == other._dy && _mo == other._mo && _yr == other._yr;
}

bool Date::operator <(Date const &other) const
{
	return _yr < other._yr ||
			(( _yr == other._yr && _mo < other._mo ) ||
			( _mo == other._mo && _dy < other._dy));
}

Date& Date::operator ++()
{
	_dy++;
	return *this;
}

Date Date::operator ++( int dummy )
{
	Date d(*this);
	++_dy;
	return d;
}

Date& Date::operator --()
{
	--_dy;
	return *this;
}

Date Date::operator --( int dummy )
{
	Date d(*this);
	--_dy;
	return d;
}

void Date::read ( std::istream &a )
{
	a >> _dy >> _mo >> _yr;
}

void Date::write ( std::ostream &o) const
{
	o << _dy << "/" << _mo << "/" << _yr;
}

std::ostream& operator <<(std::ostream& os, Date const &d)
{
	os << d.day() << '/' << d.month() << '/' << d.year();
	return os;
}

std::istream& operator >>( std::istream& is, Date &d)
{
	int x, y, z;
	is >> x >> y >> z;
	d.day( x );
	d.month( y );
	d.year( z );

	return is;
}
	//implementar +=
