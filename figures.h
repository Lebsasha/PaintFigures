#ifndef FIGURES
#define FIGURES

#include <iostream>
#include <QPoint>
#include <QPainter>


class Figure
{
public:
    virtual void draw(QPainter& painter) = 0;
    virtual void resize(const QPoint& _second);
    virtual void move(const QSize& vect);
    virtual void saveToFile(std::ostream& oStr) =0;
    /// first point must be upper left and second is lower right bound points of figure
    virtual std::pair<QPoint, QPoint> boundPoints();
    virtual ~Figure() = default;
protected:
    explicit Figure(const QPoint& initial);

protected:
    QPoint first;
    QPoint second;
private:
    //points UpLeftPoint (begin), DnRightPoint (end)
};

class Rectangle: public Figure
{
public:
    explicit Rectangle(const QPoint& initial);
    void draw(QPainter& painter) override;

    void saveToFile(std::ostream& oStr) override;
};

class Ellipse: public Figure
{
public:
    explicit Ellipse(const QPoint& initial);
    void draw(QPainter& painter) override;

    void saveToFile(std::ostream& oStr) override;
};

class Triangle: public Figure
{
public:
    explicit Triangle(const QPoint& initial);
    void draw(QPainter& painter) override;

    void saveToFile(std::ostream& oStr) override;
};
//
//class Line: public Figure
//{
//public:
//    Line(/*Points*/);
//    void draw() override;
//};
enum class State{Idle, DrawingNewFigure, MoveFigure};
enum class FigureType{None, Rectangle, Ellipse, Triangle, Line};
#endif // FIGURES
