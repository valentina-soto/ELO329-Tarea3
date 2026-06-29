#ifndef ETNUBE_H
#define ETNUBE_H

#include <string>
#include <vector>

struct Reporte {
    std::string nombreDispositivo;
    std::string nombreDueno;
    double celularX;
    double celularY;
};

class ETNube {
private:
    std::vector<Reporte> reportes;

public:
    void agregarReporte(std::string dispositivo, std::string dueno, double x, double y);
    std::vector<Reporte> getReportesPorDueno(std::string dueno) const;
    std::vector<Reporte> getTodosLosReportes() const;
};

#endif // ETNUBE_H
