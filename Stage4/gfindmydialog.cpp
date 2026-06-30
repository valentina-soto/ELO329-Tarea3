#include "gfindmydialog.h"
#include <QVBoxLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

GFindMyDialog::GFindMyDialog(const std::string& dueno, ETNube* nube,
                             QGraphicsScene* mainScene, QWidget* parent)
    : QDialog(parent), dueno(dueno), nube(nube)
{
    setWindowTitle(QString("GFind My - %1").arg(QString::fromStdString(dueno)));
    resize(800, 600);
    setAttribute(Qt::WA_DeleteOnClose);

    gscene = new QGraphicsScene(this);

    // Copy background from main scene
    for (auto* item : mainScene->items()) {
        auto* pitem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        if (pitem && pitem->zValue() == -1) {
            auto* fondo = gscene->addPixmap(pitem->pixmap());
            fondo->setZValue(-1);
            gscene->setSceneRect(pitem->pixmap().rect());
            break;
        }
    }

    auto* gview = new QGraphicsView(gscene);
    gview->setFocusPolicy(Qt::NoFocus);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(gview);

    actualizar();

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GFindMyDialog::actualizar);
    timer->start(1000);
}

void GFindMyDialog::actualizar()
{
    // Celular del dueño (su nombre coincide con el del dueño)
    if (nube->tienePosicionCelular(dueno)) {
        auto pos = nube->getPosicionCelular(dueno);
        double x = pos.first;
        double y = pos.second;
        QString qnombre = QString::fromStdString(dueno);

        if (items.count(dueno) == 0) {
            ItemDispositivo id;
            auto* rect = gscene->addRect(-10, -7, 20, 14,
                                          QPen(Qt::darkBlue, 1),
                                          QBrush(QColor(50, 130, 255)));
            rect->setPos(x, y);
            rect->setZValue(3);
            id.forma = rect;

            auto* texto = gscene->addText(qnombre);
            texto->setPos(x + 10, y - 10);
            texto->setDefaultTextColor(Qt::black);
            texto->setZValue(4);
            id.etiqueta = texto;
            items[dueno] = id;
        } else {
            items[dueno].forma->setPos(x, y);
            items[dueno].etiqueta->setPos(x + 10, y - 10);
        }
    }

    auto posiciones = nube->getPosicionesDispositivosPorDueno(dueno);

    for (const auto& [nombre, pos] : posiciones) {
        double x = pos.first;
        double y = pos.second;
        QString qnombre = QString::fromStdString(nombre);

        if (items.count(nombre) == 0) {
            ItemDispositivo id;
            bool esTablet = (nombre.rfind("Tablet(", 0) == 0);

            if (esTablet) {
                auto* rect = gscene->addRect(-10, -7, 20, 14,
                                              QPen(QColor(60, 179, 113), 1),
                                              QBrush(QColor(144, 238, 144)));
                rect->setPos(x, y);
                rect->setZValue(3);
                id.forma = rect;
            } else {
                auto* elipse = gscene->addEllipse(-7, -7, 14, 14,
                                                   QPen(Qt::darkRed, 1),
                                                   QBrush(QColor(220, 50, 50)));
                elipse->setPos(x, y);
                elipse->setZValue(3);
                id.forma = elipse;
            }

            auto* texto = gscene->addText(qnombre);
            texto->setPos(x + 10, y - 10);
            texto->setDefaultTextColor(Qt::black);
            texto->setZValue(4);
            id.etiqueta = texto;
            items[nombre] = id;
        } else {
            items[nombre].forma->setPos(x, y);
            items[nombre].etiqueta->setPos(x + 10, y - 10);
        }
    }
}
