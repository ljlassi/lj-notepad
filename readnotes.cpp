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

void ReadNotes::loadNotes() {
    m_dbconnection.connectToDB();
    m_dbconnection.selectQuery("SELECT * FROM NOTES");
    ui->textBrowser->setText(m_dbconnection.m_displayable_result);
}
