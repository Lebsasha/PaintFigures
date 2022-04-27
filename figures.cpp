#include "figures.h"
#include <QPainter>
#include <cmath>

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

void Rectangle::move()
{

}

void Rectangle::saveToFile(std::ostream& oStr)
{

}

std::pair<QPoint, QPoint> Rectangle::boundPoints()
{

    auto upLeft = QPoint(std::min(first.x(), second.x()), std::min(first.y(), second.y()));
    auto dnRight = QPoint(std::max(first.x(), second.x()), std::max(first.y(), second.y()));
    return {upLeft, dnRight};
//    if (first.x() < second.x())
//        if (first.y() < second.y())
//            return {first, second};
//        else
//        {
//            auto upLeft = QPoint(first.x(), second.y());
//            auto dnRight = QPoint(second.x(), first.y());
//            return {upLeft, dnRight};
//        }
//    else
//        if (first.y())
}
