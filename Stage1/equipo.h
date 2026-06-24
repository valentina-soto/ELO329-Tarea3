#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>

class Equipo
{
protected:
    std::string nombre;
    double posicion_x;
    double posicion_y;
    double rapidez;
    double angulo;
    double delta_angulo;

public:
    Equipo(std::string n, double x, double y, double rap, double ang, double d_ang);

    virtual ~Equipo() = default;

    double getX() const;
    double getY() const;
    std::string getNombre() const;

    virtual void mover(double delta_tiempo);
};

#endif // EQUIPO_H
