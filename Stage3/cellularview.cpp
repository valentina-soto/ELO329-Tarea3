#include "cellularview.h"
#include <QPainter>
#include <QMenu>
#include <QCursor>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsSceneMouseEvent>

CellularView::CellularView(Cellular* c, ETNube* n) : modelo(c), nube(n) {
    setPos(modelo->getX(), modelo->getY());
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF CellularView::boundingRect() const {
    return QRectF(-10, -15, 105, 30);
}

void CellularView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(50, 130, 255));
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundedRect(-10, -15, 15, 25, 5, 5);

    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);
    QString nombre = QString::fromStdString(modelo->getNombre());
    painter->drawText(QRectF(15, -15, 80, 30), Qt::AlignLeft | Qt::AlignVCenter, nombre);
}

void CellularView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event);

    QMenu menu;
    QAction* findMyAction = menu.addAction("Find My");
    QAction* seleccion = menu.exec(QCursor::pos());

    if (seleccion == findMyAction) {
        QDialog* dialog = new QDialog();
        dialog->setWindowTitle(QString("Find My - %1").arg(QString::fromStdString(modelo->getNombre())));
        dialog->resize(400, 250);

        QVBoxLayout* layout = new QVBoxLayout(dialog);

        auto reportes = nube->getReportesPorDueno(modelo->getNombre());
        if (reportes.empty()) {
            layout->addWidget(new QLabel("No hay reportes disponibles aún."));
        } else {
            for (const auto& r : reportes) {
                QString texto = QString("Dispositivo: %1  |  Posición celular: (%2, %3)")
                    .arg(QString::fromStdString(r.nombreDispositivo))
                    .arg(r.celularX, 0, 'f', 1)
                    .arg(r.celularY, 0, 'f', 1);
                layout->addWidget(new QLabel(texto));
            }
        }

        dialog->exec();
    }
}
