#include "eloteltagview.h"
#include <QPainter>

EloTelTagView::EloTelTagView(EloTelTag* tag) : modelo(tag) {
    setPos(modelo->getX(), modelo->getY());
}

QRectF EloTelTagView::boundingRect() const {
    return QRectF(-8, -12, 90, 24);
}

void EloTelTagView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(139,0,0));
    painter->setPen(QColor(139,0,0));
    painter->drawEllipse(QPointF(0, 0), 8, 8);

    painter->setPen(Qt::black);
    QFont font = painter->font(); font.setPointSize(8); painter->setFont(font);
    QString nombre = QString::fromStdString(modelo->getNombre());
    painter->drawText(QRectF(10, -10, 70, 20), Qt::AlignLeft | Qt::AlignVCenter, nombre);
}