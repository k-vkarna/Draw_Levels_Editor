#include "gamewidjet.h"
#include "item.h"

GameWidjet::GameWidjet(const Level &level, QWidget *parent)
    : QGraphicsView(parent), Color(102, 51, 33), ColorError(255, 0, 0),
      m_line(Color, &m_scene)
{
    setScene(&m_scene);

    m_scene.addItem(&m_line);

    if (LEVEL_DB.levelsAmount() >= level.number)
        m_line.addPoint(Item::itemCenter(level.startPoint));

    fitInView(m_scene.sceneRect(), Qt::KeepAspectRatio);
}

void GameWidjet::on_clicked(QPointF itemCenter) {

    if (m_level.startPoint.x() == 0 && m_level.startPoint.y() == 0) {

        int x = (itemCenter.x() - 50)/100;
        int y = (itemCenter.y() - 50)/100;
        m_level.startPoint.setX(x);
        m_level.startPoint.setY(y);
        m_level.number = LEVEL_DB.levelsAmount() + new_levels;
        emit update_level_info(QString::number(m_level.height) + " " + QString::number(m_level.width) +
                               " " + QString::number(x) + "," + QString::number(y));
        emit update_level(m_level);
        m_line.addPoint(itemCenter);
        ++m_current_move;
        emit next_step();
    }
    else if(PreviewIcon::is_equal(itemCenter - m_line.lastPoint())) {

        int lenght = PreviewIcon::direction_length(itemCenter - m_line.lastPoint());
        QString direction = PreviewIcon::point2string((itemCenter - m_line.lastPoint()).toPoint() / lenght);
        levelInformation = ",{"+direction+","+QString::number(lenght / Item::Size)+"}";
        emit update_level_info(levelInformation);

        m_line.addPoint(itemCenter);
        ++m_current_move;
        emit next_step();
    }
}

void GameWidjet::on_rightClicked() {
    emit update_level(m_level);
}

void GameWidjet::load(Level level) {
    m_level = level;
    for (int i = 0; i < m_level.height; ++i) {
        for (int j = 0; j < m_level.width; ++j) {
            Item *item = new Item(this);
            item->moveBy(i*(item->pos().x()+item->boundingRect().width()),
                         j*(item->pos().y()+item->boundingRect().height()));
            item->setZValue(ItemLayer);
            m_scene.addItem(item);

            connect(item, SIGNAL(clicked(QPointF)), SLOT(on_clicked(QPointF)));
            connect(item, SIGNAL(right_click()), SLOT(on_rightClicked()));
        }
    }
    m_current_move = 0;

    QPointF point = Item::itemCenter(m_level.startPoint);
    for (auto tip : m_level.tips) {
        point += PreviewIcon::tip2point(tip)*Item::Size;
        m_line.addPoint(point);
        m_current_move++;
    }
}

void GameWidjet::load_new_level(int height, int width) {

    m_level.width = width;
    m_level.height = height;

    for (int i = 0; i < m_level.height; ++i) {
        for (int j = 0; j < m_level.width; ++j) {
            Item *item = new Item(this);
            item->moveBy(i*(item->pos().x()+item->boundingRect().width()),
                         j*(item->pos().y()+item->boundingRect().height()));
            item->setZValue(ItemLayer);
            m_scene.addItem(item);

            connect(item, SIGNAL(clicked(QPointF)), SLOT(on_clicked(QPointF)));
            connect(item, SIGNAL(right_click()), SLOT(on_rightClicked()));
        }
    }
    m_current_move = 0;
    new_levels++;
}

int GameWidjet::getLevelNumber()
{
    return m_level.number;
}

void GameWidjet::resizeEvent(QResizeEvent *) {
    fitInView(m_scene.sceneRect(), Qt::KeepAspectRatio);
}
