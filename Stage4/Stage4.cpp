#include "Stage4.h"
#include "ui_Stage4.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <cmath>
#include <cstdlib>
#include <QDebug>

Stage4::Stage4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setFocusPolicy(Qt::NoFocus);
    setCentralWidget(view);

    limiteX = 800;
    limiteY = 600;

    // Menú Simulation
    QMenu* simMenu = menuBar()->addMenu("Simulation");
    simMenu->addAction("Play",  this, &Stage4::play);
    simMenu->addAction("Pause", this, &Stage4::pause);

    cargarConfiguracion();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage4::avanzarSimulacion);
    timer->start(deltaTiempoConfig * 1000);
}

Stage4::~Stage4()
{
    delete ui;
}

void Stage4::cargarConfiguracion()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Seleccionar archivo de configuración", "",
                                                    "Text Files (*.txt);;All Files (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }

    QTextStream in(&file);

    QString imagenFondo = in.readLine().trimmed();
    QPixmap mapa(imagenFondo);
    if (!mapa.isNull()) {
        QGraphicsPixmapItem* fondo = scene->addPixmap(mapa);
        fondo->setZValue(-1);
        scene->setSceneRect(mapa.rect());
        limiteX = mapa.width();
        limiteY = mapa.height();
    }

    deltaTiempoConfig = in.readLine().toDouble();
    int numPersonas = in.readLine().toInt();

    for (int i = 0; i < numPersonas; ++i) {
        QString lineaPersona = in.readLine();
        QTextStream streamPersona(&lineaPersona);
        QString nombrePersona;
        int numTags, tieneTablet;
        streamPersona >> nombrePersona >> numTags >> tieneTablet;

        QString lineaCelular = in.readLine();
        QTextStream streamCelular(&lineaCelular);
        double celX, celY, rapidez, angulo, deltaAngulo;
        streamCelular >> celX >> celY >> rapidez >> angulo >> deltaAngulo;

        Cellular* nuevoCelular = new Cellular(nombrePersona.toStdString(), celX, celY, rapidez, angulo, deltaAngulo);
        listaCelulares.push_back(nuevoCelular);
        tiempoCelularReporte.push_back(0);
        CellularView* vistaCelular = new CellularView(nuevoCelular, &nube, scene, &mapaDispositivos);
        listaVistasCelulares.push_back(vistaCelular);
        scene->addItem(vistaCelular);

        if (numTags > 0) {
            QString lineaTags = in.readLine();
            QTextStream streamTags(&lineaTags);
            for (int j = 0; j < numTags; ++j) {
                QString tNombre;
                double tX, tY, tRap, tAng, tDAng;
                streamTags >> tNombre >> tX >> tY >> tRap >> tAng >> tDAng;

                EloTelTag* nuevoTag = new EloTelTag(tNombre.toStdString(), tX, tY, tRap, tAng, tDAng);
                listaTags.push_back(nuevoTag);
                duenoDeTags.push_back(nombrePersona.toStdString());
                tiempoTagRadar.push_back((rand() % 40) / 10.0);
                mapaDispositivos[tNombre.toStdString()] = nuevoTag;

                EloTelTagView* vistaTag = new EloTelTagView(nuevoTag);
                listaVistasTags.push_back(vistaTag);
                scene->addItem(vistaTag);
            }
        }

        if (tieneTablet == 1) {
            QString lineaTablet = in.readLine();
            QTextStream streamTablet(&lineaTablet);
            double tabX, tabY, tabRap, tabAng, tabDAng;
            streamTablet >> tabX >> tabY >> tabRap >> tabAng >> tabDAng;

            std::string tabletKey = "Tablet(" + nombrePersona.toStdString() + ")";
            Tablet* nuevaTab = new Tablet(tabletKey, tabX, tabY, tabRap, tabAng, tabDAng);
            listaTablets.push_back(nuevaTab);
            duenoDeTablets.push_back(nombrePersona.toStdString());
            tiempoTabletRadar.push_back((rand() % 50) / 10.0);
            mapaDispositivos[tabletKey] = nuevaTab;

            TabletView* vistaTab = new TabletView(nuevaTab, nombrePersona.toStdString(), &nube, scene, &mapaDispositivos);
            listaVistasTablets.push_back(vistaTab);
            scene->addItem(vistaTab);
        }
    }
    file.close();
}

