#ifndef DOCDIALOG_H
#define DOCDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include "doc.h"
#include <memory>
#include "docmodel.h"
#include <QCheckBox>
#include <QMessageBox>
#include "calendardialog.h"
#include <QDate>
#include <QRegExpValidator>
#include <QRegExp>



class DocDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocDialog(QWidget *parent, std::shared_ptr<DocModel> mdm);
    ~DocDialog() override;
    void accept() override;

private:
    std::shared_ptr<DocModel> dm;
    std::unique_ptr<std::map<std::string, int>> fields;
    QLabel* title;
    QLabel* label_id;
    QLineEdit* id;
    QLabel* label_name;
    QLineEdit* f_name;
    QLabel* label_midd_name;
    QLineEdit* midd_name;
    QLabel* label_last_name;
    QLineEdit* last_name;
    QLabel* label_birth;
    QLineEdit* date;
    QPushButton* date_btn;
    QLabel* label_spec;
    QLineEdit* spec;
    QVBoxLayout* main;
    QHBoxLayout* lay1;
    QHBoxLayout* lay2;
    QHBoxLayout* lay3;
    QCheckBox* exp_cb;
    QCheckBox* doc_cb;
    QPushButton* ok;
    QPushButton* cancel;
    QGridLayout* grid;


    QLabel* doc_id_l;
    QLabel* f_name_l;
    QLabel* midd_name_l;
    QLabel* last_name_l;
    QLabel* date_l;
    QLabel* spec_l;

public slots:
    void dateEdition();
    void getDate(const QDate&);
    void f_nameValidate(const QString&);
    void last_nameValidate(const QString&);
    void midd_nameValidate(const QString&);
    void dateValidate(const QString&);
    void specValidate(const QString&);
    void idValidate(const QString&);
};

#endif // DOCDIALOG_H
