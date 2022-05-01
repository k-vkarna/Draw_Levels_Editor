#include "inputlevel.h"
#include "ui_inputlevel.h"
#include <QKeyEvent>

InputLevel::InputLevel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputLevel)
{
    ui->setupUi(this);

    ui->width->setInputMask("99");
    ui->height->setInputMask("99");

    //    ui->width->setValidator(new QIntValidator(0, 10, this));
    //    ui->height->setValidator(new QIntValidator(0, 10, this));

    ui->width->setText("10");
    ui->height->setText("10");

    connect(ui->cancel, SIGNAL(clicked(bool)), SIGNAL(back()));
}

InputLevel::~InputLevel()
{
    delete ui;
}

void InputLevel::on_ok_clicked()
{
    width = ui->width->text();
    height = ui->height->text();
    if (width.toInt() < 2 || height.toInt() < 2)
        QMessageBox::information(this, "Подсказка", "Минимальный размер поля: 2X2");
    else
        emit create_level(width.toInt(), height.toInt());
    ui->width->setText("10");
    ui->height->setText("10");
}
