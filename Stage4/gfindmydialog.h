#ifndef GFINDMYDIALOG_H
#define GFINDMYDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <string>
#include <map>
#include "etnube.h"

class GFindMyDialog : public QDialog {
    Q_OBJECT

public:
    GFindMyDialog(const std::string& dueno, ETNube* nube,
                  QGraphicsScene* mainScene, QWidget* parent = nullptr);

private slots:
    void actualizar();

private:
    std::string dueno;
    ETNube* nube;
    QGraphicsScene* gscene;

    struct ItemDispositivo {
        QGraphicsItem* forma;
        QGraphicsTextItem* etiqueta;
    };
    std::map<std::string, ItemDispositivo> items;
};

#endif // GFINDMYDIALOG_H
