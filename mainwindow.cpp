#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
//    centralWidget()->layout()->removeWidget(ui->graphicsView);
    painter = new Painter(centralWidget());
    centralWidget()->layout()->addWidget(painter);
    QObject::connect(ui->bDrawRectangle, (&QPushButton::clicked), this, ([=]() {this->painter->state = State::DrawRectangle;}));
    QObject::connect(ui->bDrawTriangle, (&QPushButton::clicked), this, ([=]() {this->painter->state = State::DrawTriangle;}));
    QObject::connect(ui->bDrawEllipse, (&QPushButton::clicked), this, ([=]() {this->painter->state = State::DrawEllipse;}));
    QObject::connect(ui->bDrawLine, (&QPushButton::clicked), this, ([=]() {this->painter->state = State::DrawLine;}));
    QObject::connect(ui->bMoveFigures, (&QPushButton::clicked), this, ([=]()
    {
        if (painter->state != State::MoveFigure)
            painter->state = State::MoveFigure;
        else
            painter->state = State::Idle;
    }));

}

MainWindow::~MainWindow()
{
    delete ui;
}
