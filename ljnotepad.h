#ifndef LJNOTEPAD_H
#define LJNOTEPAD_H

#include <QMainWindow>
#include "databaseconnection.h"

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

private:

    DatabaseConnection m_dbconnection;

    Ui::LJNotepad *ui;
    void on_saveNoteButton_clicked();
    void loadDatabase();
};
#endif // LJNOTEPAD_H
