#ifndef LJNOTEPAD_H
#define LJNOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LJNotepad; }
QT_END_NAMESPACE

class LJNotepad : public QMainWindow
{
    Q_OBJECT

public:
    LJNotepad(QWidget *parent = nullptr);
    ~LJNotepad();

private:
    Ui::LJNotepad *ui;
    void on_findButton_clicked();
    void loadDatabase();
};
#endif // LJNOTEPAD_H
