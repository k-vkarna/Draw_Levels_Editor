#include "leveldb.h"
#include <QMap>

LevelDB::LevelDB(QString dbFilename, QObject *parent)
    : DBfacade(dbFilename, parent)
{

}

void LevelDB::createTables() {
    if (m_db.tables().contains("levels"))
        return;
    exec("CREATE TABLE levels"
         "("
         "number INTEGER PRIMARY KEY AUTOINCREMENT, "
         "height INTEGER, width INTEGER, "
         "data TEXT NOT NULL"
         ");"
         );
}

Level LevelDB::level(int number) {
    Level level;
    exec(
                tr("SELECT data, height, width FROM levels WHERE number = ") +
                QString::number(number)
                );
    m_query->next();

    QString data = m_query->value(0).toString();
    level.height = m_query->value(1).toInt();
    level.width = m_query->value(2).toInt();
    level.number = number;

    QRegExp parseStartPoint("(\\d+),(\\d+)(.*)");
    QRegExp parseTips(",\\{(Left|Right|Up|Down|UpLeft|UpRight|DownLeft|DownRight),(\\d+)\\}");

    if (!parseStartPoint.exactMatch(data))
        throw ParseFirstPointException(data.toLatin1());

    level.startPoint = QPoint(parseStartPoint.cap(1).toInt(),
                              parseStartPoint.cap(2).toInt());

    QString tipsString = parseStartPoint.cap(3);

    int pos = 0;
    while ((pos = parseTips.indexIn(tipsString, pos)) != -1) {
        pos += parseTips.matchedLength();

        PreviewIcon tip;
        tip.direction = PreviewIcon::string2direction(parseTips.cap(1));
        tip.distance = parseTips.cap(2).toInt();

        level.tips.push_back(tip);
    }


    return level;
}

void LevelDB::loadLevelsFromFile(QString filename) {
    createTables();

    levelsFile = filename;

    QFile file(levelsFile);
    QTextStream ifst(&file);

    if (!file.open(QIODevice::ReadOnly))
        throw OpenLevelsException();

    int i = 0;
    while (ifst.atEnd() == false) {
        Level level;

        ifst >> level.height
                >> level.width
                >> level.data;

        level.number = i++;

        if (ifst.status() == QTextStream::Status::ReadPastEnd){
            file.flush();
            file.close();
            break;
        }
        insert(level);
    }
    emit updated();
}

void LevelDB::saveLevelsToFile(QString data, int levelNumber) {

    QFile saveFile(levelsFile);
    if (!saveFile.open(QFile::ReadWrite)){
        throw OpenLevelsException();
    }

    QString buff;
    QTextStream text(&saveFile);

    if (levelNumber > levelsAmount()){
        buff = text.readLine();
        QString substring = "\n" + data;
        if (buff == "")
            substring = data;
        text << substring;
        saveFile.close();
    }
    else{
        QString wholetext = "";
        levelNumber++;

        if (levelNumber == 1){
            buff = text.readLine();
            buff.replace(0,buff.length(), data);
            wholetext = wholetext + buff;
            if (levelsAmount() > 1)
                for (int i = 2; i <= levelsAmount(); i++){
                    buff = text.readLine();
                    wholetext = wholetext + "\n" + buff;
                }
        }
        if (levelNumber > 1 && levelNumber < levelsAmount()){
            int count = 1;
            for (int i = 1; i < levelNumber; i++){
                buff = text.readLine();
                wholetext = wholetext + buff + "\n";
                count++;
            }
            buff = text.readLine();
            buff.replace(0,buff.length(), data);
            wholetext = wholetext + buff;
            for (int i = count + 1; i <= levelsAmount(); i++){
                buff = text.readLine();
                wholetext = wholetext + "\n" + buff;
            }
        }
        if (levelNumber == levelsAmount() && levelsAmount() > 1){
            for (int i = 1; i < levelsAmount(); i++){
                buff = text.readLine();
                wholetext = wholetext + buff + "\n";
            }
            buff = text.readLine();
            buff.replace(0,buff.length(), data);
            wholetext = wholetext + buff;
        }

        saveFile.close();
        saveFile.remove();

        if (!saveFile.open(QFile::ReadWrite)){
            throw OpenLevelsException();
        }
        text << wholetext;
        saveFile.close();
    }
    loadLevelsFromFile(levelsFile);
}

int LevelDB::levelsAmount() {
    exec(
                tr("SELECT COUNT(*) FROM levels")
                );
    m_query->next();

    return m_query->value(0).toInt();
}

bool LevelDB::existLevel(int number) {
    exec(
                tr("SELECT data FROM levels WHERE number = ") +
                QString::number(number)
                );
    return m_query->first();
}

void LevelDB::insert(Level level) {
    bool is_exist = existLevel(level.number);
    if (is_exist) {
        exec(
                    tr("UPDATE levels SET ") +
                    "height = " + QString::number(level.height) + "," +
                    "width = " + QString::number(level.width) + "," +
                    "data = " + qs(level.data) +
                    "WHERE number = " + QString::number(level.number)
                    );
        return;
    }
    exec(tr("INSERT INTO levels(number, height, width, data) VALUES (") +
         QString::number(level.number) + "," +
         QString::number(level.height) + "," +
         QString::number(level.width) + "," + qs(level.data) + ")"
         );
}

