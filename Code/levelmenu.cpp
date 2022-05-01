#include "levelmenu.h"
#include "leveldb.h"
#include "taskicon.h"
#include <QVBoxLayout>
#include <QScrollBar>
#include <QResizeEvent>
#include <QGraphicsProxyWidget>

LevelMenu::LevelMenu(QWidget *parent)
    : QGraphicsView(parent), m_scene(this)
{
    setInteractive(false);
    setDragMode(QGraphicsView::DragMode::ScrollHandDrag);

    setViewportMargins(0, 0, 0, 0);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    load();
}

void LevelMenu::load() {
    setScene(&m_scene);
    int levelsAmount = LEVEL_DB.levelsAmount();

    for (int i = 0; i < levelsAmount; ++i) {
        Level level(LEVEL_DB.level(i));
        taskicon *icon = new taskicon(level);

        m_icons[i] = icon;

        m_scene.addWidget(icon);
        icon->show();
    }

    disposeIcons();
}

void LevelMenu::updateLevels()
{
    const int n = m_icons.size();
    for (int i = 0; i < n; ++i) {
        m_icons[i]->deleteLater();
    }
    load();
}

void LevelMenu::disposeIcons() {
    const int n = m_icons.size();

    const int NRow = n/NColumn + (n%NColumn?1:0);

    for (int i = 0; i < n; ++i) {
        int iRow = i/NColumn;
        int iColumn = i%NColumn;

        if (height() > width()) {
            std::swap(iRow, iColumn);
        }

        m_icons[i]->move(iRow*IconSize, iColumn*IconSize);
        m_icons[i]->resize(IconSize, IconSize);
    }

    if (height() > width()) {
        m_scene.setSceneRect(0, 0, IconSize*NColumn, IconSize*NRow);
    }
    else {
        m_scene.setSceneRect(0, 0, IconSize*NRow, IconSize*NColumn);
    }
    fitInView(0, 0, IconSize*NColumn, IconSize*NColumn, Qt::KeepAspectRatio);
}

void LevelMenu::resizeEvent(QResizeEvent *event) {
    if (event->size() != event->oldSize())
        disposeIcons();
}

void LevelMenu::mousePressEvent(QMouseEvent *event) {
    m_clickPos = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void LevelMenu::mouseReleaseEvent(QMouseEvent *event) {
    auto proxyWidget = dynamic_cast<QGraphicsProxyWidget*>(itemAt(event->pos()));
    if (proxyWidget) {
        auto taskIcon = dynamic_cast<taskicon*>(proxyWidget->widget());
        if (taskIcon) {
            if ((m_clickPos - event->pos()).manhattanLength() < 10)
                emit selected(taskIcon->level());
        }
    }

    QGraphicsView::mouseReleaseEvent(event);
}
