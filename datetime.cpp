#include <iostream>
#include "datetime.h"

static bool __is_valid_time(int h, int m, int s)
{
    return h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60;
}

DateTime::DateTime() : Date(), _hr(0), _mi(0), _se(0)
{

}

DateTime::DateTime(int day, int month, int year, int hour, int min, int sec) :
    Date(day, month, year), _hr(hour), _mi(min), _se(sec)
{
    if (!__is_valid_time(_hr, _mi, _se))
    {
        _hr = _mi = _se = 0;
    }
}

DateTime::DateTime(DateTime const &other) :
    Date(other), _hr(other._hr), _mi(other._mi), _se(other._se)
{

}

DateTime& DateTime::operator =(DateTime const &other)
{
    Date::operator =(other);
    //static_cast<Date>(*this) = other;

    _hr = other._hr;
    _mi = other._mi;
    _se = other._se;

    return *this;
}

bool DateTime::operator ==(DateTime const &other) const
{
    return Date::operator==(other) && 
        _hr == other._hr && _mi == other._mi && _se == other._se;
}

bool DateTime::operator >(DateTime const &other) const
{
	return Date::operator >=(other) ||
		(_hr > other._hr ||
		(_hr == other._hr && (_mi > other._mi ||
		(_mi == other._mi && _se > other._se))));
}

bool DateTime::operator <(DateTime const &other) const
{
	return Date::operator <=(other) ||
			(_yr < other._yr ||
			(_yr == other._yr && (_mo < other._mo ||
			(_mo == other._mo && _dy < other._dy))));
}

bool DateTime::operator >=(DateTime const &other) const
{
	return !DateTime::operator <(other);
}

bool DateTime::operator <=(DateTime const &other) const
{
	return !DateTime::operator >(other);
}

void DateTime::write(std::ostream &o) const
{
    o << _dy << "-" << _mo << "-" << _yr;
    o << " " << _hr << ":" << _mi << ":" << _se;
}

void DateTime::read(std::istream &a)
{
    Date::read(a);

    int h, m, s;
    a >> h >> m >> s;

    if (__is_valid_time(h, m, s))
    {
        _hr = h, _mi = m, _se = s;
    }
}

std::ostream& operator <<(std::ostream &o, DateTime const &dt)
{
    dt.write(o);
    return o;
}

std::istream& operator >>(std::istream &a, DateTime &dt)
{
    dt.read(a);
    return a;
}
