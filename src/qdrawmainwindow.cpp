#include "include/qdrawmainwindow.h"
#include "ui_qdrawmainwindow.h"

QDrawMainWindow::QDrawMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QDrawMainWindow)
{
    ui->setupUi(this);
}

QDrawMainWindow::~QDrawMainWindow()
{
    delete ui;
}
