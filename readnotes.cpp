#include "readnotes.h"
#include "ui_readnotes.h"

ReadNotes::ReadNotes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadNotes)
{
    ui->setupUi(this);
}

ReadNotes::~ReadNotes()
{
    delete ui;
}

void ReadNotes::loadNotes(DatabaseConnection dbconnection) {
    dbconnection.selectQuery("SELECT * FROM NOTES");
    ui->textBrowser->setText(dbconnection.m_displayable_result);
}
