#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QPen>
#include <QBrush>

#include <exception>

class Line : public QGraphicsItemGroup, public QObject
{
    const int EllipseRadius = 20;
    const int LineWidth = 13;

    QPen m_pen;
    QBrush m_brush;

public:
    Line(const QColor &color, QObject *parent = nullptr);
    QPointF lastPoint() const;
    bool is_single_point();
public slots:
    void addPoint(QPointF point);
    void setColor(const QColor &color);
protected:
    QGraphicsEllipseItem *m_lastPoint;
    QGraphicsPathItem m_lines;
    QPainterPath m_path;
    int m_length;
};

#endif // LINE_H
