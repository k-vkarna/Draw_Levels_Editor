#ifndef SCREEN_H
#define SCREEN_H

#include "mainwindow.h"
#include "leveleditscreen.h"
#include "inputlevel.h"
#include "gamewidjet.h"
#include "screenstack.h"
#include "savepromt.h"


class Screen : public screenstack
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);
public slots:
    void on_level_selected(int number);
    void create();
    void create_level(int width, int height);
    void show_menu();
    void saveFile(QString levelInfo, int levelNumber);
protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    MainWindow *m_menu;
    LevelEditScreen *m_game;
    InputLevel *m_levelsettings;
    GameWidjet *m_newLevel;
};

#endif // SCREEN_H
