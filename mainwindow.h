#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QSqlTableModel>
#include <QDial>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase * returnDatabase(){
        return &db;
    }

private slots:
    void on_pushButtonAddBook_clicked();

    void on_pushButtonAutor_clicked();

    void on_pushButtonPublisher_clicked();

    void on_pushButtonStyle_clicked();

    void on_pushButtonOrder_clicked();

    void on_pushButtonOrderList_clicked();

    void on_TabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool connectDatabase();
    void showbAll();
    QSqlRelationalTableModel * tableModelBook;
    QSqlRelationalTableModel * tableModelAutor;
    QSqlRelationalTableModel * tableModelPublisher;
    QSqlRelationalTableModel * tableModelStyle;
    QSqlRelationalTableModel * tableModelOrderBooks;
    QSqlRelationalTableModel * tableModelOrder;
};

#endif // MAINWINDOW_H
