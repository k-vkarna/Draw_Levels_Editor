#ifndef LEVELEDITSCREEN_H
#define LEVELEDITSCREEN_H

#include <QWidget>
#include "leveldb.h"
#include "gamewidjet.h"
#include <QStack>

namespace Ui {
class LevelEditScreen;
}

class LevelEditScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LevelEditScreen(QWidget *parent = nullptr);
    ~LevelEditScreen();
signals:
    void save(QString levelInfo, int levelNumber);
    void back();
    void exit();
public slots:
    void load(const Level &level);
    void load_new_level(const int &width, const int &height);
    void update_level_info(const QString levelInformation);
    void updateLevel(Level level);
    bool saved_file_or_not();

private slots:
    void on_save_clicked();
    void on_exit_clicked();
    void on_back_clicked();

private:
    QStack<QWidget*> m_widgets;
    Ui::LevelEditScreen *ui;
    Level m_level;
    GameWidjet *m_game;
    QString levelData;
};

#endif // LEVELEDITSCREEN_H
