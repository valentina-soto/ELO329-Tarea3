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

void ETNube::reportarPosicionCelular(std::string nombre, double x, double y) {
    posicionesCelulares[nombre] = {x, y};
}

std::pair<double,double> ETNube::getPosicionCelular(std::string nombre) const {
    if (posicionesCelulares.count(nombre))
        return posicionesCelulares.at(nombre);
    return {0, 0};
}

bool ETNube::tienePosicionCelular(std::string nombre) const {
    return posicionesCelulares.count(nombre) > 0;
}

void ETNube::reportarPosicionDispositivo(std::string nombre, std::string dueno, double x, double y) {
    posicionesDispositivos[nombre] = {dueno, x, y};
}

std::map<std::string, std::pair<double,double>> ETNube::getPosicionesDispositivosPorDueno(std::string dueno) const {
    std::map<std::string, std::pair<double,double>> resultado;
    for (const auto& [nombre, info] : posicionesDispositivos) {
        if (info.dueno == dueno)
            resultado[nombre] = {info.x, info.y};
    }
    return resultado;
}
