#include "docdialog.h"

DocDialog::DocDialog(QWidget *parent, std::shared_ptr<DocModel> mdm) :
    QDialog(parent), dm(mdm)

{
    fields = std::make_unique<std::map<std::string, int>>();
    fields->insert(std::make_pair("Код",0));
    fields->insert(std::make_pair("Имя",0));
    fields->insert(std::make_pair("Отчество",0));
    fields->insert(std::make_pair("Фамилия",0));
    fields->insert(std::make_pair("Дата рождения",0));
    fields->insert(std::make_pair("Должность",0));

    this->setGeometry(0,0,400,400);
    title = new QLabel("Добавление нового врача", this);
    title->setAlignment(Qt::AlignHCenter);
    label_id = new QLabel("Код", this);
    id = new QLineEdit(this);
    label_name = new QLabel("Имя",this);
    f_name = new QLineEdit(this);
    label_midd_name = new QLabel("Отчество",this);
    midd_name = new QLineEdit(this);
    label_last_name = new QLabel("Фамилия",this);
    last_name = new QLineEdit(this);
    label_birth = new QLabel("Дата рождения",this);
    date = new QLineEdit(this);
    date_btn = new QPushButton(this);
    QPixmap  pm ("C:\\prod\\docstat\\icons\\calendar_pix.jpg");
    QIcon icon(pm);
    date_btn->setIcon(icon);
    label_spec = new QLabel("Должность",this);
    spec = new QLineEdit(this);
    main = new QVBoxLayout(this);

    doc_id_l = new QLabel("",this);
    f_name_l = new QLabel("",this);
    midd_name_l = new QLabel("",this);
    last_name_l = new QLabel("",this);
    date_l = new QLabel("",this);
    spec_l = new QLabel("",this);
    QFont s("Times", 8, QFont::Bold);
    doc_id_l->setFont(s);
    f_name_l->setFont(s);
    midd_name_l->setFont(s);
    last_name_l->setFont(s);
    date_l->setFont(s);
    spec_l->setFont(s);

    lay3 = new QHBoxLayout();
    lay3->addWidget(date);
    lay3->addWidget(date_btn);

    grid = new QGridLayout();
    grid->addWidget(label_id,0,0);
    grid->addWidget(id,0,1);
    grid->addWidget(doc_id_l,1,1);

    grid->addWidget(label_name,2,0);
    grid->addWidget(f_name,2,1);
    grid->addWidget(f_name_l,3,1);

    grid->addWidget(label_midd_name,4,0);
    grid->addWidget(midd_name,4,1);
    grid->addWidget(midd_name_l,5,1);

    grid->addWidget(label_last_name,6,0);
    grid->addWidget(last_name,6,1);
    grid->addWidget(last_name_l,7,1);

    grid->addWidget(label_birth,8,0);
    grid->addLayout(lay3,8,1);
    grid->addWidget(date_l,9,1);

    grid->addWidget(label_spec,10,0);
    grid->addWidget(spec,10,1);
    grid->addWidget(spec_l,11,1);

    id->setGeometry(0,0,200,50);
    f_name->setGeometry(0,0,200,50);
    midd_name->setGeometry(0,0,200,50);
    last_name->setGeometry(0,0,200,50);
    date->setGeometry(0,0,200,50);
    spec->setGeometry(0,0,200,50);

    lay1 = new QHBoxLayout();
    lay2 = new QHBoxLayout();

    doc_cb = new QCheckBox("действующий врач",this);
    exp_cb = new QCheckBox("эксперт",this);
    lay1->addWidget(doc_cb);
    lay1->addWidget(exp_cb);

    ok = new QPushButton("Добавить", this);
    cancel = new QPushButton("Отмена", this);
    lay2->addWidget(cancel);
    lay2->addWidget(ok);
    main->addWidget(title);
    main->addLayout(grid);
    main->addLayout(lay1);
    main->addLayout(lay2);
    this->setWindowTitle("Добавление нового врача");

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(date_btn, SIGNAL(clicked()), this, SLOT(dateEdition()));

    connect(id, SIGNAL(textEdited(const QString&)), this, SLOT(idValidate(const QString&)));
    connect(f_name, SIGNAL(textEdited(const QString&)), this, SLOT(f_nameValidate(const QString&)));
    connect(midd_name, SIGNAL(textEdited(const QString&)), this, SLOT(midd_nameValidate(const QString&)));
    connect(last_name, SIGNAL(textEdited(const QString&)), this, SLOT(last_nameValidate(const QString&)));
    connect(date, SIGNAL(textEdited(const QString&)), this, SLOT(dateValidate(const QString&)));
    connect(spec, SIGNAL(textEdited(const QString&)), this, SLOT(specValidate(const QString&)));
}

DocDialog::~DocDialog(){
    dm.reset();
}

void DocDialog::f_nameValidate(const QString& inp){
    if(!inp.isEmpty()){
        (*fields)["Имя"] = 1;
        QRegExpValidator f_name_validator(QRegExp("[А-Яа-я]{1,20}"));
        int pos = 0;
        QString s(inp);
        switch (f_name_validator.validate(s,pos)) {
        case QValidator::Acceptable:
            f_name_l->setText("");
            break;
        default:
            f_name_l->setText("ошибка: допустимо введение только кириллицы");
            (*fields)["Имя"] = -1;
            }
        }else{
            f_name_l->setText("");
        }
}

