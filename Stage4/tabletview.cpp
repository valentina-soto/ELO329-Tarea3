#include "tabletview.h"
#include "findmydialog.h"
#include "gfindmydialog.h"
#include <QPainter>
#include <QMenu>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

TabletView::TabletView(Tablet* t, const std::string& dueno, ETNube* n,
                       QGraphicsScene* sc, std::map<std::string, Equipo*>* mapa)
    : modelo(t), dueno(dueno), nube(n), scene(sc), mapaDispositivos(mapa)
{
    setPos(modelo->getX(), modelo->getY());
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF TabletView::boundingRect() const {
    return QRectF(-50, -20, 100, 45);
}

QPainterPath TabletView::shape() const {
    QPainterPath path;
    path.addRoundedRect(-15, -20, 30, 20, 5, 5);
    return path;
}

void TabletView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(144,238,144));
    painter->setPen(QPen(QColor(60,179,113), 1));
    painter->drawRoundedRect(-15, -20, 30, 20, 5, 5);

    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);
    painter->drawText(QRectF(-50, 2, 100, 20), Qt::AlignCenter,
                      QString::fromStdString(dueno));
}

void TabletView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event);
    ungrabMouse();

    QMenu menu;
    QAction* findMyAction  = menu.addAction("Find My");
    QAction* gFindMyAction = menu.addAction("GFind My");
    QAction* seleccion = menu.exec(QCursor::pos());

    if (seleccion == findMyAction) {
        FindMyDialog* dialog = new FindMyDialog(dueno, nube, scene, mapaDispositivos);
        dialog->show();
    } else if (seleccion == gFindMyAction) {
        GFindMyDialog* dialog = new GFindMyDialog(dueno, nube, scene);
        dialog->show();
    }
}
