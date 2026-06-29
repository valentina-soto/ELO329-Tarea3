#ifndef ELOTELTAG_H
#define ELOTELTAG_H

#include "equipo.h"

class EloTelTag : public Equipo
{
public:
    EloTelTag(std::string n, double x, double y, double rap, double ang, double d_ang);
};

#endif // ELOTELTAG_H
