#ifndef TABLETVIEW_H
#define TABLETVIEW_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QGraphicsScene>
#include <map>
#include <string>
#include "tablet.h"
#include "etnube.h"
#include "equipo.h"

class TabletView : public QGraphicsItem {
private:
    Tablet* modelo;
    std::string dueno;
    ETNube* nube;
    QGraphicsScene* scene;
    std::map<std::string, Equipo*>* mapaDispositivos;

public:
    TabletView(Tablet* t, const std::string& dueno, ETNube* n,
               QGraphicsScene* sc, std::map<std::string, Equipo*>* mapa);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // TABLETVIEW_H
