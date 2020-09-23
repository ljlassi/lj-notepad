#include "ljnotepad.h"
#include "ui_ljnotepad.h"
#include <QTextStream>
#include <sqlite3.h>
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
    m_dbconnection.closeDBConnection();
    delete ui;
}

void LJNotepad::on_pushButton_clicked()
{
    QString title = ui->lineEdit->text();
    QString content = ui->textEdit->toPlainText();
    const char* title_query;
    const char* content_query;
    title_query = title.toStdString().c_str();
    content_query = content.toStdString().c_str();
    const char* sql_stmt = "INSERT INTO NOTES VALUES (?, ?)";
    m_dbconnection.saveNote(sql_stmt, title_query, content_query);
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
