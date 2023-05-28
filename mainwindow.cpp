#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cstring>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("./Kursa4DB.db");

    if(!db.open())qDebug() << "ERROR" << db.lastError().text();
    else qDebug() <<"Connect!" ;
    qry = new QSqlQuery(db);

    qry->exec("CREATE TABLE Books(КОД_КНИГИ INT(3) PRIMARY KEY, НАЗВАНИЕ TEXT, КОД_АВТОРА INT(3), ФАМИЛИЯ TEXT, ИЗДАНИЕ INT(4), FOREIGN KEY (КОД_АВТОРА) REFERENCES АВТОРЫ (КОД_АВТОРА) )");
    qry->exec("CREATE TABLE Autors(КОД_АВТОРА INT(3) PRIMARY KEY, ФАМИЛИЯ TEXT, ИНИЦИАЛЫ TEXT)");
    qry->exec("CREATE TABLE Readers(БИЛЕТ INT(4) PRIMARY KEY, ФАМИЛИЯ TEXT, ИМЯ TEXT, ТЕЛЕФОН INT(11))");
    qry->exec("CREATE TABLE Extrad(АКТ INT(6), КОД_КНИГИ INT(3), НАЗВАНИЕ TEXT, ОТДАНА DATE, ВОЗВРАТ DATE, БИЛЕТ INT(4), FOREIGN KEY (КОД_КНИГИ) REFERENCES Books (КОД_КНИГИ), FOREIGN KEY (БИЛЕТ) REFERENCES Readers (БИЛЕТ))");
    //qry->exec("SELECT Readers.card, Books.title, Readers.name, Readers.number FROM Readers, Books, Extrad WHERE Extrad.return < 'now'");


    model = new QSqlTableModel(this,db);
    read_model = new QSqlTableModel(this,db);
    autors_model = new QSqlTableModel(this,db);
    books_model = new QSqlTableModel(this,db);
    extrad_model = new QSqlTableModel(this,db);
    milo_model = new QSqlTableModel(this,db);

    connect(yes, &QPushButton::clicked,this, &MainWindow::yes_clicked);
    connect(no, &QPushButton::clicked,this, &MainWindow::no_clicked);

    connect(ReadT,&QTableView::clicked,this, &MainWindow::on_TableVieww_clicked);
    connect(AutorsT,&QTableView::clicked,this, &MainWindow::on_TableVieww_clicked);
    connect(BooksT,&QTableView::clicked,this, &MainWindow::on_TableVieww_clicked);
    connect(ExtradT,&QTableView::clicked,this, &MainWindow::on_TableVieww_clicked);



    connect(r_addButton,&QPushButton::clicked,this, &MainWindow::on_addButton_clicked);
    connect(a_addButton,&QPushButton::clicked,this, &MainWindow::on_addButton_clicked);
    connect(b_addButton,&QPushButton::clicked,this, &MainWindow::on_addButton_clicked);
    connect(e_addButton,&QPushButton::clicked,this, &MainWindow::on_addButton_clicked);
    connect(r_delButton,&QPushButton::clicked,this, &MainWindow::on_delButton_clicked);
    connect(a_delButton,&QPushButton::clicked,this, &MainWindow::on_delButton_clicked);
    connect(b_delButton,&QPushButton::clicked,this, &MainWindow::on_delButton_clicked);
    connect(e_delButton,&QPushButton::clicked,this, &MainWindow::on_delButton_clicked);

    r_addButton->setText("Добавить");
    a_addButton->setText("Добавить");
    b_addButton->setText("Добавить");
    e_addButton->setText("Добавить");
    r_delButton->setText("Избавиться");
    a_delButton->setText("Избавиться");
    b_delButton->setText("Избавиться");
    e_delButton->setText("Избавиться");

    ui->tableView->setModel(model);

    //QLabel *sort_lb = new QLabel;
    QLabel *srch_lb = new QLabel;

    //Readers Table
    Read->setObjectName("ReadersTable");

    QVBoxLayout *ReadT_Lt = new QVBoxLayout;
    QVBoxLayout *Read_sort_Lt = new QVBoxLayout;
    QHBoxLayout *r_AD_Lt = new QHBoxLayout;
    QVBoxLayout *Read_srch_Lt = new QVBoxLayout;
    QHBoxLayout *Read_Bt_Lt = new QHBoxLayout;
    QVBoxLayout *Read_Lt3 = new QVBoxLayout;
    QPushButton *r_sort_acc_but = new QPushButton;
    QPushButton *r_srch_but = new QPushButton;
    QPushButton *r_update_but = new QPushButton;
    QLabel *r_sort_lb = new QLabel;

    r_sort_lb->setText("Сортировка:");
    srch_lb->setText("Поиск по читательскому билету:");

    ReadT_Lt->addWidget(ReadT);

    r_AD_Lt->addWidget(r_addButton);
    r_AD_Lt->addWidget(r_delButton);

    read_sort_box->addItem("По чит.билету");
    read_sort_box->addItem("По фамилии");

    connect(r_srch_but,&QPushButton::clicked,this, &MainWindow::r_srch_clicked);
    connect(r_sort_acc_but,&QPushButton::clicked,this, &MainWindow::r_sort_acc_clicked);
    connect(r_update_but,&QPushButton::clicked,this, &MainWindow::r_update_clicked);

    r_sort_acc_but->setText("Сортировать");
    r_srch_but->setText("Поиск");
    r_update_but->setText("Обновить");

    Read_sort_Lt->addWidget(r_sort_lb);
    Read_sort_Lt->addWidget(read_sort_box);
    Read_sort_Lt->addWidget(r_sort_acc_but);

    Read_srch_Lt->addWidget(srch_lb);
    Read_srch_Lt->addWidget(read_LE);
    Read_srch_Lt->addWidget(r_srch_but);

    Read_Bt_Lt->addLayout(Read_sort_Lt);
    Read_Bt_Lt->addLayout(Read_srch_Lt);

    Read_Lt3->addLayout(ReadT_Lt);
    Read_Lt3->addLayout(Read_Bt_Lt);
    Read_Lt3->addLayout(r_AD_Lt);
    Read_Lt3->addWidget(r_update_but);

    Read->setLayout(Read_Lt3);
    read_model->setTable("Readers");
    read_model->select();
    ReadT->setModel(read_model);
    ReadT->setMaximumWidth(750);
    Read->setFixedSize(440,500);


    //Autors Table
    Autors->setObjectName("AutorsTable");

    QVBoxLayout *AutorsT_Lt = new QVBoxLayout;
    QVBoxLayout *Autors_sort_Lt = new QVBoxLayout;
    QHBoxLayout *a_AD_Lt = new QHBoxLayout;
    QVBoxLayout *Autors_srch_Lt = new QVBoxLayout;
    QHBoxLayout *Autors_Bt_Lt = new QHBoxLayout;
    QVBoxLayout *Autors_Lt3 = new QVBoxLayout;
    QLabel *a_srch_lb = new QLabel;
    QLabel *a_sort_lb = new QLabel;
    QPushButton *a_sort_acc_but = new QPushButton;
    QPushButton *a_srch_but = new QPushButton;
    QPushButton *a_update_but = new QPushButton;

    a_sort_lb->setText("Сортировать:");
    a_srch_lb->setText("Найти книгу по коду автора:");
    AutorsT_Lt->addWidget(AutorsT);
    a_AD_Lt->addWidget(a_addButton);
    a_AD_Lt->addWidget(a_delButton);


    autors_sort_box->addItem("По коду автора");
    autors_sort_box->addItem("По фамилии");

    connect(a_srch_but,&QPushButton::clicked,this, &MainWindow::a_srch_clicked);
    connect(a_sort_acc_but,&QPushButton::clicked,this, &MainWindow::a_sort_acc_clicked);
    connect(a_update_but,&QPushButton::clicked,this, &MainWindow::a_update_clicked);

    a_sort_acc_but->setText("Сортировать");
    a_srch_but->setText("Поиск");
    a_update_but->setText("Обновить");

    Autors_sort_Lt->addWidget(a_sort_lb);
    Autors_sort_Lt->addWidget(autors_sort_box);
    Autors_sort_Lt->addWidget(a_sort_acc_but);

    Autors_srch_Lt->addWidget(a_srch_lb);
    Autors_srch_Lt->addWidget(autors_LE);
    Autors_srch_Lt->addWidget(a_srch_but);

    Autors_Bt_Lt->addLayout(Autors_sort_Lt);
    Autors_Bt_Lt->addLayout(Autors_srch_Lt);
    Autors_Lt3->addLayout(AutorsT_Lt);
    Autors_Lt3->addLayout(Autors_Bt_Lt);
    Autors_Lt3->addLayout(a_AD_Lt);
    Autors_Lt3->addWidget(a_update_but);


    Autors->setLayout(Autors_Lt3);
    autors_model->setTable("Autors");
    autors_model->select();
    AutorsT->setModel(autors_model);
    AutorsT->setMaximumWidth(750);
    Autors->setFixedSize(340,500);



    //Books table
    Books->setObjectName("BooksTable");

    QVBoxLayout *BooksT_Lt = new QVBoxLayout;
    QVBoxLayout *Books_sort_Lt = new QVBoxLayout;
    QHBoxLayout *b_AD_Lt = new QHBoxLayout;
    QVBoxLayout *Books_srch_Lt = new QVBoxLayout;
    QHBoxLayout *Books_Bt_Lt = new QHBoxLayout;
    QVBoxLayout *Books_Lt3 = new QVBoxLayout;
    QLabel *b_srch_lb = new QLabel;
    QPushButton *b_sort_acc_but = new QPushButton;
    QPushButton *b_srch_but = new QPushButton;
    QPushButton *b_update_but = new QPushButton;
    QLabel *b_sort_lb = new QLabel;

    b_srch_lb->setText("Найти книгу по коду:");
    b_sort_lb->setText("Сортировка:");

    BooksT_Lt->addWidget(BooksT);
    b_AD_Lt->addWidget(b_addButton);
    b_AD_Lt->addWidget(b_delButton);


    books_sort_box->addItem("По коду автора");
    books_sort_box->addItem("По названию");

    connect(b_srch_but,&QPushButton::clicked,this, &MainWindow::b_srch_clicked);
    connect(b_sort_acc_but,&QPushButton::clicked,this, &MainWindow::b_sort_acc_clicked);
    connect(b_update_but,&QPushButton::clicked,this, &MainWindow::b_update_clicked);

    b_sort_acc_but->setText("Сортировать");
    b_srch_but->setText("Поиск");
    b_update_but->setText("Обновить");

    Books_sort_Lt->addWidget(b_sort_lb);
    Books_sort_Lt->addWidget(books_sort_box);
    Books_sort_Lt->addWidget(b_sort_acc_but);

    Books_srch_Lt->addWidget(b_srch_lb);
    Books_srch_Lt->addWidget(books_LE);
    Books_srch_Lt->addWidget(b_srch_but);

    Books_Bt_Lt->addLayout(Books_sort_Lt);
    Books_Bt_Lt->addLayout(Books_srch_Lt);
    Books_Lt3->addLayout(BooksT_Lt);
    Books_Lt3->addLayout(Books_Bt_Lt);
    Books_Lt3->addLayout(b_AD_Lt);
    Books_Lt3->addWidget(b_update_but);


    Books->setLayout(Books_Lt3);
    books_model->setTable("Books");
    books_model->select();
    BooksT->setModel(books_model);
    BooksT->setMaximumWidth(750);
    Books->setFixedSize(540,500);


    //Extrad Table
    Extrad->setObjectName("ExtradTable");

    QVBoxLayout *ExtradT_Lt = new QVBoxLayout;
    QVBoxLayout *Extrad_sort_Lt = new QVBoxLayout;
    QHBoxLayout *e_AD_Lt = new QHBoxLayout;
    QVBoxLayout *Extrad_srch_Lt = new QVBoxLayout;
    QHBoxLayout *Extrad_Bt_Lt = new QHBoxLayout;
    QVBoxLayout *Extrad_Lt3 = new QVBoxLayout;
    QLabel *e_srch_lb = new QLabel;
    QLabel *e_sort_lb = new QLabel;
    QPushButton *e_sort_acc_but = new QPushButton;
    QPushButton *e_srch_but = new QPushButton;
    QPushButton *e_update_but = new QPushButton;

    e_sort_lb->setText("Сортировать:");
    e_srch_lb->setText("Найти запись по чит.билету:");
    ExtradT_Lt->addWidget(ExtradT);
    e_AD_Lt->addWidget(e_addButton);
    e_AD_Lt->addWidget(e_delButton);


    extrad_sort_box->addItem("По коду выдачи");
    extrad_sort_box->addItem("По коду книги");
    extrad_sort_box->addItem("По названию книги");
    extrad_sort_box->addItem("По дате выдачи");

    connect(e_srch_but,&QPushButton::clicked,this, &MainWindow::e_srch_clicked);
    connect(e_sort_acc_but,&QPushButton::clicked,this, &MainWindow::e_sort_acc_clicked);
    connect(e_update_but,&QPushButton::clicked,this, &MainWindow::e_update_clicked);

    e_sort_acc_but->setText("Сортировать");
    e_srch_but->setText("Поиск");
    e_update_but->setText("Обновить");

    Extrad_sort_Lt->addWidget(e_sort_lb);
    Extrad_sort_Lt->addWidget(extrad_sort_box);
    Extrad_sort_Lt->addWidget(e_sort_acc_but);

    Extrad_srch_Lt->addWidget(e_srch_lb);
    Extrad_srch_Lt->addWidget(extrad_LE);
    Extrad_srch_Lt->addWidget(e_srch_but);

    Extrad_Bt_Lt->addLayout(Extrad_sort_Lt);
    Extrad_Bt_Lt->addLayout(Extrad_srch_Lt);
    Extrad_Lt3->addLayout(ExtradT_Lt);
    Extrad_Lt3->addLayout(Extrad_Bt_Lt);
    Extrad_Lt3->addLayout(e_AD_Lt);
    Extrad_Lt3->addWidget(e_update_but);


    Extrad->setLayout(Extrad_Lt3);
    extrad_model->setTable("Extrad");
    extrad_model->select();
    ExtradT->setModel(extrad_model);
    ExtradT->setMaximumWidth(750);
    Extrad->setFixedSize(640,500);


    //Подтверждение удаления
    QHBoxLayout *H_Lt = new QHBoxLayout;
    QVBoxLayout *V_Lt = new QVBoxLayout;
    QLabel *acc_Lbl = new QLabel;
    acc_Lbl->setText("Вы уверены, что хотите удалить запись?");
    yes->setText("Да");
    no->setText("Нет");
    H_Lt->addWidget(yes);
    H_Lt->addWidget(no);
    QWidget *temp_d = new QWidget;
    temp_d->setLayout(H_Lt);
    V_Lt->addWidget(acc_Lbl);
    V_Lt->addWidget(temp_d);
    acc->setLayout(V_Lt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    temp->insertRow(temp->rowCount());
}

