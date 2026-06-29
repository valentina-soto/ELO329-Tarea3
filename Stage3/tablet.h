#ifndef TABLET_H
#define TABLET_H

#include "equipo.h"

class Tablet : public Equipo
{
public:
    Tablet(std::string n, double x, double y, double rap, double ang, double d_ang);
};

#endif // TABLET_H
