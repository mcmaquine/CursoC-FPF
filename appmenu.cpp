#include <iostream>
#include <string>

#include "datetime.h"
#include "appmenu.h"

using namespace std;

static Agenda *_agenda = nullptr;
static bool _changed = false;

inline void __print_appoint(DateTime const &dt, string const &descr)
{
    cout << dt << ": " << descr << endl;
}

inline bool __read_date(DateTime &dt)
{
    if (!dt.read(cin))
    {
        cout << "Invalid data/time informed" << endl;
        return false;
    }
    return true;
}

inline void __read_description(string &descr)
{
#ifdef _WIN32
    getline(cin, descr);
#endif
    getline(cin, descr);
}

void AppMenu::prepare(Agenda *agenda)
{
    _agenda = agenda;
    _changed = false;
}

bool AppMenu::changed()
{
    return _changed;
}

int AppMenu::show()
{
    if (nullptr == _agenda)
    {
        cout << "Not prepared yet - missing Agenda" << endl;
        return -1;
    }

    cout << "[1] Add appointment" << endl;
    cout << "[2] Show appointment" << endl;
    cout << "[3] Edit appointment" << endl;
    cout << "[4] Delete appointment" << endl;
    cout << "[5] List appointments" << endl;
    cout << "[0] Exit" << endl;
    cout << "Choose an option: ";

    int x;
    cin >> x;

    int ret;
    switch (x)
    {
    case 0:
        ret = -1;
        break;

    case 1:
        ret = addAppointment();
        break;

    case 2:
        ret = showAppointment();
        break;

    case 3:
        ret = editAppointment();
        break;

    case 4:
        ret = deleteAppointment();
        break;

    case 5:
        ret = listAppointments();
        break;

    default:
        cout << "Invalid option" << endl;
        ret = -2;
        break;
    }

    return ret;
}

int AppMenu::addAppointment()
{
    cout << endl;
    cout << "Inform a date and time: ";

    DateTime dt;
    if (__read_date(dt))
    {
        cout << endl;
        cout << "Inform the description: ";

        string descr;
        __read_description(descr);

        _changed = _changed || _agenda->addAppointment(dt, descr);

        return 0;
    }

    return -3;
}

int AppMenu::showAppointment()
{
    cout << endl;
    cout << "Inform a date and time: ";

    DateTime dt;
    if (__read_date(dt))
    {
        cout << _agenda->getAppointment(dt) << endl;
        return 0;
    }

    return -3;
}

int AppMenu::editAppointment()
{
    cout << endl;
    cout << "Inform date and time: ";

    DateTime dt;
    if (!__read_date(dt))
    {
        return -3;
    }

    // cout << "Change date and time? (y/n) ";

    string s;
    // cin >> s;

    // if (s[0] == 'y' || s[0] == 'Y')
    // {
    //     cout << endl;
    //     cout << "Inform the new date and time: ";
    //     if (!__read_date(dt))
    //     {
    //         return -3;
    //     }
    // }

    cout << endl;
    cout << "Inform the new description: ";
    __read_description(s);

    _agenda->changeAppointment(dt, s);

    _changed = true;

    return 0;
}

int AppMenu::deleteAppointment()
{
    cout << endl;
    cout << "Inform date and time: ";

    DateTime dt;
    if (__read_date(dt))
    {
        _agenda->deleteAppointment(dt);

        _changed = true;

        return 0;
    }

    return -3;
}

int AppMenu::listAppointments()
{    
    for (auto i = _agenda->begin(); i != _agenda->end(); ++i)
    {
        cout << i->first << " - " << i->second << endl;
    }

    return 0;
}
