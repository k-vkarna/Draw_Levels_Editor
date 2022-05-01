#include "screen.h"
#include "mainwindow.h"
#include "leveldb.h"
#include <QKeyEvent>
#include <QMessageBox>


Screen::Screen(QWidget *parent)
    : screenstack(parent)
{
    m_menu = new MainWindow(this);
    connect(m_menu, SIGNAL(levelSelected(int)), SLOT(on_level_selected(int)));
    connect(m_menu, SIGNAL(create()), SLOT(create()));
    connect(m_menu, SIGNAL(exit()), this, SLOT(close()));
    m_menu->hide();

    m_game = new LevelEditScreen(this);
    connect(m_game, SIGNAL(back()), SLOT(show_menu()));
    connect(m_game, SIGNAL(exit()), this, SLOT(close()));
    connect(m_game, SIGNAL(save(QString, int)), SLOT(saveFile(QString, int)));
    m_game->hide();

    m_levelsettings = new InputLevel(this);
    connect(m_levelsettings, SIGNAL(create_level(int, int)), SLOT(create_level(int, int)));
    connect(m_levelsettings, SIGNAL(back()), SLOT(pop()));
    m_levelsettings->hide();

    push(m_menu);
}

void Screen::on_level_selected(int number) {
    Level level = LEVEL_DB.level(number);
    m_game->load(level);

    push(m_game);
}

void Screen::create() {
    push(m_levelsettings);
}

void Screen::create_level(int width, int height)
{
    m_game->load_new_level(width, height);

    push(m_game);
}

void Screen::show_menu()
{
    push(m_menu);
}

void Screen::saveFile(QString levelInfo, int levelNumber)
{
    LEVEL_DB.saveLevelsToFile(levelInfo, levelNumber);
    m_menu->update_levels();
}

void Screen::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Back) {
        if (lenght() > 1)
            pop();
        else
            this->close();
    }

    event->accept();
}

void Screen::closeEvent(QCloseEvent *event)
{
    if (screenstack::m_current_widget.front() == m_game){
        if (!m_game->saved_file_or_not()){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "LevelEditor", "Вы уверены? Все несохраненные данные будут потеряны.",
                                          QMessageBox::Ok|QMessageBox::Cancel);
            if (reply == QMessageBox::Ok)
                event->accept();
            else
                event->ignore();
        }
        else
            event->accept();
    }
}
