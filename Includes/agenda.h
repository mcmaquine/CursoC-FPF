#pragma once

#include <map>
#include <string>

#include "datetime.h"

class Agenda
{
public:
    Agenda() { }

    bool addAppointment(DateTime dt, std::string const &descr);
    std::string getAppointment(DateTime dt) const;
    bool changeAppointment(DateTime dt, std::string const &descr);
    bool deleteAppointment(DateTime dt);

    std::map<DateTime, std::string> listAppointments() const { return _data; }

    std::map<DateTime, std::string>::const_iterator begin() const { return _data.begin(); }
    std::map<DateTime, std::string>::const_iterator end() const { return _data.end(); }

private:
    std::map<DateTime, std::string> _data;
};
