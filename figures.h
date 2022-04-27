#ifndef FIGURES
#define FIGURES

#include <iostream>
#include <QPoint>
#include <QPainter>


class Figure
{
public:
    virtual void draw(QPainter& painter) = 0;
    virtual void resize(const QPoint& point) =0;
    virtual void move(/**/) =0;
    virtual void saveToFile(std::ostream& oStr) =0;
    /// first point must be upper left and second is lower right bound points of figure
    virtual std::pair<QPoint, QPoint> boundPoints() = 0;
    virtual ~Figure() = default;
protected:
    Figure() = default;
private:
    //points UpLeftPoint (begin), DnRightPoint (end)
};

class Rectangle: public Figure
{
    QPoint first;
    QPoint second;
public:
    explicit Rectangle(const QPoint& initial);
    void draw(QPainter& painter) override;

    void resize(const QPoint& second) override;
    void move() override;
    void saveToFile(std::ostream& oStr) override;

    std::pair<QPoint, QPoint> boundPoints() override;
};

//class Ellipse: public Figure
//{
//public:
//    Ellipse(/*Points*/);
//    void draw() override;
//    void saveToFile(std::ostream& oStr) override;
//};
//
//class Triangle: public Figure
//{
//public:
//    Triangle(/*Points*/);
//    void draw() override;
//    void saveToFile(std::ostream& oStr) override;
//};
//
//class Line: public Figure
//{
//public:
//    Line(/*Points*/);
//    void draw() override;
//};
enum class State{Idle, DrawRectangle, DrawEllipse, DrawTriangle, DrawLine, MoveFigure};
#endif // FIGURES
