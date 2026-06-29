#ifndef FINDMYDIALOG_H
#define FINDMYDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QList>
#include <string>
#include <map>
#include <set>
#include "etnube.h"
#include "equipo.h"

class FindMyDialog : public QDialog {
    Q_OBJECT

public:
    FindMyDialog(const std::string& dueno, ETNube* nube,
                 QGraphicsScene* scene,
                 std::map<std::string, Equipo*>* dispositivos,
                 QWidget* parent = nullptr);
    ~FindMyDialog();

private slots:
    void actualizar();

private:
    void toggleTraza(const std::string& nombre);

    std::string dueno;
    ETNube* nube;
    QGraphicsScene* scene;
    std::map<std::string, Equipo*>* dispositivos;
    QVBoxLayout* layout;
    QTimer* timer;

    std::set<std::string> trazasActivas;
    std::map<std::string, QList<QGraphicsLineItem*>> lineasTraza;
    std::map<std::string, std::pair<double,double>> ultimaPosicion;
};

#endif // FINDMYDIALOG_H
