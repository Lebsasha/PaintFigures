#include "painter.h"
#include <QPainter>
#include <QMouseEvent>

Painter::Painter(QWidget *parent) : QWidget(parent), figures(), state(State::Idle)
{
    setMouseTracking(true);
}

void Painter::paintEvent(QPaintEvent* event)
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
    QPainter painter(this);
    setAutoFillBackground(true);//TODO

    for (const auto &item : figures)
    {
        item->draw(painter);
    }

//    QWidget::paintEvent(event);
}

void Painter::mousePressEvent(QMouseEvent* event)
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
    if (state == State::DrawRectangle)
    {
        figures.push_back(new Rectangle(event->pos()));//TODO destructor
    }
}

void Painter::mouseReleaseEvent(QMouseEvent* event)
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
    if (state != State::Idle)
        state = State::Idle;
}

void Painter::mouseMoveEvent(QMouseEvent* event)
{
    std::cout<< __PRETTY_FUNCTION__ <<std::endl;
    if (event->buttons() == Qt::LeftButton)
    {
        if (state == State::DrawRectangle)
        {
            (*figures.rbegin())->resize(event->pos());
        }
        else if(state == State::MoveFigure)
        {

        }

        if(state != State::Idle)
            repaint();
    }
}

void Painter::closeEvent(QCloseEvent* event)//TODO If closing window with unsaved figure
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
}

void Painter::resizeEvent(QResizeEvent* event)
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
}

const Figure* Painter::currFigureUnderMousePointer(const QPoint& pos)
{
    for (const auto &item: figures)
    {
        const std::pair<QPoint, QPoint>& boundPoints = item->boundPoints();
        if (pos.x() >= boundPoints.first.x() && pos.x() <= boundPoints.second.x() &&
            pos.y() >= boundPoints.first.y() && pos.y() <= boundPoints.second.y())
            return item;
    }
    return nullptr;
}

