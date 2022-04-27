#include "figures.h"
#include <QPainter>

Rectangle::Rectangle(const QPoint& initial): first(initial), second(initial)
{}

void Rectangle::draw(QPainter& painter)
{
    int w = second.x() - first.x();
    int h = second.y() - first.y();
    painter.drawRect(first.x(), first.y(), w, h);
}

void Rectangle::resize(const QPoint& _second)
{
    second = _second;
}

void Rectangle::move(const QSize& vect)
{
    first.setX(first.x() + vect.width());
    first.setY(first.y() + vect.height());
    second.setX(second.x() + vect.width());
    second.setY(second.y() + vect.height());
}

void Rectangle::saveToFile(std::ostream& oStr)
{

}

std::pair<QPoint, QPoint> Rectangle::boundPoints()
{
    auto upLeft = QPoint(std::min(first.x(), second.x()), std::min(first.y(), second.y()));
    auto dnRight = QPoint(std::max(first.x(), second.x()), std::max(first.y(), second.y()));
    return {upLeft, dnRight};
}
