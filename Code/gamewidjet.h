#ifndef GAMEWIDJET_H
#define GAMEWIDJET_H

#include "line.h"
#include "leveldb.h"
#include <QGraphicsView>

class GameWidjet : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameWidjet(const Level &level, QWidget *parent = nullptr);
public slots:
    virtual void on_clicked(QPointF itemCenter);
    virtual void on_rightClicked();
    void load(Level level);
    void load_new_level(int widht, int height);
    int getLevelNumber();
private slots:
    void resizeEvent(QResizeEvent *);
signals:
    void next_step();
    void update_level_info(QString levelInformation);
    void update_level(Level level);
protected:
    const QColor Color;
    const QColor ColorError;
    const int MoveDelayMS = 700;
    const int WinDelayMS = 1500;
    QGraphicsScene m_scene;
    Line m_line;

    Level m_level;
    int m_current_move;
    int new_levels = 0;

    bool m_wrongMoveState;
    QString levelInformation;

    const int EllipseRadius = 20;
    const int LineWidth = 4;
    const int ItemLayer = 0;
};

#endif // GAMEWIDJET_H
