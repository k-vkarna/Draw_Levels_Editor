#include "dbfacade.h"

DBfacade::DBfacade(QString databasename, QObject *parent) : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE", databasename);
    m_db.setDatabaseName(databasename);

    if (false == m_db.open())
        throw OpenDBException(databasename.toLatin1());

    m_query = new QSqlQuery(m_db);
}

DBfacade::~DBfacade() {
    delete m_query;
}

QString DBfacade::qs(QString str) {
    return "'" + str + "'";
}

void DBfacade::exec(QString str) throw(QString) {
    if (false == m_query->exec(str))
        throw ExecException(str.toLatin1());
}
