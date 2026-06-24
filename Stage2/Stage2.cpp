#include "Stage2.h"
#include "ui_Stage2.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Stage2::Stage2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inicializar la escena visual
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    limiteX = 800;
    limiteY = 600;

    // Ejecutar la lectura del archivo config.txt
    cargarConfiguracion();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage2::avanzarSimulacion);
    timer->start(deltaTiempoConfig * 1000);
}

Stage2::~Stage2()
{
    // Limpiar memoria
    delete ui;
}

void Stage2::cargarConfiguracion()
{
    // seleccionar config.txt
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Seleccionar archivo de configuración", "",
                                                    "Text Files (*.txt);;All Files (*)");

    if (fileName.isEmpty()) {
        return;
    }

    // Abrir archivo
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }

    QTextStream in(&file);

    // Leer lineas
    QString imagenFondo = in.readLine();
       QPixmap mapa(imagenFondo); // Carga la imagen
    if(!mapa.isNull()) {
        scene->addPixmap(mapa);
        scene->setSceneRect(mapa.rect());
        limiteX = mapa.width();
        limiteY = mapa.height();
    }

    deltaTiempoConfig = in.readLine().toDouble();
    int numPersonas = in.readLine().toInt();

    // Lee cada persona y el celular
    for (int i = 0; i < numPersonas; ++i) {
        QString lineaPersona = in.readLine();
        QTextStream streamPersona(&lineaPersona);
        QString nombrePersona;
        int numTags, tieneTablet;

        // nombre, cuántos tags tiene, y si tiene tablet (1) o no (0)
        streamPersona >> nombrePersona >> numTags >> tieneTablet;

        // Leer la línea del celular
        QString lineaCelular = in.readLine();
        QTextStream streamCelular(&lineaCelular);
        double celX, celY, rapidez, angulo, deltaAngulo;
        streamCelular >> celX >> celY >> rapidez >> angulo >> deltaAngulo;

        // Instanciar el Celular y guardarlo en la lista
        Cellular* nuevoCelular = new Cellular(nombrePersona.toStdString(), celX, celY, rapidez, angulo, deltaAngulo);
        listaCelulares.push_back(nuevoCelular);

        CellularView* vistaCelular = new CellularView(nuevoCelular);
        listaVistasCelulares.push_back(vistaCelular);
        scene->addItem(vistaCelular);

        // Dibujo de tags
        if (numTags > 0) {
            QString lineaTags = in.readLine();
            QTextStream streamTags(&lineaTags);
            for(int j = 0; j < numTags; ++j) {
                QString tNombre;
                double tX, tY, tRap, tAng, tDAng;
                streamTags >> tNombre >> tX >> tY >> tRap >> tAng >> tDAng;

                EloTelTag* nuevoTag = new EloTelTag(tNombre.toStdString() + nombrePersona.toStdString(), tX, tY, tRap, tAng, tDAng);
                listaTags.push_back(nuevoTag);

                EloTelTagView* vistaTag = new EloTelTagView(nuevoTag);
                listaVistasTags.push_back(vistaTag);
                scene->addItem(vistaTag);
            }
        }
        // Indicador de tablet y dibujo
            if (tieneTablet == 1) {
                QString lineaTablet = in.readLine();
                QTextStream streamTablet(&lineaTablet);
                double tabX, tabY, tabRap, tabAng, tabDAng;
                streamTablet >> tabX >> tabY >> tabRap >> tabAng >> tabDAng;

                Tablet* nuevaTab = new Tablet(nombrePersona.toStdString(), tabX, tabY, tabRap, tabAng, tabDAng);
                listaTablets.push_back(nuevaTab);

                TabletView* vistaTab = new TabletView(nuevaTab);
                listaVistasTablets.push_back(vistaTab);
                scene->addItem(vistaTab);
            }

    }
    file.close();
}

void Stage2::avanzarSimulacion() {
    // Mover Celulares
    for (size_t i = 0; i < listaCelulares.size(); ++i) {
        listaCelulares[i]->mover(deltaTiempoConfig, limiteX, limiteY);
        listaVistasCelulares[i]->setPos(listaCelulares[i]->getX(), listaCelulares[i]->getY());
    }

    // Mover Tablets
    for (size_t i = 0; i < listaTablets.size(); ++i) {
        listaTablets[i]->mover(deltaTiempoConfig, limiteX, limiteY);
        listaVistasTablets[i]->setPos(listaTablets[i]->getX(), listaTablets[i]->getY());
    }

    // Mover Tags
    for (size_t i = 0; i < listaTags.size(); ++i) {
        listaTags[i]->mover(deltaTiempoConfig, limiteX, limiteY);
        listaVistasTags[i]->setPos(listaTags[i]->getX(), listaTags[i]->getY());
    }
}