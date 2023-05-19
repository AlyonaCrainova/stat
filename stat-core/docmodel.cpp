#include "docmodel.h"
#include <QModelIndex>
#include <memory>
#include <QVector>
#include "doc.h"
#include <QDebug>


DocModel::DocModel (QObject* parent) :
    QAbstractListModel(parent),
    mDb(DatabaseManager::instance()),
    mDocs(mDb.docDao.docs())
{

}

QModelIndex DocModel::addDoc(const Doc& doc){
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    std::unique_ptr<Doc> newDoc(std::make_unique<Doc>(doc));
    mDb.docDao.addDoc(*newDoc);
    mDocs->push_back(std::move(newDoc));
    endInsertRows();
    return index(rowIndex, 0);
}

int DocModel::rowCount(const QModelIndex& parent) const{
    Q_UNUSED(parent)
    return static_cast<int>(mDocs->size());
}

QVariant DocModel::data(const QModelIndex& index, int role)const {
    if (!isIndexValid(index)) {
        return QVariant();
    }
    const Doc & doc = *mDocs->at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        return doc.getF_name()+" "+doc.getMidd_name()+" "+doc.getLast_name();
    case Qt::UserRole:
        return doc.getId();
    case DocModel::Roles::BirthDateRole:
        return doc.getBirth_date();
    case DocModel::Roles::DocNameRole:
        return doc.getF_name();
    case DocModel::Roles::DocMiddNameRole:
        return doc.getMidd_name();
    case DocModel::Roles::DocLastNameRole:
        return doc.getLast_name();
    case DocModel::Roles::SpecRole:
        return doc.getSpecialization();
    default:
    return QVariant();
    }
}


bool DocModel::setData(const QModelIndex& index, const QVariant& value, int role){
    if (!isIndexValid(index)){
        return false;
    }
    qDebug()<<index.row();
    Doc& doc = *mDocs->at(index.row());

    if (role == Roles::DocNameRole){
        doc.setF_name(value.toString());
    }else if(role == Roles::DocMiddNameRole){
        doc.setMidd_name(value.toString());
    }else if (role==Roles::ExpertRole){
        qDebug()<<value.toBool();
        doc.setExpert(value.toBool());
    }else {
        doc.setLast_name(value.toString());
    }
    mDb.docDao.updateDoc(doc);
    emit dataChanged(index, index);
    return true;
}

bool DocModel::isIndexValid(const QModelIndex& index) const{
    if (index.row() < 0
            || index.row() >= rowCount()
            || !index.isValid()) {
        return false;
    }
    return true;
}

bool DocModel::removeRows(int row, int count, const QModelIndex& parent){
    if (row < 0|| row >= rowCount() || count < 0|| (row + count) > rowCount()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft--) {
        const Doc & doc = *mDocs->at(row + countLeft);
        mDb.docDao.removeDoc(doc.getId());
    }
    mDocs->erase(mDocs->begin() + row, mDocs->begin() + row + count);
    endRemoveRows();
    return true;
}
