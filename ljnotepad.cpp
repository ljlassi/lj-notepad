#include "ljnotepad.h"
#include "ui_ljnotepad.h"
#include <QTextStream>
#include <sqlite3.h>
#include "databaseconnection.h"

/**
 * @brief LJNotepad::LJNotepad
 * Constructor with QT specific stuff.
 * @param parent
 */

LJNotepad::LJNotepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LJNotepad)
{
    ui->setupUi(this);
    m_readnotes = new ReadNotes();
    loadDatabase(); // Create database if it doens't exist, otherwise open the connection.
}

/**
 * @brief LJNotepad::~LJNotepad
 * Called when you close the window.
 */
LJNotepad::~LJNotepad()
{
    m_dbconnection.closeDBConnection();
    delete ui;
    delete m_readnotes;
}

/**
 * @brief LJNotepad::loadDatabase
 * Create database if it doens't exist, otherwise open the connection. Create the necessary table(s).
 */
void LJNotepad::loadDatabase() {
    std::string sql;
    sql = "CREATE TABLE IF NOT EXISTS NOTES ("  \
        "TITLE           TEXT    NOT NULL," \
          "CONTENT TEXT NOT NULL);";
    m_dbconnection.connectToDB();
    m_dbconnection.runSQL(sql);
}

/**
 * @brief LJNotepad::on_pushButton_pressed
 * Called when you press the save note button, just calls the method called when you click the same button.
 */

void LJNotepad::on_saveNoteButton_pressed()
{
    QString title = this->ui->lineEdit->text();
    QByteArray ba = title.toLocal8Bit();
    const char* title_query = ba.data();
    QString content = this->ui->textEdit->toPlainText();
    QByteArray ba2 = content.toLocal8Bit();
    const char* content_query = ba2.data();
    const char* sql_stmt = "INSERT INTO NOTES VALUES (?, ?)";
    m_dbconnection.saveNote(sql_stmt, title_query, content_query);
}

void LJNotepad::on_actionRead_Notes_triggered()
{
    m_readnotes->show();
    m_readnotes->loadNotes(m_dbconnection);
}
