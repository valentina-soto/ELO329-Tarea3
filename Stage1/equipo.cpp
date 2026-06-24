#include "equipo.h"
#include <cmath>


Equipo::Equipo(std::string n, double x, double y, double rap, double ang, double d_ang)
    : nombre(n), posicion_x(x), posicion_y(y), rapidez(rap), angulo(ang), delta_angulo(d_ang)
{

}


// Get
double Equipo::getX() const {
    return posicion_x;
}
double Equipo::getY() const {
    return posicion_y;
}
std::string Equipo::getNombre() const {
    return nombre;
}

// Métodos
void Equipo::mover(double delta_tiempo) {

}