#include "findmydialog.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLayoutItem>

FindMyDialog::FindMyDialog(const std::string& dueno, ETNube* nube,
                           QGraphicsScene* scene,
                           std::map<std::string, Equipo*>* dispositivos,
                           QWidget* parent)
    : QDialog(parent), dueno(dueno), nube(nube), scene(scene), dispositivos(dispositivos)
{
    setWindowTitle(QString("Find My - %1").arg(QString::fromStdString(dueno)));
    resize(480, 300);
    setAttribute(Qt::WA_DeleteOnClose);

    layout = new QVBoxLayout(this);
    actualizar();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FindMyDialog::actualizar);
    timer->start(1000);
}

FindMyDialog::~FindMyDialog()
{
    for (auto& [nombre, lineas] : lineasTraza) {
        for (auto* linea : lineas) {
            scene->removeItem(linea);
            delete linea;
        }
    }
}

void FindMyDialog::toggleTraza(const std::string& nombre)
{
    if (trazasActivas.count(nombre)) {
        trazasActivas.erase(nombre);
        for (auto* linea : lineasTraza[nombre]) {
            scene->removeItem(linea);
            delete linea;
        }
        lineasTraza[nombre].clear();
        ultimaPosicion.erase(nombre);
    } else {
        trazasActivas.insert(nombre);
        if (dispositivos->count(nombre)) {
            auto* eq = (*dispositivos)[nombre];
            ultimaPosicion[nombre] = {eq->getX(), eq->getY()};
        }
    }
    actualizar();
}

void FindMyDialog::actualizar()
{
    // Actualizar trazas activas
    for (const auto& nombre : trazasActivas) {
        if (dispositivos->count(nombre)) {
            auto* eq = (*dispositivos)[nombre];
            double newX = eq->getX(), newY = eq->getY();
            if (ultimaPosicion.count(nombre)) {
                auto [lastX, lastY] = ultimaPosicion[nombre];
                QGraphicsLineItem* linea = scene->addLine(lastX, lastY, newX, newY,
                                                           QPen(Qt::yellow, 2));
                linea->setZValue(2);
                lineasTraza[nombre].append(linea);
            }
            ultimaPosicion[nombre] = {newX, newY};
        }
    }

    // Reconstruir layout
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Obtener último reporte por dispositivo
    auto reportes = nube->getReportesPorDueno(dueno);
    if (reportes.empty()) {
        layout->addWidget(new QLabel("No hay reportes disponibles aún."));
        return;
    }

    std::map<std::string, Reporte> ultimoReporte;
    for (const auto& r : reportes)
        ultimoReporte[r.nombreDispositivo] = r;

    for (const auto& [nombre, r] : ultimoReporte) {
        QWidget* fila = new QWidget();
        QHBoxLayout* filaLayout = new QHBoxLayout(fila);
        filaLayout->setContentsMargins(0, 0, 0, 0);

        QString texto = QString("Dispositivo: %1  |  Pos. celular: (%2, %3)")
            .arg(QString::fromStdString(nombre))
            .arg(r.celularX, 0, 'f', 1)
            .arg(r.celularY, 0, 'f', 1);
        filaLayout->addWidget(new QLabel(texto));

        if (dispositivos->count(nombre)) {
            bool activa = trazasActivas.count(nombre) > 0;
            QPushButton* btn = new QPushButton(activa ? "Traza ON" : "Traza");
            connect(btn, &QPushButton::clicked, [this, nombre]() {
                toggleTraza(nombre);
            });
            filaLayout->addWidget(btn);
        }

        layout->addWidget(fila);
    }
}