void MainWindow::dataChanged()
{
    ui->comboBox->addItem(column_value);
}

void MainWindow::on_delButton_clicked()
{
    c_del = false;
    acc->show();
}

void MainWindow::yes_clicked()
{
    temp->removeRow(row);
    //if (c_del)ui->comboBox->removeItem(row+3);
    acc->close();
}

void MainWindow::no_clicked()
{
    acc->close();
}

void MainWindow::on_TableVieww_clicked(const QModelIndex &index)
{
    row = index.row();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 1){
        temp=read_model;
        temp->select();
        Read->setWindowTitle("ЧИТАТЕЛИ");
        Read->show();
        model->setTable("Readers");
        model->select();
    }
    if (index ==  2){
        temp=autors_model;
        temp->select();
        Autors->setWindowTitle("АВТОРЫ");
        Autors->show();
        model->setTable("Autors");
        model->select();
    }
    if (index == 3){
        temp=books_model;
        temp->select();
        Books->setWindowTitle("КНИГИ");
        Books->show();
        model->setTable("Books");
        model->select();
    }
    if (index == 4){
        temp=extrad_model;
        temp->select();
        Extrad->setWindowTitle("КНИГИ НА РУКАХ");
        Extrad->show();
        model->setTable("Extrad");
        model->select();
    }
    qDebug()<<temp->tableName();
}


