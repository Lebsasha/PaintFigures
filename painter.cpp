#include "painter.h"
#include <QPainter>
#include <QMouseEvent>

Painter::Painter(QWidget *parent, QLabel& state_label) : QWidget(parent), state(State::Idle), stateLabel(state_label), figures()
{
    setMouseTracking(true);
    QPalette pal = palette();
    pal.setColor(backgroundRole(), Qt::white);
    setPalette(pal);
    setAutoFillBackground(true);
    figureMoveHandler = {nullptr, QPoint(0, 0)};
    setState(State::Idle);
}

void Painter::setState(State newState)
{
    state = newState;
    switch (newState)
    {
        case State::Idle:
            stateLabel.setText("");
            break;
        case State::DrawRectangle:
            stateLabel.setText("Drawaing rectangle");
            break;
        case State::DrawEllipse:
            stateLabel.setText("Drawing ellipse");
            break;
        case State::DrawTriangle:
            stateLabel.setText("Drawing triangle");
            break;
        case State::DrawLine:
            stateLabel.setText("Drawing line");
            break;
        case State::MoveFigure:
            stateLabel.setText("Moving figures");
            break;
    }
}

State Painter::getState()
{
    return state;
}

void Painter::paintEvent(QPaintEvent* )
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
    QPainter painter(this);

    for (const auto &item : figures)
    {
        item->draw(painter);
    }
}

void Painter::mousePressEvent(QMouseEvent* event)
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
    if (state == State::DrawRectangle)
    {
        figures.push_back(new Rectangle(event->pos()));//TODO destructor
    }
    if (state == State::MoveFigure)
    {
        figureMoveHandler.movingFigure = currFigureUnderMousePointer(event->pos());
        figureMoveHandler.initialPos = event->pos();
    }
}

void Painter::mouseReleaseEvent(QMouseEvent* event)
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
    if (state != State::Idle && state != State::MoveFigure)
    {
        setState(State::Idle);
    }
}

void Painter::mouseMoveEvent(QMouseEvent* event)
{
//    std::cout<< __PRETTY_FUNCTION__ <<std::endl;
    if (event->buttons() == Qt::LeftButton)
    {
        if (state == State::DrawRectangle)
        {
            (*figures.rbegin())->resize(event->pos());
        }
        else if(state == State::MoveFigure)
        {
            int deltaX = event->x() - figureMoveHandler.initialPos.x();
            int deltaY = event->y() - figureMoveHandler.initialPos.y();
            figureMoveHandler.movingFigure->move(QSize(deltaX, deltaY));
            figureMoveHandler.initialPos = event->pos();
        }

        if(state != State::Idle)
            repaint();
    }
}

void Painter::closeEvent(QCloseEvent* event)//TODO If closing window with unsaved figure
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
}

void Painter::resizeEvent(QResizeEvent* )
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
}

Figure* Painter::currFigureUnderMousePointer(const QPoint& pos)
{
    for (const auto &item: figures)
    {
        const std::pair<QPoint, QPoint>& boundPoints = item->boundPoints();
        if (pos.x() >= boundPoints.first.x() && pos.x() <= boundPoints.second.x() &&
            pos.y() >= boundPoints.first.y() && pos.y() <= boundPoints.second.y()
            /*dynamic_cast<Line*>(item) != nullptr*/)
            return item;
    }
    return nullptr;
}

Painter::~Painter()
{
    for (const auto &item : figures)
        delete item;
}

