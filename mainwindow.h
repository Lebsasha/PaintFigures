#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "painter.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    Painter* painter;
};

#endif // MAINWINDOW_H
