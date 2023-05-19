#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QString>
#include "examinationdao.h"
#include "docdao.h"
#include "patientdao.h"
#include "questiondao.h"
#include "freportdao.h"
#include "report2dao.h"
#include "report3dao.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class QSqlDatabase;
class QSqlQuery;
const QString DATABASE_FILENAME = "docstat.db";
class DatabaseManager
{
    std::unique_ptr<QSqlDatabase> mDatabase;
public:
    static void debugQuery(const QSqlQuery& query);
    static DatabaseManager& instance();
    ~DatabaseManager();
    const ExaminationDao examinationDao;
    const DocDao docDao;
    const PatientDao patDao;
    const QuestionDao questionDao;
    const FReportDao freportDao;
    const Report2Dao report2Dao;
    const Report3Dao report3Dao;

protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator=(const DatabaseManager& rhs);


};

#endif // DATABASEMANAGER_H
