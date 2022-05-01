#include "screenstack.h"

screenstack::screenstack(QWidget *parent)
    : QWidget(parent), m_layout(this)
{
    setLayout(&m_layout);
    m_layout.setMargin(0);
}

void screenstack::push(QWidget *widget) {
    if (false == m_widgets.empty()) {
        QWidget *top = m_widgets.front();
        top->hide();
    }
    m_layout.addWidget(widget);
    m_widgets.push_front(widget);
    m_current_widget.push_front(widget);
    widget->show();
}

void screenstack::pop() {
    if (m_widgets.empty())
        return;
    m_widgets.front()->hide();

    m_widgets.pop_front();
    if (false == m_widgets.empty()) {
        m_widgets.front()->show();
    }
}

int screenstack::lenght() {
    return m_widgets.length();
}
