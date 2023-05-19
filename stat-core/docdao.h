#ifndef DOCDAO_H
#define DOCDAO_H
#include "doc.h"
#include <QVector>
#include <memory>

class QSqlDatabase;
class Doc;
class DocDao
{
private:
    QSqlDatabase& mDatabase;
public:
    DocDao(QSqlDatabase& database);
    void init() const;
    void addDoc(Doc& doc)const;
    void updateDoc(Doc &doc) const;
    void removeDoc(QString doc_id) const;
    std::unique_ptr<std::vector<std::unique_ptr<Doc>>> docs() const;
    std::unique_ptr<std::vector<std::unique_ptr<Doc>>> exps() const;

};

#endif // DOCDAO_H
