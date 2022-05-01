#ifndef TASKICON_H
#define TASKICON_H

#include <QWidget>
#include <QLabel>
#include "gamewidjet.h"

class taskicon : public GameWidjet
{
    Q_OBJECT
public:
    explicit taskicon(const Level &level, QWidget *parent = nullptr);
    int level();
    void update();
private:
    const int m_Level;
};

#endif // TASKICON_H
