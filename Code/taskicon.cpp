#include "taskicon.h"
#include "item.h"
#include "leveldb.h"
#include <QVBoxLayout>

taskicon::taskicon(const Level &level, QWidget *parent)
    : GameWidjet(level, parent),
      m_Level(level.number)
{
    QPointF point = Item::itemCenter(level.startPoint);
    for (auto tip : level.tips) {
        point += PreviewIcon::tip2point(tip)*Item::Size;
        m_line.addPoint(point);
    }
    setInteractive(false);
}

int taskicon::level() {
    return m_Level;
}

void taskicon::update()
{

}
