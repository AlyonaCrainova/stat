#ifndef DOCMODEL_H
#define DOCMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <memory>
#include "databasemanager.h"
#include "doc.h"


#include "stat-core_global.h"
class DOCSTATCORESHARED_EXPORT DocModel: public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        DocNameRole = Qt::DisplayRole+2,
        DocMiddNameRole,
        DocLastNameRole,
        ExpertRole,
        ActiveRole,
        BirthDateRole,
        SpecRole,
       };
    DocModel(QObject* parent = nullptr);
    QModelIndex addDoc(const Doc& doc);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    bool isIndexValid(const QModelIndex& index) const;
    DatabaseManager& mDb;
    std::unique_ptr<std::vector<std::unique_ptr<Doc>>> mDocs;
};

#endif // DOCMODEL_H
