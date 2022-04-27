#include "figures.h"
#include <QPainter>

Figure::Figure(const QPoint& initial): first(initial), second(initial)
{}

void Figure::resize(const QPoint& _second)
{
    second = _second;
}

void Figure::move(const QSize& vect)
{
    first.setX(first.x() + vect.width());
    first.setY(first.y() + vect.height());
    second.setX(second.x() + vect.width());
    second.setY(second.y() + vect.height());
}

std::pair<QPoint, QPoint> Figure::boundPoints()
{
    auto upLeft = QPoint(std::min(first.x(), second.x()), std::min(first.y(), second.y()));
    auto dnRight = QPoint(std::max(first.x(), second.x()), std::max(first.y(), second.y()));
    return {upLeft, dnRight};
}

QPoint Figure::getCenter() const
{
    return (first + second)/2;
}

Rectangle::Rectangle(const QPoint& initial): Figure(initial)
{}

void Rectangle::draw(QPainter& painter)
{
    int w = second.x() - first.x();
    int h = second.y() - first.y();
    painter.drawRect(first.x(), first.y(), w, h);
}

void Rectangle::saveToFile(std::ostream& oStr)
{

}

Ellipse::Ellipse(const QPoint& initial): Figure(initial)
{}

void Ellipse::draw(QPainter& painter)
{
    QPoint center = (first + second)/2;
    int rx = (second.x() - first.x())/2;
    int ry = (second.y() - first.y())/2;
    painter.drawEllipse(center, rx, ry);
}

void Ellipse::saveToFile(std::ostream& oStr)
{

}

Triangle::Triangle(const QPoint& initial) : Figure(initial)
{}

void Triangle::draw(QPainter& painter)
{
    painter.drawLine(second.x(), second.y(), first.x(), second.y());
    painter.drawLine(first.x(), second.y(), (first.x() + second.x())/2, first.y());
    painter.drawLine((first.x() + second.x())/2, first.y(), second.x(), second.y());
}

void Triangle::saveToFile(std::ostream& oStr)
{

}

Line::Line(const QPoint& initial) : Figure(initial)
{}

void Line::draw(QPainter& painter)
{
    painter.drawLine(first, second);
}

void Line::saveToFile(std::ostream& oStr)
{

}
