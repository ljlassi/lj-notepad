#include "ljnotepad.h"
#include "ui_ljnotepad.h"
#include <QTextStream>
#include "databaseconnection.h"

LJNotepad::LJNotepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LJNotepad)
{
    ui->setupUi(this);
    loadDatabase();
}

LJNotepad::~LJNotepad()
{
    delete ui;
}

void LJNotepad::on_findButton_clicked()
{
    QString searchString = ui->lineEdit->text();
    ui->textEdit->find(searchString, QTextDocument::FindWholeWords);
}

void LJNotepad::loadDatabase() {
    std::string sql;
    sql = "CREATE TABLE IF NOT EXISTS NOTES ("  \
        "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
        "TITLE           TEXT    NOT NULL," \
          "CONTENT TEXT NOT NULL);";

    DatabaseConnection dbconnection;
    dbconnection.connectToDB();
    dbconnection.runSQL(sql);
}