void Stage4::actualizarRadares()
{
    // Tags emiten cada 4 segundos
    for (size_t i = 0; i < listaTags.size(); ++i) {
        tiempoTagRadar[i] += deltaTiempoConfig;
        if (tiempoTagRadar[i] >= 4.0) {
            tiempoTagRadar[i] = 0;
            RadarInfo r;
            r.x = listaTags[i]->getX();
            r.y = listaTags[i]->getY();
            r.radio = 0;
            r.dispositivo = listaTags[i]->getNombre();
            r.dueno = duenoDeTags[i];
            r.circulo = scene->addEllipse(0, 0, 1, 1, QPen(QColor(220, 50, 50, 180), 1.5));
            r.circulo->setZValue(1);
            radaresActivos.push_back(r);
        }
    }

    // Tablets emiten cada 5 segundos
    for (size_t i = 0; i < listaTablets.size(); ++i) {
        tiempoTabletRadar[i] += deltaTiempoConfig;
        if (tiempoTabletRadar[i] >= 5.0) {
            tiempoTabletRadar[i] = 0;
            RadarInfo r;
            r.x = listaTablets[i]->getX();
            r.y = listaTablets[i]->getY();
            r.radio = 0;
            r.dispositivo = listaTablets[i]->getNombre();
            r.dueno = duenoDeTablets[i];
            r.circulo = scene->addEllipse(0, 0, 1, 1, QPen(QColor(50, 180, 50, 180), 1.5));
            r.circulo->setZValue(1);
            radaresActivos.push_back(r);
        }
    }

    // Crecer y chequear radares activos
    for (auto it = radaresActivos.begin(); it != radaresActivos.end(); ) {
        it->radio += 50.0 * deltaTiempoConfig;
        double r = it->radio;
        it->circulo->setRect(it->x - r, it->y - r, r * 2, r * 2);

        if (it->radio >= 50.0) {
            for (auto cel : listaCelulares) {
                double dx = cel->getX() - it->x;
                double dy = cel->getY() - it->y;
                if (sqrt(dx*dx + dy*dy) <= 50.0) {
                    nube.agregarReporte(it->dispositivo, it->dueno, cel->getX(), cel->getY());
                    nube.reportarPosicionDispositivo(it->dispositivo, it->dueno, it->x, it->y);
                }
            }
            scene->removeItem(it->circulo);
            delete it->circulo;
            it = radaresActivos.erase(it);
        } else {
            ++it;
        }
    }
}

void Stage4::play()  { timer->start(deltaTiempoConfig * 1000); }
void Stage4::pause() { timer->stop(); }

void Stage4::avanzarSimulacion()
{
    for (size_t i = 0; i < listaCelulares.size(); ++i) {
        listaCelulares[i]->mover(deltaTiempoConfig, limiteX, limiteY);
        listaVistasCelulares[i]->setPos(listaCelulares[i]->getX(), listaCelulares[i]->getY());

        tiempoCelularReporte[i] += deltaTiempoConfig;
        if (tiempoCelularReporte[i] >= 4.0) {
            tiempoCelularReporte[i] = 0;
            nube.reportarPosicionCelular(listaCelulares[i]->getNombre(),
                                         listaCelulares[i]->getX(),
                                         listaCelulares[i]->getY());
            qDebug() << "Celular" << QString::fromStdString(listaCelulares[i]->getNombre())
                     << "reporta posicion:" << listaCelulares[i]->getX()
                     << "," << listaCelulares[i]->getY();
        }
    }

    for (size_t i = 0; i < listaTablets.size(); ++i) {
        listaTablets[i]->mover(deltaTiempoConfig, limiteX, limiteY);
        listaVistasTablets[i]->setPos(listaTablets[i]->getX(), listaTablets[i]->getY());
    }

    for (size_t i = 0; i < listaTags.size(); ++i) {
        listaTags[i]->mover(deltaTiempoConfig, limiteX, limiteY);
        listaVistasTags[i]->setPos(listaTags[i]->getX(), listaTags[i]->getY());
    }

    actualizarRadares();
}
