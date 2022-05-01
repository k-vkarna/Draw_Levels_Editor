#ifndef LEVELMENU_H
#define LEVELMENU_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMap>

class taskicon;

class LevelMenu : public QGraphicsView
{
    Q_OBJECT
public:
    LevelMenu(QWidget *parent = nullptr);
signals:
    void selected(int levelNumber);
public slots:
    void load();
    void updateLevels();
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    void disposeIcons();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    QGraphicsScene m_scene;
private:
    QPoint m_clickPos;
    QMap<int, taskicon*> m_icons;

    const int IconSize = 150;
    const int NColumn = 3;
};

#endif // LEVELMENU_H
