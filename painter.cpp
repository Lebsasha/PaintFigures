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
    creatingFigureType = FigureType::None;
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
        case State::DrawingNewFigure:
        {
            std::string s = "Drawing ";
            switch (creatingFigureType)
            {
                case FigureType::Rectangle:
                    s.append("rectangle");
                    break;
                case FigureType::Ellipse:
                    s.append("ellipse");
                    break;
                case FigureType::Triangle:
                    s.append("triangle");
                    break;
                case FigureType::Line:
                    s.append("line");
                    break;
                case FigureType::None:
                    s = "Error occurred while creating figure";
                    break;
            }
            stateLabel.setText(QString(s.c_str()));
            break;
        }
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

    for (const auto &item: figures)
    {
        item->draw(painter);
    }
}

void Painter::mousePressEvent(QMouseEvent* event)
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
    if (state == State::DrawingNewFigure)
    {
        Figure* figure;
        switch (creatingFigureType)
        {
            case FigureType::None:
                figure = nullptr;
                break;
            case FigureType::Rectangle:
                figure = new Rectangle(event->pos());
                break;
            case FigureType::Ellipse:
                figure = new Ellipse(event->pos());
                break;
            case FigureType::Triangle:
                figure = new Triangle(event->pos());
                break;
            case FigureType::Line:
            {
                Figure* pFigure = currFigureUnderMousePointer(event->pos());
                if (pFigure != nullptr)
                    figure = new Line(pFigure->getCenter());
                else
                {
                    creatingFigureType = FigureType::None;
                    setState(State::Idle);
                    return;
                }
            }
                break;
        }
        figures.push_back(figure);
    }
    else if (state == State::MoveFigure)
    {
        figureMoveHandler.movingFigure = currFigureUnderMousePointer(event->pos());
        figureMoveHandler.initialPos = event->pos();
    }
}

void Painter::mouseReleaseEvent(QMouseEvent* event)
{
    std::cout<<__PRETTY_FUNCTION__ <<std::endl;
    if (state == State::DrawingNewFigure)
    {
        if (creatingFigureType == FigureType::Line)
        {
            auto figure = currFigureUnderMousePointer(event->pos());
            if (figure == nullptr)
            {
                figures.pop_back();
                repaint();
                return; ///Let's try draw line again
            }
        }
        setState(State::Idle);
        creatingFigureType = FigureType::None;
    }
}

void Painter::mouseMoveEvent(QMouseEvent* event)
{
//    std::cout<< __PRETTY_FUNCTION__ <<std::endl;
    if (event->buttons() == Qt::LeftButton)
    {
        if (state == State::DrawingNewFigure)
        {
            if (creatingFigureType != FigureType::Line)
                (*figures.rbegin())->resize(event->pos());
            else
            {
                auto figure = currFigureUnderMousePointer(event->pos());
                if (figure == nullptr)
                   (*figures.rbegin())->resize(event->pos());
                else
                   (*figures.rbegin())->resize(figure->getCenter());
            }
        }
        else if(state == State::MoveFigure && figureMoveHandler.movingFigure != nullptr)
        {
            int deltaX = event->x() - figureMoveHandler.initialPos.x();
            int deltaY = event->y() - figureMoveHandler.initialPos.y();
            QSize movingVector = {deltaX, deltaY};
            for (const auto& item: figures)
            {
                Line* line = dynamic_cast<Line*>(item);
                if (line != nullptr)
                {
                    const auto& linePoints = line->getPoints();
                    const QPoint& center = figureMoveHandler.movingFigure->getCenter();
                    if (center == linePoints.first)
                        line->movePoint(linePoints.first, movingVector);
                    else if (center == linePoints.second)
                        line->movePoint(linePoints.second, movingVector);
                }
            }
            figureMoveHandler.movingFigure->move(movingVector);
            figureMoveHandler.initialPos = event->pos();
        }

        if(state == State::DrawingNewFigure || state == State::MoveFigure)
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
            pos.y() >= boundPoints.first.y() && pos.y() <= boundPoints.second.y() &&
            dynamic_cast<Line*>(item) == nullptr)
            return item;
    }
    return nullptr;
}

Painter::~Painter()
{
    for (const auto &item : figures)
        delete item;
}

