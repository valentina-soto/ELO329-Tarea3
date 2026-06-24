#ifndef TABLETVIEW_H
#define TABLETVIEW_H

#include <QGraphicsItem>
#include "tablet.h"

class TabletView : public QGraphicsItem {
private:
    Tablet* modelo;

public:
    TabletView(Tablet* t);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // TABLETVIEW_H
