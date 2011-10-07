#ifndef QDRAWMAINWINDOW_H
#define QDRAWMAINWINDOW_H

#include <QMainWindow>
#include "glcanvas.h"
namespace Ui {
    class QDrawMainWindow;
}

class QDrawMainWindow : public QMainWindow
{
    Q_OBJECT
private:


public:
    explicit QDrawMainWindow(QWidget *parent = 0);
    ~QDrawMainWindow();

private:
    Ui::QDrawMainWindow *ui;
};

#endif // QDRAWMAINWINDOW_H
