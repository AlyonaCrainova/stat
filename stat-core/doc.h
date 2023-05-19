#ifndef DOC_H
#define DOC_H
#include <QString>

#include "stat-core_global.h"
class DOCSTATCORESHARED_EXPORT Doc
{
private:
    QString id;
    QString f_name;
    QString midd_name;
    QString last_name;
    QString birth_date;
    QString specialization;
    bool active;
    bool expert;

public:
    explicit Doc(QString, QString, QString, QString ,QString, QString, bool, bool);
    Doc(const Doc& doc) = default;
    Doc(Doc&& doc) = default;
    ~Doc() = default;
    Doc& operator= (Doc& other) = default;
    Doc& operator=(Doc&&other);



    QString getF_name() const;
    QString getMidd_name() const;
    QString getLast_name() const;
    QString getId() const;
    QString getBirth_date() const;
    QString getSpecialization() const;
    void setSpecialization(QString);
    bool getExpert() const;
    void setExpert(bool);
    void setBirth_date(QString);
    bool getActive() const;
    void setActive(bool);
    void setId(QString);
    void setF_name(QString );
    void setMidd_name(QString);
    void setLast_name(QString);
};

#endif // DOC_H
