#pragma once

#include "date.h"

class DateTime : public Date
{
public:
    DateTime();
    DateTime(int day, int month, int year, int hour, int min, int sec);
    DateTime(DateTime const &other);

    int hour() const { return _hr; };
    int minute() const { return _mi; }
    int second() const { return _se; }

    void hour(int hr) { if (hr >= 0 && hr < 24)_hr = hr; };
    void minute(int mi) { if (mi >= 0 && mi < 60) _mi = mi; }
    void second(int se) { if (se >= 0 && se < 60) _se = se; }

    DateTime& operator =(DateTime const &other);

    bool operator ==(DateTime const &other) const;

    void write(std::ostream &o) const;

    void read(std::istream &a);

private:
    int _hr, _mi, _se;
};


std::ostream& operator <<(std::ostream &o, DateTime const &date);

std::istream& operator >>(std::istream &a, DateTime &date);
