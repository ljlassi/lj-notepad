#include "ljnotepad.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LJNotepad w;
    w.show();
    return a.exec();
}