void MainWindow::resultAnalys(QString arg_in){
    qry->exec("SELECT home_id, visitors_id FROM matches WHERE match_id =\'" + arg_in + "\'");
    int v_id;
    int h_id;
    if (qry->exec() && qry->next()) {
        h_id = qry->value(0).toInt();
        v_id = qry->value(1).toInt();
    }
    qry->exec(QString("SELECT team_name FROM teams WHERE team_id = '%1'").arg(QString::number(h_id)));
    QString ht_nm;
    QString vt_nm;
    if (qry->exec() && qry->next()) {
        ht_nm = qry->value(0).toString();
    }
    qry->exec(QString("SELECT team_name FROM teams WHERE team_id = '%1'").arg(QString::number(v_id)));
    if (qry->exec() && qry->next()) {
        vt_nm = qry->value(0).toString();
    }
    qry->exec("SELECT scored_hom, scored_vis FROM Matches WHERE match_id =\'" + arg_in + "\'");
    if (qry->exec() && qry->next()) {
        int score_h = qry->value(0).toInt();
        int score_v = qry->value(1).toInt();
        qDebug() << ht_nm << "-" << vt_nm;
        qDebug() << "result - " << score_h << ":" << score_v;
    } else {
        qDebug() << "Query failed or no results";
    }
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    resultAnalys(arg1);
}

