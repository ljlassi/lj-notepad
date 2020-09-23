#ifndef LJNOTEPAD_H
#define LJNOTEPAD_H

#include <QMainWindow>
#include "databaseconnection.h"
#include "readnotes.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LJNotepad; }
QT_END_NAMESPACE

class LJNotepad : public QMainWindow
{
    Q_OBJECT

public:
    LJNotepad(QWidget *parent = nullptr);
    ~LJNotepad();

private slots:
    void on_saveNoteButton_pressed();
    void on_actionRead_Notes_triggered();

private:
    ReadNotes *m_readnotes;
    DatabaseConnection m_dbconnection;

    Ui::LJNotepad *ui;
    void loadDatabase();
};
#endif // LJNOTEPAD_H
