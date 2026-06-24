#ifndef STAGE2_H
#define STAGE2_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <QTimer>
#include "cellular.h"
#include "cellularview.h"
#include "tablet.h"
#include "tabletview.h"
#include "eloteltag.h"
#include "eloteltagview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Stage2 : public QMainWindow
{
    Q_OBJECT

public:
    Stage2(QWidget *parent = nullptr);
    ~Stage2();

private slots:
    void avanzarSimulacion();

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

    std::vector<Tablet*> listaTablets;
    std::vector<TabletView*> listaVistasTablets;

    std::vector<EloTelTag*> listaTags;
    std::vector<EloTelTagView*> listaVistasTags;

    void cargarConfiguracion();
};

#endif // STAGE2_H
