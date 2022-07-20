#include "agenda.h"

using namespace std;

bool Agenda::addAppointment(DateTime dt, std::string const &descr)
{
    if (_data.find(dt) == _data.end())
    {
        _data[dt] = descr;
        return true;
    }
    return false;
}

string Agenda::getAppointment(DateTime dt) const
{
    auto i = _data.find(dt);
    if (i == _data.end())
    {
        return string();
    }

    return i->second;
}

bool Agenda::changeAppointment(DateTime dt, std::string const &descr)
{
    auto i = _data.find(dt);
    if (i != _data.end())
    {
        i->second = descr;
        return true;
    }
    return false;
}

bool Agenda::deleteAppointment(DateTime dt)
{
    auto i = _data.find(dt);
    if (i != _data.end())
    {
        _data.erase(i);
        return true;
    }
    return false;
}