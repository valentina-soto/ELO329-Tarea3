#include "tabletview.h"
#include <QPainter>

TabletView::TabletView(Tablet* t) : modelo(t) {
    setPos(modelo->getX(), modelo->getY());
}

QRectF TabletView::boundingRect() const {
    return QRectF(-50, -20, 100, 65);
}

void TabletView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(144,238,144));
    painter->setPen(QPen(QColor(60,179,113), 1));
    painter->drawRoundedRect(-15, -20, 30, 20, 5, 5);

    painter->setPen(Qt::black);
    QFont font = painter->font(); font.setPointSize(10); painter->setFont(font);
    QString nombre = QString::fromStdString(modelo->getNombre());
    painter->drawText(QRectF(-50, 2, 100, 20), Qt::AlignCenter, nombre);
}
