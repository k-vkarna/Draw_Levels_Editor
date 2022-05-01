#include "leveldb.h"
#include "screen.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);
    try {
        LEVEL_DB.loadLevelsFromFile("levels.db");
        a.setStyleSheet(
                    "QLabel { background: rgba(0, 0, 0, 0); }"

                    "QPushButton { "
                    "background-color: rgba(255, 153, 102, 200); "
                    "border-style: outset;"
                    "border-width: 2px;"
                    "border-radius: 10px;"
                    "border-color: beige;"
                    "font: bold 14px;"
                    "padding: 6px;"
                    "font-size:14pt;"
                    "}"
                    "QPushButton:hover {"
                    "background-color: rgba(255, 102, 0, 200);"
                    "}"
                    "QPushButton:pressed {"
                    "background-color: rgba(255, 0, 0, 200);"
                    "}"
                    "QPushButton:disabled {"
                    "background-color: rgba(204, 153, 102, 200);"
                    "}"

                    "QMessageBox { "
                    "background: rgb(208, 246, 185); "
                    "}"

                    "Screen { "
                    "background: rgb(208, 246, 185); "
                    "}"

                    "Screen > MainWindow > LevelMenu { "
                    "background-color: rgba(169, 170, 171, 220); "
                    "}"
                    "Screen > LevelEditScreen > GameWidjet { "
                    "background-color: rgba(169, 170, 171, 220); "
                    "}"

                    "taskicon { "
                    "background-color: rgba(139, 137, 112, 50); "
                    "border-style: outset;"
                    "border-width: 3px;"
                    "border-radius: 20px;"
                    "border-color: rgba(0, 0, 0, 150);"
                    "}"
                    );
        Screen w;
        w.show();
        return a.exec();
    }
    catch (QString err) {
        qDebug() << err;
    }
}
