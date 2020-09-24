#ifndef READNOTES_H
#define READNOTES_H

#include <QWidget>
#include "databaseconnection.h"

namespace Ui {
class ReadNotes;
}

class ReadNotes : public QWidget
{
    Q_OBJECT

public:
    explicit ReadNotes(QWidget *parent = nullptr);
    ~ReadNotes();
    void loadNotes(DatabaseConnection dbconnection);

private:

    Ui::ReadNotes *ui;
};

#endif // READNOTES_H