void DocDialog::last_nameValidate(const QString& inp){
    if(!inp.isEmpty()){
        (*fields)["Фамилия"] = 1;
        QRegExpValidator last_name_validator(QRegExp("[А-Яа-я]{1,20}"));
        int pos = 0;
        QString s(inp);
        switch (last_name_validator.validate(s,pos)) {
        case QValidator::Acceptable:
            last_name_l->setText("");
            break;
        default:
            last_name_l->setText("ошибка: допустимо введение только кириллицы");
            (*fields)["Фамилия"] = -1;

            }
        }else{
            last_name_l->setText("");
        }
}
void DocDialog::midd_nameValidate(const QString& inp){
    if(!inp.isEmpty()){
        (*fields)["Отчество"] =1;
        QRegExpValidator midd_name_validator(QRegExp("[А-Яа-я]{1,20}"));
        int pos = 0;
        QString s(inp);
        switch (midd_name_validator.validate(s,pos)) {
        case QValidator::Acceptable:
            midd_name_l->setText("");
            break;
        default:
            midd_name_l->setText("ошибка: допустимо введение только кириллицы");
            (*fields)["Отчество"] = -1;
            }
        }else{
            midd_name_l->setText("");
        }
}

void DocDialog::dateValidate(const QString& inp){
    if(!inp.isEmpty()){
        (*fields)["Дата рождения"] =1;
        QRegExpValidator date_validator(QRegExp("([3][0-1]|[1-2][0-9]|[0][1-9])[.]([1][0-2]|[0][1-9])[.]([1][9][0-9]{2}|[2][0][0-9]{2})"));
        int pos = 0;
        QString s(inp);
        switch (date_validator.validate(s,pos)) {
        case QValidator::Acceptable:
            date_l->setText("");
            break;
        default:
            date_l->setText("ошибка: введите дату в формате ДД.ММ.ГГГГ");
            (*fields)["Дата рождения"] =-1;
            }
        }else{
            date_l->setText("");

        }
}
void DocDialog::specValidate(const QString&inp){
    if(!inp.isEmpty()){
        (*fields)["Должность"] =1;
        QRegExpValidator spec_validator(QRegExp("[А-Яа-я]{1,20}"));
        int pos = 0;
        QString s(inp);
        switch (spec_validator.validate(s,pos)) {
        case QValidator::Acceptable:
            spec_l->setText("");
            break;
        default:
            spec_l->setText("ошибка: допустимо введение только кириллицы");
            (*fields)["Должность"] = -1;
            }
        }else{
            spec_l->setText("");

        }
}
void DocDialog::idValidate(const QString&inp){
    if(!inp.isEmpty()){
        (*fields)["Код"] =1;
        QRegExpValidator doc_id_validator(QRegExp("[A-Za-zА-Яа-я0-9]{1,20}"));
        int pos = 0;
        QString s(inp);
        switch (doc_id_validator.validate(s,pos)) {
        case QValidator::Acceptable:
            doc_id_l->setText("");
            break;
        default:
            doc_id_l->setText("ошибка: допустимо введение только кириллицы, латиницы и цифр");
            (*fields)["Код"] =-1;
            }
        }else{
            doc_id_l->setText("");
        }
}

void DocDialog::accept(){

    std::string empty_fields;
    std::string err_fields;

    std::map<std::string, int>::const_iterator itb = fields->cbegin(), ite = fields->cend();
    while(itb!=ite){
        if(itb->second==-1) {
            err_fields+= err_fields.empty()? itb->first: ", " + itb->first;
            }
        ++itb;
    }

    itb = fields->cbegin();
    while(itb!=ite){
        if(!itb->second) {empty_fields+= empty_fields.empty()? itb->first: ", " + itb->first;}
        ++itb;
    }

    QString message;
    if(!empty_fields.empty()){
        message.append(QString::fromStdString("Не заполнены обязательные поля: " + empty_fields));
        }
    if(!err_fields.empty()){
        if(!message.isEmpty()){message.append("\n");}
        message.append(QString::fromStdString("Не корректные данные в полях: "+ err_fields));
    }

    if(err_fields.find("Дата рождения")==1){
        std::string day(date->text().toStdString(), 0, 2);
        std::string month (date->text().toStdString(), 3, 2);
        std::string year (date->text().toStdString(), 6, 4);
        QDate mdate(std::stoi(year), std::stoi(month), std::stoi(day));
        if(!mdate.isValid() || mdate >QDate::currentDate()){
            if(!message.isEmpty()){
                message.append("\n");
            }
            message.append("Введенная дата "+date->text()+" некорректна. Введите корректную дату \n\
                        в формате ДД.ММ.ГГГГ или выберите в меню календаря.");

        }
    }

    if (message.isEmpty()){
        Doc* doc = new Doc(id->text(),f_name->text(), midd_name->text(),last_name->text(),date->text(),\
                                          spec->text(),doc_cb->checkState()==Qt::Checked?1:0,\
                                          exp_cb->checkState()==Qt::Checked?1:0);
        dm->addDoc(*doc);
        delete doc;
        emit accepted();
        this->close();
    }else{
        QMessageBox* msgbx = new QMessageBox(this);
        msgbx->setText(message);
        msgbx->setWindowTitle("Ошибка");
        msgbx->show();
    }

}


void DocDialog::dateEdition(){
    CalendarDialog* cd = new CalendarDialog(this);
    cd->show();
    connect(cd, SIGNAL(sendDate(const QDate&)), this, SLOT(getDate(const QDate&)));
}

void DocDialog::getDate(const QDate& date){
    this->date->setText(date.toString("dd.MM.yyyy"));
}
