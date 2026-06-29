#include "cellularview.h"
#include "findmydialog.h"
#include "gfindmydialog.h"
#include <QPainter>
#include <QMenu>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

CellularView::CellularView(Cellular* c, ETNube* n, QGraphicsScene* sc, std::map<std::string, Equipo*>* mapa)
    : modelo(c), nube(n), scene(sc), mapaDispositivos(mapa)
{
    setPos(modelo->getX(), modelo->getY());
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF CellularView::boundingRect() const {
    return QRectF(-10, -15, 105, 30);
}

QPainterPath CellularView::shape() const {
    QPainterPath path;
    path.addRoundedRect(-10, -15, 15, 25, 5, 5);
    return path;
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
    ungrabMouse();

    QMenu menu;
    QAction* findMyAction  = menu.addAction("Find My");
    QAction* gFindMyAction = menu.addAction("GFind My");
    QAction* seleccion = menu.exec(QCursor::pos());

    if (seleccion == findMyAction) {
        FindMyDialog* dialog = new FindMyDialog(modelo->getNombre(), nube, scene, mapaDispositivos);
        dialog->show();
    } else if (seleccion == gFindMyAction) {
        GFindMyDialog* dialog = new GFindMyDialog(modelo->getNombre(), nube, scene);
        dialog->show();
    }
}
