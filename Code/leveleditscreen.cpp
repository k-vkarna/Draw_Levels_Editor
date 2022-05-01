#include "leveleditscreen.h"
#include "ui_leveleditscreen.h"
#include <QFile>
#include <QMessageBox>

LevelEditScreen::LevelEditScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelEditScreen), m_game(nullptr)
{
    ui->setupUi(this);
    ui->level_information->setReadOnly(true);
}

LevelEditScreen::~LevelEditScreen()
{
    delete ui;
}

void LevelEditScreen::load(const Level &level) {
    m_level = level;

    if (m_game)
        m_game->deleteLater();

    m_game = new GameWidjet(m_level, this);
    m_game->load(m_level);

    ui->gameLayout->addWidget(m_game);

    connect(m_game, SIGNAL(update_level_info(QString)), SLOT(update_level_info(QString)));
    connect(m_game, SIGNAL(update_level(Level)), SLOT(updateLevel(Level)));

    QFile file ("levels.db");
    if (!file.open(QFile::ReadOnly)){
        throw OpenLevelsException();
    }
    QTextStream text(&file);
    QString buff;
    for (int i = 0; i<=level.number; i++){
        buff = text.readLine();
    }
    levelData = buff;
    ui->level_information->setPlainText(buff);
    file.flush();
    file.close();
}


void LevelEditScreen::load_new_level(const int &width, const int &height)
{
    levelData = "";

    if (m_game)
        m_game->deleteLater();

    Level new_level;

    m_game = new GameWidjet(new_level, this);
    m_game->load_new_level(width, height);

    ui->gameLayout->addWidget(m_game);

    connect(m_game, SIGNAL(update_level_info(QString)), SLOT(update_level_info(QString)));
    connect(m_game, SIGNAL(update_level(Level)), SLOT(updateLevel(Level)));

    ui->level_information->clear();
}

void LevelEditScreen::update_level_info(const QString levelInformation)
{
    QString buff = ui->level_information->toPlainText() + levelInformation;
    ui->level_information->setPlainText(buff);
}

void LevelEditScreen::updateLevel(Level level)
{
    QString current_info = ui->level_information->toPlainText();

    if (current_info == "")
        return;

    if (current_info.contains("{")){
        current_info.remove(current_info.lastIndexOf(",{"), current_info.length() - current_info.lastIndexOf(",{"));
        ui->level_information->setPlainText(current_info);
    }

    QString size_area = QString::number(level.width) + " " + QString::number(level.height) + " ";
    current_info.replace(0,size_area.length(),"");

    Level update_level = level;

    QRegExp parseStartPoint("(\\d+),(\\d+)(.*)");
    QRegExp parseTips(",\\{(Left|Right|Up|Down|UpLeft|UpRight|DownLeft|DownRight),(\\d+)\\}");

    if (!parseStartPoint.exactMatch(current_info))
        throw ParseFirstPointException(current_info.toLatin1());

    update_level.startPoint = QPoint(parseStartPoint.cap(1).toInt(),
                                     parseStartPoint.cap(2).toInt());

    QString tipsString;
    if (parseStartPoint.cap(3) != ""){

        tipsString = parseStartPoint.cap(3);
        parseTips.indexIn(tipsString, 0);
        QString substring = PreviewIcon::rotate_direction(parseTips.cap(1));
        substring = ",{" + parseTips.cap(1) + "," + parseTips.cap(2) + "},{" + substring + "," +
                parseTips.cap(2) + "},{" + parseTips.cap(1) + "," + parseTips.cap(2);
        tipsString.replace(tipsString.indexOf(",{"), tipsString.indexOf("}"), substring);
    }
    else {
        tipsString = ",{Up,0}";
    }

    int pos = 0;
    update_level.tips.clear();

    while ((pos = parseTips.indexIn(tipsString, pos)) != -1) {
        pos += parseTips.matchedLength();

        PreviewIcon tip;
        tip.direction = PreviewIcon::string2direction(parseTips.cap(1));
        tip.distance = parseTips.cap(2).toInt();

        update_level.tips.push_back(tip);
    }

    if (m_game)
        m_game->deleteLater();

    m_game = new GameWidjet(update_level, this);
    m_game->load(update_level);

    ui->gameLayout->addWidget(m_game);

    connect(m_game, SIGNAL(update_level_info(QString)), SLOT(update_level_info(QString)));
    connect(m_game, SIGNAL(update_level(Level)), SLOT(updateLevel(Level)));

}

bool LevelEditScreen::saved_file_or_not()
{
    if (levelData == ui->level_information->toPlainText())
        return true;
    else
        return false;
}

void LevelEditScreen::on_save_clicked()
{
    levelData = ui->level_information->toPlainText();
    emit save(ui->level_information->toPlainText(), m_game->getLevelNumber());
}

void LevelEditScreen::on_back_clicked()
{
    if (!saved_file_or_not()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "LevelEditor", "Вы уверены? Все несохраненные данные будут потеряны.",
                                      QMessageBox::Ok|QMessageBox::Cancel);
        if (reply == QMessageBox::Ok)
            emit back();
    }
    else
        emit back();
}

void LevelEditScreen::on_exit_clicked()
{
    if (!saved_file_or_not()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "LevelEditor", "Вы уверены? Все несохраненные данные будут потеряны.",
                                      QMessageBox::Ok|QMessageBox::Cancel);
        if (reply == QMessageBox::Ok)
            emit exit();
    }
    else
        emit exit();
}
