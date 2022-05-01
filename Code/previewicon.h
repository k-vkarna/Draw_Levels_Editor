#ifndef PREVIEWICON_H
#define PREVIEWICON_H

#include <QString>
#include <exception>
#include <QPoint>
#include <QDebug>

struct PreviewIcon
{
    enum Direction {
        Left, Right, Up, Down,
        UpLeft, UpRight, DownLeft, DownRight
    } direction;

    int distance;

    static Direction string2direction(QString string);
    static QPoint tip2point(const PreviewIcon& tip);
    static QString point2string (QPoint point);
    static QString rotate_direction(QString direction);
    static int direction_length(const QPointF& delta);
    static bool is_equal(const QPointF& delta);
};

#endif // PREVIEWICON_H
