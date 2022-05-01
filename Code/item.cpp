#include "item.h"
#include <QPainter>
#include <QDebug>

Item::Item(QObject *parent) : QObject(parent), QGraphicsItem()
{

}

QRectF Item::boundingRect() const
{
    return QRectF(0, 0, Size, Size);
}

QPointF Item::itemCenter(QPoint itemPos) {
    return itemPos*Size + QPoint(Size/2, Size/2);
}

void Item::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *,
                 QWidget *) {
    int height = boundingRect().height(),
            width = boundingRect().width();
    painter->drawLine(0, height/2, width, height/2);
    painter->drawLine(width/2, 0, width/2, height);
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() & Qt::RightButton){
        emit right_click();
    }
    else {
        int height = boundingRect().height(),
                width = boundingRect().width();
        emit clicked(pos() + QPointF(height/2, width/2));
        QGraphicsItem::mousePressEvent(event);
    }
}
