#ifndef CELLULARVIEW_H
#define CELLULARVIEW_H

#include <QGraphicsItem>
#include "cellular.h"

class CellularView : public QGraphicsItem {
private:
    Cellular* modelo; // Enlace directo al modelo de datos

public:
    CellularView(Cellular* c);

    // fronteras máximas del dibujo
    QRectF boundingRect() const override;

    // Realiza el dibujo en la pantalla usando QPainter
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // CELLULARVIEW_H