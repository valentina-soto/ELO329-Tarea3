#ifndef CELLULAR_H
#define CELLULAR_H

#include "equipo.h"

class Cellular : public Equipo
{
public:
    Cellular(std::string n, double x, double y, double rap, double ang, double d_ang);
};

#endif // CELLULAR_H
