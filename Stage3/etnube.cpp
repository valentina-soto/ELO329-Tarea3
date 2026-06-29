#include "etnube.h"

void ETNube::agregarReporte(std::string dispositivo, std::string dueno, double x, double y) {
    reportes.push_back({dispositivo, dueno, x, y});
}

std::vector<Reporte> ETNube::getReportesPorDueno(std::string dueno) const {
    std::vector<Reporte> resultado;
    for (const auto& r : reportes) {
        if (r.nombreDueno == dueno) {
            resultado.push_back(r);
        }
    }
    return resultado;
}

std::vector<Reporte> ETNube::getTodosLosReportes() const {
    return reportes;
}
