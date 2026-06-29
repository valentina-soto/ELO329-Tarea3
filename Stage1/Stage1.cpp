#include "Stage1.h"
#include "ui_Stage1.h"
#include "cellularview.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <iostream>

Stage1::Stage1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inicializar la escena visual
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Ejecutar la lectura del archivo config.txt
    cargarConfiguracion();
}

Stage1::~Stage1()
{
    // Limpiar memoria
    for(auto c : listaCelulares) {
        delete c;
    }
    delete ui;
}

void Stage1::cargarConfiguracion()
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
    QString imagenFondo = in.readLine().trimmed();
    double deltaTiempo = in.readLine().toDouble();
    int numPersonas = in.readLine().toInt();

    QPixmap mapa(imagenFondo); // Carga la imagen
    if(!mapa.isNull()) {
        QGraphicsPixmapItem* fondo = scene->addPixmap(mapa);
        fondo->setZValue(-1);
        scene->setSceneRect(mapa.rect());
    }

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

        // consola
        std::cout << "Celular de " << nuevoCelular->getNombre()
                  << " -> X: " << nuevoCelular->getX()
                  << ", Y: " << nuevoCelular->getY() << std::endl;

        CellularView* vistaCelular = new CellularView(nuevoCelular);
        scene->addItem(vistaCelular);
        // Si tiene más de 0 tags, leemos y descartamos esa única línea
        if (numTags > 0) {
            in.readLine();
        }

        // Indicador de tablet
        if (tieneTablet == 1) {
            in.readLine();
        }
    }

    file.close();
}