#include "line.h"

#include <QDebug>

Line::Line(const QColor &color, QObject* parent)
    : QGraphicsItemGroup(), QObject(parent), m_brush(color),
    m_lastPoint(nullptr), m_length(0)
{
    setColor(color);

    this->addToGroup(&m_lines);
}

void Line::setColor(const QColor &color) {
    m_pen.setColor(color);
    m_brush.setColor(color);

    m_pen.setWidth(LineWidth);
    m_pen.setJoinStyle(Qt::RoundJoin);

    m_lines.setPen(m_pen);
}

void Line::addPoint(QPointF point) {
    QPointF radius(EllipseRadius, EllipseRadius);

    if (m_lastPoint) {
        m_path.lineTo(point);
        m_lines.setPath(m_path);

        delete m_lastPoint;
    }
    else {
       m_path.moveTo(point);
    }
    m_lastPoint = new QGraphicsEllipseItem(QRectF(-radius, radius), this);
    m_lastPoint->setBrush(m_brush);
    m_lastPoint->setPos(point);
    ++m_length;
}

QPointF Line::lastPoint() const {
    return m_lastPoint->pos();
}

bool Line::is_single_point() {
  return 2 > m_length;
}
