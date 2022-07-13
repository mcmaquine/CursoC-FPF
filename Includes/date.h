#pragma once
#include <iostream>

class Date
{
public:
	Date();
	Date(int day, int month, int year); // @suppress("Class members should be properly initialized")
	Date( Date const &other );

	int day() const { return _dy; }
	int month() const { return _mo; }
	int year() const { return _yr;}

	void day( int day);
	void month( int month );
	void year( int year);

	bool isLeapYear();

	Date& operator =(Date const &other );

	bool operator ==( Date const &other) const;

	bool operator <( Date const &other) const;

	Date& operator ++();

	Date operator ++(int dummy);

	Date& operator --();

	Date operator --( int dummy );

	void write(std::ostream &o) const;

	void read( std::istream &a);

private:

	void _add_day(int days);
	void _add_month( int months);

	int _dy, _mo, _yr;
	int _modays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

std::ostream& operator <<(std::ostream &o, Date const &date);

std::istream& operator >>(std::istream &a, Date &date);
