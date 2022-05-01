#ifndef LEVELDB_H
#define LEVELDB_H

#include "dbfacade.h"
#include "singleton.h"

#include "previewicon.h"

#include <QObject>
#include <QList>

struct Level {
    int number;
    int height, width;
    QString data;
    QVector<PreviewIcon> tips;
    QPoint startPoint;
};

class LevelDB : public DBfacade
{
    Q_OBJECT
public:
    explicit LevelDB(QString dbFIlename = "levelstatus.sqlite",
                     QObject *parent = nullptr);
    Level level(int number);
    void loadLevelsFromFile(QString filename);
    void saveLevelsToFile(QString data, int levelNumber);
private:
    void createTables();
    bool existLevel(int number);
    QString levelsFile;
public slots:
    void insert(Level level);
    int levelsAmount();
};

class OpenLevelsException: public std::exception {
    virtual const char* what() const throw() {
        return "can't open levels file";
    }
};

class ParseFirstPointException: public std::exception {
public:
    ParseFirstPointException(const char* data) : m_data(data) {}
private:
    virtual const char* what() const throw() {
        return m_data;
    }
    const char* m_data;
};

#define LEVEL_DB Singleton<LevelDB>::instance()

#endif // LEVELDB_H
