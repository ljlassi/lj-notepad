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
}

/**
 * @brief LJNotepad::on_pushButton_clicked
 * Called when you click the save note button.
 */
void LJNotepad::on_saveNoteButton_clicked()
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
    LJNotepad::on_saveNoteButton_clicked();
}

void LJNotepad::on_actionRead_Notes_triggered()
{
    std::cout << "Clicked menu." << std::endl;
    m_readnotes->show();
    m_readnotes->loadNotes();
}
