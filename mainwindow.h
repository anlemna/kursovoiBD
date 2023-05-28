#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtSql>
#include <QMainWindow>
#include <QDebug>
#include <sql.h>
#include <QLayout>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget *Read = new QWidget;
    QWidget *Autors = new QWidget;
    QWidget *Books = new QWidget;
    QWidget *Extrad = new QWidget;
    QWidget *acc = new QWidget;

    QWidget *Milo = new QWidget;

    QTableView *ReadT = new QTableView;
    QTableView *AutorsT = new QTableView;
    QTableView *BooksT = new QTableView;
    QTableView *ExtradT = new QTableView;
    QTableView *MiloT = new QTableView;

    QPushButton *yes = new QPushButton;
    QPushButton *no = new QPushButton;
    QPushButton *r_addButton = new QPushButton;
    QPushButton *a_addButton = new QPushButton;
    QPushButton *b_addButton = new QPushButton;
    QPushButton *e_addButton = new QPushButton;

    QPushButton *r_delButton = new QPushButton;
    QPushButton *a_delButton = new QPushButton;
    QPushButton *b_delButton = new QPushButton;
    QPushButton *e_delButton = new QPushButton;
    QPushButton *m_delButton = new QPushButton;



private slots:
    void on_addButton_clicked();
    void on_delButton_clicked();
    void on_TableVieww_clicked(const QModelIndex &index);
    void on_comboBox_currentIndexChanged(int index);

    void yes_clicked();
    void no_clicked();
    void r_sort_acc_clicked();
    void a_sort_acc_clicked();
    void b_sort_acc_clicked();
    void e_sort_acc_clicked();
    //void m_sort_acc_clicked();

    void r_srch_clicked();
    void a_srch_clicked();
    void b_srch_clicked();
    void e_srch_clicked();
    //void m_srch_clicked();

    void  r_update_clicked();
    void  a_update_clicked();
    void  b_update_clicked();
    void  e_update_clicked();
    //void  m_update_clicked();


    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *qry;
    QSqlTableModel *model;
    QSqlTableModel *temp;
    QSqlTableModel *read_model;
    QSqlTableModel *autors_model;
    QSqlTableModel *books_model;
    QSqlTableModel *extrad_model;
    QSqlTableModel *milo_model;
    QComboBox *comboBox;

    QComboBox *read_sort_box = new QComboBox;
    QLineEdit *read_LE = new QLineEdit;

    QComboBox *autors_sort_box = new QComboBox;
    QLineEdit *autors_LE = new QLineEdit;

    QComboBox *books_sort_box = new QComboBox;
    QLineEdit *books_LE = new QLineEdit;

    QComboBox *extrad_sort_box = new QComboBox;
    QLineEdit *extrad_LE = new QLineEdit;

    QComboBox *milo_sort_box = new QComboBox;
    QLineEdit *milo_LE = new QLineEdit;

    QString column_value;

    bool c_del;

    int idx;
    int row;

    void resultAnalys(QString numStr);
    void Sort(int idx);

    void add_toCB();
    void dataChanged();
};
#endif // MAINWINDOW_H
