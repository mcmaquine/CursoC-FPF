/*
 * Date.cpp
 *
 *  Created on: 10 de jul de 2022
 *      Author: maquine
 */
#include <iostream>
#include "date.h"

using namespace std;

static int __month_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static int __leap_factor(int m, int y)
{
    return m == 2 && ((y % 4) == 0);
}

static bool inline __day_exceed(int d, int m, int y)
{
    return d > (__month_days[m - 1] + __leap_factor(m, y));
}

static bool inline __is_valid_day(int d, int m, int y)
{
    return d > 0 && !__day_exceed(d, m, y);
}

static bool inline __is_valid_month(int m)
{
    return m > 0 && m < 13;
}

static bool __is_valid(int d, int m, int y)
{
    return y > 0 && __is_valid_month(m) && __is_valid_day(d, m, y);
}

Date::Date() : _dy(1), _mo(1), _yr(1)
{
}

Date::Date(int day, int month, int year) : _dy(day), _mo(month), _yr(year)
{
    if (!__is_valid(day, month, year))
    {
        _dy = _mo = _yr = 1;
    }
}

Date::Date(Date const &other) : _dy(other._dy), _mo(other._mo), _yr(other._yr)
{
}

void Date::day(int dy)
{
    if (__is_valid_day(dy, _mo, _yr + 1))
    {
        _dy = dy;
    }
}

void Date::month(int mo)
{
    if (__is_valid_month(mo))
    {
        _mo = mo;
    }
}

void Date::year(int yr)
{
    if (yr > 0)
    {
        _yr = yr;
    }
}

bool Date::is_leap_year()
{
	return _yr % 400 == 0 || ( _yr % 4 == 0 && _yr % 100 != 0 );
}

Date& Date::operator =(Date const &other)
{
    _dy = other._dy, _mo = other._mo, _yr = other._yr;
    return *this;
}

bool Date::operator ==(Date const &other) const
{
    return _dy == other._dy && _mo == other._mo && _yr == other._yr;
}

bool Date::operator !=(Date const &other) const
{
    return !operator ==(other);
}

bool Date::operator <(Date const &other) const
{
    return _yr < other._yr ||
          (_yr == other._yr && (_mo < other._mo ||
                               (_mo == other._mo && _dy < other._dy)));
}

bool Date::operator >=(Date const &other) const
{
    return !operator <(other);
}

bool Date::operator >(Date const &other) const
{
    return _yr > other._yr ||
          (_yr == other._yr && (_mo > other._mo ||
                               (_mo == other._mo && _dy > other._dy)));
}

bool Date::operator <=(Date const &other) const
{
    return !operator >(other);
}

Date& Date::operator ++()
{
    day_up();
    return *this;
}

Date Date::operator ++(int dummy)
{
    Date d(*this);
    day_up();
    return d;
}

Date& Date::operator +=( int days ){
	for( int i = 0; i < days; i++)
	{
		day_up();
	}

	return *this;
}

Date& Date::operator -=( int days )
{
	for( int i = 0; i < days; i++){
		day_down();
	}

	return *this;
}

void Date::day_up()
{
    if (__day_exceed(++_dy, _mo, _yr))
    {
        _dy = 1;
        (++_mo) > 12 && (_mo = 1, ++_yr);
    }
}

Date& Date::operator --()
{
    day_down();
    return *this;
}

Date Date::operator --(int dummy)
{
    Date d(*this);
    day_down();
    return d;
}

void Date::day_down()
{
    if (--_dy < 1)
    {
        (--_mo) > 0 || ((_mo = 12) && --_yr);
        _dy = __month_days[_mo - 1] + __leap_factor(_mo, _yr);
    }
}

void Date::write(ostream &o) const
{
    o << _dy << "/" << _mo << "/" << _yr;
}

void Date::read(istream &a)
{
    int d, m, y;
    a >> d >> m >> y;
    if (__is_valid(d, m, y))
    {
        _dy = d, _mo = m, _yr = y;
    }
}

ostream& operator <<(ostream &o, Date const &date)
{
    date.write(o);
    return o;
}

istream& operator >>(istream &a, Date &date)
{
    date.read(a);
    return a;
}

	//implementar +=
