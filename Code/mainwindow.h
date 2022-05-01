#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui { class MainWindow; }

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update_levels();

private:
signals:
    void levelSelected(int number);
    void exit();
    void create();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
