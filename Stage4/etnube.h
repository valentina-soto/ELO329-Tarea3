#ifndef ETNUBE_H
#define ETNUBE_H

#include <string>
#include <vector>
#include <map>

struct Reporte {
    std::string nombreDispositivo;
    std::string nombreDueno;
    double celularX;
    double celularY;
};

class ETNube {
private:
    std::vector<Reporte> reportes;
    std::map<std::string, std::pair<double,double>> posicionesCelulares;

public:
    void agregarReporte(std::string dispositivo, std::string dueno, double x, double y);
    std::vector<Reporte> getReportesPorDueno(std::string dueno) const;
    std::vector<Reporte> getTodosLosReportes() const;

    void reportarPosicionCelular(std::string nombre, double x, double y);
    std::pair<double,double> getPosicionCelular(std::string nombre) const;
};

#endif // ETNUBE_H
