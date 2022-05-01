#ifndef SCREENSTACK_H
#define SCREENSTACK_H

#include <QWidget>
#include <QGridLayout>
#include <QStack>

class screenstack : public QWidget
{
    Q_OBJECT
public:
    explicit screenstack(QWidget *parent = nullptr);
    QStack<QWidget*> m_current_widget;
public slots:
    void push(QWidget* widget);
    void pop();
    int lenght();
private:
    QStack<QWidget*> m_widgets;
    QGridLayout m_layout;
};

#endif // SCREENSTACK_H
