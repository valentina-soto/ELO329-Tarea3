#include "cellularview.h"
#include <QPainter>

CellularView::CellularView(Cellular* c) : modelo(c) {
    // Posicionamos este ítem visual en las coordenadas del modelo
    setPos(modelo->getX(), modelo->getY());
}

QRectF CellularView::boundingRect() const {
    // area donde se va a dibujar
   return QRectF(-10, -15, 105, 30);
}

void CellularView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Dibujo celular
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(50, 130, 255));
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundedRect(-10, -15, 15, 25, 5, 5);

    // Dibujo nombre
    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);
    QString nombre = QString::fromStdString(modelo->getNombre());
    painter->drawText(QRectF(15, -15, 80, 30), Qt::AlignLeft | Qt::AlignVCenter, nombre);
}