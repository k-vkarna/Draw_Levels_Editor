#ifndef INPUTLEVEL_H
#define INPUTLEVEL_H

#include <QWidget>
#include <QIntValidator>
#include <QMessageBox>

namespace Ui {
class InputLevel;
}

class InputLevel : public QWidget
{
    Q_OBJECT

public:
    explicit InputLevel(QWidget *parent = nullptr);
    ~InputLevel();
signals:
    void back();
    void create_level(int width, int height);

private slots:
    void on_ok_clicked();

private:
    Ui::InputLevel *ui;
    QString width, height;
};

#endif // INPUTLEVEL_H
