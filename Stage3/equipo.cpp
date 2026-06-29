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
void Equipo::mover(double delta_tiempo, double limiteAncho, double limiteAlto ) {
    double angulo_rad = angulo * M_PI / 180.0;

    // 2. Calcular nueva posición
    // En Qt, el eje Y crece hacia abajo, por eso restamos si queremos que 90° sea "hacia arriba"
    double nueva_x = posicion_x + (rapidez * cos(angulo_rad) * delta_tiempo);
    double nueva_y = posicion_y - (rapidez * sin(angulo_rad) * delta_tiempo);

    // 3. Lógica de rebote en los bordes
    if (nueva_x <= 0 || nueva_x >= limiteAncho) {
        angulo = 180.0 - angulo; // Invierte componente X
        nueva_x = (nueva_x <= 0) ? 0 : limiteAncho;
    }
    if (nueva_y <= 0 || nueva_y >= limiteAlto) {
        angulo = -angulo; // Invierte componente Y
        nueva_y = (nueva_y <= 0) ? 0 : limiteAlto;
    }

    // 4. Asegurar que el ángulo se mantenga entre 0 y 360
    while (angulo < 0) angulo += 360.0;
    while (angulo >= 360.0) angulo -= 360.0;

    // 5. Actualizar posiciones internas
    posicion_x = nueva_x;
    posicion_y = nueva_y;
}