#ifndef STAGE4_H
#define STAGE4_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <vector>
#include <string>
#include <map>
#include <QTimer>
#include "cellular.h"
#include "cellularview.h"
#include "tablet.h"
#include "tabletview.h"
#include "eloteltag.h"
#include "eloteltagview.h"
#include "etnube.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct RadarInfo {
    double x, y;
    double radio;
    std::string dispositivo;
    std::string dueno;
    QGraphicsEllipseItem* circulo;
};

class Stage4 : public QMainWindow
{
    Q_OBJECT

public:
    Stage4(QWidget *parent = nullptr);
    ~Stage4();

private slots:
    void avanzarSimulacion();
    void play();
    void pause();

private:
    Ui::MainWindow *ui;

    // interfaz gráfica
    QGraphicsScene *scene;
    QGraphicsView *view;

    // tiempo
    QTimer *timer;
    double deltaTiempoConfig;
    double limiteX;
    double limiteY;

    // listas para almacenar en memoria
    std::vector<Cellular*> listaCelulares;
    std::vector<CellularView*> listaVistasCelulares;
    std::vector<double> tiempoCelularReporte;

    std::vector<Tablet*> listaTablets;
    std::vector<TabletView*> listaVistasTablets;
    std::vector<std::string> duenoDeTablets;
    std::vector<double> tiempoTabletRadar;

    std::vector<EloTelTag*> listaTags;
    std::vector<EloTelTagView*> listaVistasTags;
    std::vector<std::string> duenoDeTags;
    std::vector<double> tiempoTagRadar;

    // radares activos
    std::vector<RadarInfo> radaresActivos;

    // nube
    ETNube nube;

    // mapa nombre dispositivo -> puntero al equipo (para traza)
    std::map<std::string, Equipo*> mapaDispositivos;

    void cargarConfiguracion();
    void actualizarRadares();
};

#endif // STAGE4_H
