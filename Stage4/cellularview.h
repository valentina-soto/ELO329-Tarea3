#ifndef CELLULARVIEW_H
#define CELLULARVIEW_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "cellular.h"
#include "etnube.h"
#include "equipo.h"

class CellularView : public QGraphicsItem {
private:
    Cellular* modelo;
    ETNube* nube;
    QGraphicsScene* scene;
    std::map<std::string, Equipo*>* mapaDispositivos;

public:
    CellularView(Cellular* c, ETNube* n, QGraphicsScene* sc, std::map<std::string, Equipo*>* mapa);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // CELLULARVIEW_H
