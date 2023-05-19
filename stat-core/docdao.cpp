#include "docdao.h"
#include "databasemanager.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <memory>
#include <QDebug>


DocDao::DocDao(QSqlDatabase& database): mDatabase(database)
{

}

void DocDao::init() const{

    if (!mDatabase.tables().contains("doc")) {
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE `doc` (\
                    `id` TEXT PRIMARY KEY,\
                    `f_name` TEXT NOT NULL,\
                    `last_name` TEXT NOT NULL,\
                    `midd_name`	TEXT NOT NULL,\
                    `birth_date` TEXT NOT NULL,\
                    `active` INTEGER NOT NULL,\
                    `expert` INTEGER NOT NULL,\
                    `specialization` TEXT NOT NULL);");
    }

}

void DocDao::addDoc(Doc& doc) const {
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO doc (id, f_name, midd_name, last_name, birth_date, active, expert, specialization ) \
    VALUES (:id,:f_name, :midd_name, :last_name, :birth_date, :active, :expert, :specialization);");
    query.bindValue(":id", doc.getId());
    query.bindValue(":f_name", doc.getF_name());
    query.bindValue(":midd_name", doc.getMidd_name());
    query.bindValue(":last_name", doc.getLast_name());
    query.bindValue(":birth_date", doc.getBirth_date());
    query.bindValue(":active", doc.getActive());
    query.bindValue(":expert", doc.getExpert());
    query.bindValue(":specialization", doc.getSpecialization());
    if(!query.exec()){
        qDebug()<<"problems in DocDao::addDoc(Doc& doc)";
    }

}

void DocDao::updateDoc(Doc& doc) const {
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE doc SET f_name = (:f_name), midd_name = (:midd_name), last_name = (:last_name),\
                  birth_date = (:birth_date), active = (:active), expert = (:expert), specialization = (:specialization)\
                  WHERE id = (:id);");
    query.bindValue(":f_name", doc.getF_name());
    query.bindValue(":midd_name", doc.getMidd_name());
    query.bindValue(":last_name", doc.getLast_name());
    query.bindValue(":id", doc.getId());
    query.bindValue(":birth_date", doc.getBirth_date());
    query.bindValue(":active", doc.getActive());
    query.bindValue(":expert", doc.getExpert());
    query.bindValue(":specialization", doc.getSpecialization());
    query.exec();

}

void DocDao::removeDoc(QString doc_id) const{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM doc WHERE id = (:id)");
    query.bindValue(":id", doc_id);

}

std::unique_ptr<std::vector<std::unique_ptr<Doc>>> DocDao::docs() const{
    QSqlQuery query("SELECT * FROM doc WHERE active = 1 and expert = 0", mDatabase);
    query.exec();
    std::unique_ptr<std::vector<std::unique_ptr<Doc>>> list(new std::vector<std::unique_ptr<Doc>>);
    while(query.next()) {
        auto doc (std::make_unique<Doc>(query.value("id").toString(),query.value("f_name").toString(), query.value("midd_name").toString(),\
                                          query.value("last_name").toString(),query.value("birth_date").toString(),\
                                          query.value("specialization").toString(), query.value("active").toBool(), query.value("expert").toBool()\
                                          ));
        list->push_back(std::move(doc));
    }
    return list;
}
std::unique_ptr<std::vector<std::unique_ptr<Doc>>> DocDao::exps() const{
    QSqlQuery query("SELECT * FROM doc WHERE expert = 1", mDatabase);
    query.exec();
    std::unique_ptr<std::vector<std::unique_ptr<Doc>>> list(new std::vector<std::unique_ptr<Doc>>);
    while(query.next()) {
        auto doc (std::make_unique<Doc>(query.value("id").toString(),query.value("f_name").toString(), query.value("midd_name").toString(),\
                                          query.value("last_name").toString(),query.value("birth_date").toString(),\
                                          query.value("specialization").toString(), query.value("active").toBool(), query.value("expert").toBool()\
                                          ));
        list->push_back(std::move(doc));
    }
    return list;
}
