#include "databasemanager.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include "docdao.h"
#include "patientdao.h"
#include "examinationdao.h"
#include "questiondao.h"



void DatabaseManager::debugQuery(const QSqlQuery& query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError) {
        qDebug() << "Query OK:"  << query.lastQuery();
    } else {
       qWarning() << "Query KO:" << query.lastError().text();
       qWarning() << "Query text:" << query.lastQuery();
    }
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString& path):
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    examinationDao(*mDatabase),
    docDao(*mDatabase),
    patDao(*mDatabase),
    questionDao(*mDatabase),
    freportDao(*mDatabase),
    report2Dao(*mDatabase),
    report3Dao(*mDatabase)

{
    mDatabase->setDatabaseName(path);
    bool openStatus = mDatabase->open();
    qDebug() << "Database connection: " << (openStatus ? "OK" : "Error");
    examinationDao.init();
    docDao.init();
    patDao.init();
    questionDao.init();

}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();

}
