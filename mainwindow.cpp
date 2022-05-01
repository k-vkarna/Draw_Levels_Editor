#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    layout()->setSpacing(0);
    layout()->setMargin(0);

    connect(ui->graphicsView, SIGNAL(selected(int)),
            this, SIGNAL(levelSelected(int)));
    connect(ui->exit, SIGNAL(clicked(bool)), SIGNAL(exit()));
    connect(ui->newLevel, SIGNAL(clicked(bool)), SIGNAL(create()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_levels()
{
    ui->graphicsView->updateLevels();
}

