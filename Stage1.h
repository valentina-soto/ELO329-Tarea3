#ifndef STAGE1_H
#define STAGE1_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include "cellular.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Stage1 : public QMainWindow
{
    Q_OBJECT

public:
    Stage1(QWidget *parent = nullptr);
    ~Stage1();

private:
    Ui::MainWindow *ui;

    // interfaz gráfica
    QGraphicsScene *scene;
    QGraphicsView *view;

    // Lista para almacenar los celulares en memoria
    std::vector<Cellular*> listaCelulares;

    void cargarConfiguracion();
};

#endif // STAGE1_H