void MainWindow::Sort(int idx){
    temp->setSort(idx, Qt::AscendingOrder);
    temp->select();
}


void MainWindow::r_sort_acc_clicked()
{
    Sort(read_sort_box->currentIndex());
}

void MainWindow::a_sort_acc_clicked()
{
    Sort(autors_sort_box->currentIndex());
}

void MainWindow::b_sort_acc_clicked()
{
    Sort(books_sort_box->currentIndex());
}

void MainWindow::e_sort_acc_clicked()
{
    Sort(extrad_sort_box->currentIndex());
}

void MainWindow::r_srch_clicked(){
    QString txt = read_LE->text();
    qDebug()<< txt;
    temp->setFilter(QString("БИЛЕТ = '%1'").arg(txt));
    temp->select();
}

void MainWindow::a_srch_clicked(){
    QString txt = autors_LE->text();
    qDebug()<< txt;
    temp->setFilter(QString("КОД_АВТОРА = '%1'").arg(txt));
    temp->select();
}

void MainWindow::b_srch_clicked(){
    QString txt = books_LE->text();
    qDebug()<< txt;
    temp->setFilter(QString("КОД_КНИГИ = '%1'").arg(txt));
    temp->select();
}

void MainWindow::e_srch_clicked(){
    QString txt = extrad_LE->text();
    qDebug()<< txt;
    temp->setFilter(QString("БИЛЕТ = '%1'").arg(txt));
    temp->select();
}

void MainWindow::r_update_clicked()
{
    temp->setTable("Readers");
    temp->select();
}

void MainWindow::a_update_clicked()
{
    temp->setTable("Autors");
    temp->select();
}

void MainWindow::b_update_clicked()
{
    temp->setTable("Books");
    temp->select();
}

void MainWindow::e_update_clicked()
{
    temp->setTable("Extrad");
    temp->select();
}

void MainWindow::on_pushButton_clicked()
{
    temp=milo_model;
    temp->select();
    QSqlQueryModel *model_milo = new QSqlQueryModel;
    model_milo->setQuery("SELECT Readers.БИЛЕТ, Books.НАЗВАНИЕ, Readers.ИМЯ, Readers.ТЕЛЕФОН FROM Readers, Books, Extrad WHERE Extrad.ВОЗВРАТ < '2023.05.07' AND Readers.БИЛЕТ=Extrad.БИЛЕТ AND Books.КОД_КНИГИ=Extrad.КОД_КНИГИ");
    MiloT->setModel(model_milo);
    MiloT->setFixedSize(420,200);
    MiloT->setWindowTitle("БЕССЕРДЕЧНЫЕ ДОЛЖНИКИ");
    MiloT->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QWidget::close();
}
