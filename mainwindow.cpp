#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   if(! connectDatabase())
       qApp->quit();
   showbAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showbAll(){
//Books
    tableModelBook = new QSqlRelationalTableModel(nullptr, db);
    tableModelBook->setTable("book");

    tableModelBook->setHeaderData(0, Qt::Horizontal, "id");
    tableModelBook->setHeaderData(1, Qt::Horizontal, "style");
    tableModelBook->setHeaderData(2, Qt::Horizontal, "author");
    tableModelBook->setHeaderData(3, Qt::Horizontal, "publisher");
    tableModelBook->setHeaderData(4, Qt::Horizontal, "name");
    tableModelBook->setHeaderData(5, Qt::Horizontal, "price");
    tableModelBook->setRelation(1, QSqlRelation("style", "id", "name"));
    tableModelBook->setRelation(2, QSqlRelation("author", "id", "name"));
    tableModelBook->setRelation(3, QSqlRelation("publisher", "id", "name"));
    tableModelBook->setEditStrategy(QSqlTableModel::OnRowChange);
    tableModelBook->select();

    ui->tableViewBook->setModel(tableModelBook);
    ui->tableViewBook->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewBook));
    ui->tableViewBook->setSortingEnabled(true);
//Author
tableModelAutor = new QSqlRelationalTableModel(nullptr, db);
tableModelAutor->setTable("author");
tableModelAutor->setEditStrategy(QSqlTableModel::OnRowChange);
tableModelAutor->setHeaderData(0, Qt::Horizontal, "id");
tableModelAutor->setHeaderData(1, Qt::Horizontal, "name");
tableModelAutor->select();
ui->tableViewAuthor->setModel(tableModelAutor);
ui->tableViewAuthor->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewAuthor));
ui->tableViewAuthor->setSortingEnabled(true);
//Publisher
tableModelPublisher = new QSqlRelationalTableModel(nullptr, db);
tableModelPublisher->setTable("publisher");
tableModelPublisher->setEditStrategy(QSqlTableModel::OnRowChange);
tableModelPublisher->setHeaderData(0, Qt::Horizontal, "id");
tableModelPublisher->setHeaderData(1, Qt::Horizontal, "name");
tableModelPublisher->select();
ui->tableViewPublisher->setModel(tableModelPublisher);
ui->tableViewPublisher->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewPublisher));
ui->tableViewPublisher->setSortingEnabled(true);
//Style
tableModelStyle = new QSqlRelationalTableModel(nullptr, db);
tableModelStyle->setTable("style");
tableModelStyle->setEditStrategy(QSqlTableModel::OnRowChange);
tableModelStyle->setHeaderData(0, Qt::Horizontal, "id");
tableModelStyle->setHeaderData(1, Qt::Horizontal, "name");
tableModelStyle->select();
ui->tableViewStyle->setModel(tableModelStyle);
ui->tableViewStyle->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewStyle));
ui->tableViewStyle->setSortingEnabled(true);
//Order
tableModelOrder = new QSqlRelationalTableModel(nullptr, db);
tableModelOrder->setTable("order1");
tableModelOrder->setEditStrategy(QSqlTableModel::OnRowChange);
tableModelOrder->setHeaderData(0, Qt::Horizontal, "id");
tableModelOrder->setHeaderData(1, Qt::Horizontal, "Client Name");
tableModelOrder->setHeaderData(2, Qt::Horizontal, "Date");
tableModelOrder->setHeaderData(3, Qt::Horizontal, "orderListId");
tableModelOrder->setRelation(3, QSqlRelation("order_list", "id", "id"));

tableModelOrder->select();
ui->tableViewOrder->setModel(tableModelOrder);
ui->tableViewOrder->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewOrder));
ui->tableViewOrder->setSortingEnabled(true);

//OrderBooks
tableModelOrderBooks = new QSqlRelationalTableModel(nullptr, db);
tableModelOrderBooks->setTable("order_list");
tableModelOrderBooks->setRelation(1, QSqlRelation("book", "id", "name"));
tableModelOrderBooks->setEditStrategy(QSqlTableModel::OnRowChange);
tableModelOrderBooks->setHeaderData(0, Qt::Horizontal, "id");
tableModelOrderBooks->setHeaderData(1, Qt::Horizontal, "book id");
tableModelOrderBooks->setHeaderData(2, Qt::Horizontal, "count");
tableModelOrderBooks->select();
ui->tableViewOredrBooks->setModel(tableModelOrderBooks);
ui->tableViewOredrBooks->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewOredrBooks));
ui->tableViewOredrBooks->setSortingEnabled(true);


}

bool MainWindow::connectDatabase(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("booksmarket");
    db.setUserName("root");
    db.setPassword("123456");
    if (db.open()){
        QMessageBox::information(this, "OK", "Database is connected");
        return true;}
    else{
        QMessageBox::critical(this, "Error!", "Database is not conected!");
        return false;
    }
}

void MainWindow::on_pushButtonAddBook_clicked()
{
    tableModelBook->insertRow(0);
}

void MainWindow::on_pushButtonAutor_clicked()
{
    tableModelAutor->insertRow(0);
}

void MainWindow::on_pushButtonPublisher_clicked()
{
    tableModelPublisher->insertRow(0);
}

void MainWindow::on_pushButtonStyle_clicked()
{
    tableModelStyle->insertRow(0);
}


void MainWindow::on_pushButtonOrder_clicked()
{
    tableModelOrder->insertRow(0);
}

void MainWindow::on_pushButtonOrderList_clicked()
{
    tableModelOrderBooks->insertRow(0);
}


void MainWindow::on_TabWidget_currentChanged(int index)
{
    ui->tableViewBook->update();
    ui->tableViewAuthor->update();
    ui->tableViewOrder->update();
    ui->tableViewOredrBooks->update();
    ui->tableViewPublisher->update();
    ui->tableViewStyle->update();
    tableModelOrderBooks->select();
    tableModelBook->select();
    tableModelAutor->select();
    tableModelBook->select();
    tableModelOrder->select();
    tableModelPublisher->select();
    tableModelStyle->select();
}
