#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
//    centralWidget()->layout()->removeWidget(ui->graphicsView);
    painter = new Painter(centralWidget(), *ui->stateLabel);
    centralWidget()->layout()->addWidget(painter);
    QObject::connect(ui->bDrawRectangle, (&QPushButton::clicked), this, ([=]() {painter->setState(State::DrawRectangle);} ));
    QObject::connect(ui->bDrawTriangle, (&QPushButton::clicked), this, ([=]() {painter->setState(State::DrawTriangle);} ));
    QObject::connect(ui->bDrawEllipse, (&QPushButton::clicked), this, ([=]() {painter->setState(State::DrawEllipse);} ));
    QObject::connect(ui->bDrawLine, (&QPushButton::clicked), this, ([=]() {painter->setState(State::DrawLine);} ));
    QObject::connect(ui->bMoveFigures, (&QPushButton::clicked), this, ([=]()
    {
        if (painter->getState() != State::MoveFigure)
            painter->setState(State::MoveFigure);
        else
            painter->setState(State::Idle);
    }));

}

MainWindow::~MainWindow()
{
    delete ui;
}
