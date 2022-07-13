#pragma once
#include <iostream>

class Date
{
public:
    Date();
    Date(int day, int month, int year);
    Date(Date const &other);

    int day() const { return _dy; };
    int month() const { return _mo; }
    int year() const { return _yr; }

    void day(int dy);
    void month(int mo);
    void year(int yr);

    Date& operator =(Date const &other);

    bool operator ==(Date const &other) const;

    bool operator !=(Date const &other) const;

    bool operator <(Date const &other) const;

    bool operator >=(Date const &other) const;

    bool operator >(Date const &other) const;

    bool operator <=(Date const &other) const;

    Date& operator ++();

    Date operator ++(int dummy);

    Date& operator --();

    Date operator --(int dummy);

    void write(std::ostream &o) const;

    void read(std::istream &a);

protected:
    int _dy, _mo, _yr;

private:
    void day_up();
    void day_down();
};

std::ostream& operator <<(std::ostream &o, Date const &date);

std::istream& operator >>(std::istream &a, Date &date);
