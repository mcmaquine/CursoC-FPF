
#include "agenda.h"

class AppMenu
{
public:
    static void prepare(Agenda *agenda);

    static bool changed();
    
    static int show();

private:
    static int addAppointment();

    static int showAppointment();

    static int editAppointment();

    static int deleteAppointment();

    static int listAppointments();
};
