#include "doc.h"

Doc::Doc(QString mid,QString mdoc_f_name, QString mdoc_midd_name, QString mdoc_last_name,\
         QString mbirth_date, QString mspecialization, bool mactive, bool mexpert):\
    id(mid), f_name(mdoc_f_name), midd_name(mdoc_midd_name), last_name(mdoc_last_name), \
    birth_date(mbirth_date), specialization(mspecialization), active(mactive),expert(mexpert)
{

}


Doc& Doc::operator=(Doc&&other){
    this->id = std::move(other.id);
    this->f_name = std::move(other.f_name);
    this->midd_name = std::move(other.midd_name);
    this->last_name = std::move(other.last_name);
    this->birth_date = std::move(other.birth_date);
    this->specialization = std::move(other.specialization);
    this->active = other.active;
    this->expert = other.expert;
    return *this;

}


QString Doc::getF_name()const{
    return this->f_name;
}
QString Doc::getMidd_name()const{
    return this->midd_name;
}
QString Doc::getLast_name()const{
    return this->last_name;
}
QString Doc::getId() const{
    return this->id;
}
void Doc::setId(QString doc_id){
    this->id = doc_id;
}

void Doc::setF_name(QString doc_f_name){
    this->f_name = doc_f_name;
}
void Doc::setMidd_name(QString doc_midd_name){
    this->midd_name = doc_midd_name;
}
void Doc::setLast_name(QString doc_last_name){
    this->last_name = doc_last_name;
}

bool Doc::getActive() const{
    return this->active;
}
void Doc::setActive(bool active){
    this->active = active;
}
QString Doc::getBirth_date() const{
    return  this->birth_date;
}
void Doc::setBirth_date(QString birth_date){
    this->birth_date = birth_date;
}

bool Doc::getExpert() const{
    return this->expert;
}

void Doc::setExpert(bool b){
    this->expert = b;

}
QString Doc::getSpecialization() const{
    return this->specialization;
}
void Doc::setSpecialization(QString specialization){
    this->specialization = specialization;
}
