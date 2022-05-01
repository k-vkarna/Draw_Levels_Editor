#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

class Item : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Item(QObject *parent = nullptr);
    QRectF boundingRect() const;
    static QPointF itemCenter(QPoint itemPos);

    static const int Size = 100;
signals:
    void clicked(QPointF itemPoint);
    void right_click();
public slots:
    void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ITEM_H
