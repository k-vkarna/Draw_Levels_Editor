#ifndef DBFACADE_H
#define DBFACADE_H

#include <QObject>
#include <QtSql/QtSql>
#include <exception>

class DBfacade : public QObject
{
    Q_OBJECT
public:
    explicit DBfacade(QString databasename,
                      QObject *parent = nullptr);
    ~DBfacade();
signals:
    void updated();
protected:
    void exec(QString) throw(QString);
    QString qs(QString);

    QSqlDatabase m_db;
    QSqlQuery *m_query;
};

class OpenDBException: public std::exception {
public:
    OpenDBException(const char* dbName) : m_dbname(dbName) {}
private:
    virtual const char* what() const throw() {
        return m_dbname;
    }
    const char* m_dbname;
};

class ExecException: public std::exception {
public:
    ExecException(const char* request) : m_request(request) {}
private:
    virtual const char* what() const throw() {
        return m_request;
    }
    const char* m_request;
};

#endif // DBFACADE_H
