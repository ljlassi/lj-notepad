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

void LJNotepad::on_pushButton_clicked()
{
    QString searchString = ui->lineEdit->text();
    ui->textEdit->find(searchString, QTextDocument::FindWholeWords);
    std::string sql = "INSERT INTO NOTES VALUES ('THIS IS A TITLE', 'THIS IS TEXT')";
    m_dbconnection.runSQL(sql);
}

void LJNotepad::loadDatabase() {
    std::string sql;
    sql = "CREATE TABLE IF NOT EXISTS NOTES ("  \
        "TITLE           TEXT    NOT NULL," \
          "CONTENT TEXT NOT NULL);";
    m_dbconnection.connectToDB();
    m_dbconnection.runSQL(sql);
}

void LJNotepad::on_pushButton_pressed()
{
    LJNotepad::on_pushButton_clicked();
}
