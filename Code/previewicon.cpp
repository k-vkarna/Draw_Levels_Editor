#include "previewicon.h"
#include "item.h"

PreviewIcon::Direction PreviewIcon::string2direction(QString direction)
{
    std::map<std::string, PreviewIcon::Direction> string2direction ={
        {"Left", PreviewIcon::Direction::Left},
        {"Right", PreviewIcon::Direction::Right},
        {"Up", PreviewIcon::Direction::Up},
        {"Down", PreviewIcon::Direction::Down},
        {"UpLeft", PreviewIcon::Direction::UpLeft},
        {"UpRight", PreviewIcon::Direction::UpRight},
        {"DownLeft", PreviewIcon::Direction::DownLeft},
        {"DownRight", PreviewIcon::Direction::DownRight}
    };
    return string2direction.at(direction.toStdString());
}

QPoint PreviewIcon::tip2point(const PreviewIcon& tip)
{
    std::map<Direction, QPoint> direction2vector = {
        {PreviewIcon::Direction::Left, QPoint(-1, 0)},
        {PreviewIcon::Direction::Right, QPoint(1, 0)},
        {PreviewIcon::Direction::Up, QPoint(0, -1)},
        {PreviewIcon::Direction::Down, QPoint(0, 1)},
        {PreviewIcon::Direction::UpLeft, QPoint(-1, -1)},
        {PreviewIcon::Direction::UpRight, QPoint(1, -1)},
        {PreviewIcon::Direction::DownLeft, QPoint(-1, 1)},
        {PreviewIcon::Direction::DownRight, QPoint(1, 1)}
    };
    return direction2vector.at(tip.direction)*tip.distance;
}

QString PreviewIcon::point2string(QPoint point)
{
    if(point == QPoint(-1, 0)){
        return "Left";
    }
    if(point == QPoint(1, 0)){
        return "Right";
    }
    if(point == QPoint(0, -1)){
        return "Up";
    }
    if(point == QPoint(0, 1)){
        return "Down";
    }
    if(point == QPoint(-1, -1)){
        return "UpLeft";
    }
    if(point == QPoint(1, -1)){
        return "UpRight";
    }
    if(point == QPoint(-1, 1)){
        return "DownLeft";
    }
    if(point == QPoint(1, 1)){
        return "DownRight";
    }
    return "";
}

QString PreviewIcon::rotate_direction(QString direction)
{
    if (direction == "Left")
        return "Right";
    if (direction == "Right")
        return "Left";
    if (direction == "Up")
        return "Down";
    if (direction == "Down")
        return "Up";
    if (direction == "UpLeft")
        return "DownRight";
    if (direction == "UpRight")
        return "DownLeft";
    if (direction == "DownLeft")
        return "UpRight";
    if (direction == "DownRight")
        return "UpLeft";
    return "";
}

int PreviewIcon::direction_length(const QPointF &delta)
{
    if(delta.toPoint().x() != 0)
        return  abs(delta.toPoint().x());
    if(delta.toPoint().y() != 0)
        return abs(delta.toPoint().y());
    return 0;
}

bool PreviewIcon::is_equal(const QPointF &delta) {

    if (delta.toPoint().x() == 0 && delta.toPoint().y() == 0)
        return false;
    if ((delta.toPoint().x() * delta.toPoint().y()) != 0)
        if (abs(delta.toPoint().x()) != abs(delta.toPoint().y()))
            return false;
        else
            return  true;
    else
        return true;
}

