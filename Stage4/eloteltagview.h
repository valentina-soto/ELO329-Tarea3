#ifndef ELOTELTAGVIEW_H
#define ELOTELTAGVIEW_H

#include <QGraphicsItem>
#include "eloteltag.h"

class EloTelTagView : public QGraphicsItem {
private:
    EloTelTag* modelo;

public:
    EloTelTagView(EloTelTag* tag);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // ELOTELTAGVIEW_H
