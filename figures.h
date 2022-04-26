#ifndef FIGURES
#define FIGURES

#include <iostream>


class Figure
{
public:
    virtual void draw();
    virtual void resize(/*Second (at mice view) point*/);
    virtual void move(/**/);
    virtual void saveToFile(std::ostream& oStr);
protected:
    Figure();
    virtual ~Figure();
private:
    //points UpLeftPoint (begin), DnRightPoint (end)
};

class Rectangle: public Figure
{
public:
    Rectangle(/*Points*/);
    virtual void draw() override;
    virtual void saveToFile(std::ostream& oStr) override;
};

class Ellipse: public Figure
{
public:
    Ellipse(/*Points*/);
    virtual void draw() override;
    virtual void saveToFile(std::ostream& oStr) override;
};

class Triangle: public Figure
{
public:
    Triangle(/*Points*/);
    virtual void draw() override;
    virtual void saveToFile(std::ostream& oStr) override;
};

#endif // FIGURES_H
