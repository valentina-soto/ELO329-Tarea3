#ifndef CELLULARVIEW_H
#define CELLULARVIEW_H

#include <QGraphicsItem>
#include "cellular.h"
#include "etnube.h"

class CellularView : public QGraphicsItem {
private:
    Cellular* modelo;
    ETNube* nube;

public:
    CellularView(Cellular* c, ETNube* n);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // CELLULARVIEW_H
