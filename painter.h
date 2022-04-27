#ifndef PAINTER
#define PAINTER

#include "figures.h"
#include <vector>
#include <QWidget>

class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = nullptr);
    ~Painter() override;

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

    Figure* currFigureUnderMousePointer(const QPoint& pos);

public:
    State state = State::Idle;

private:
    std::vector<Figure*> figures;

    struct FigureMoveHandler
    {
        Figure* movingFigure;
        QPoint initialPos;
    };
    FigureMoveHandler figureMoveHandler;



signals:

public slots:

};

#endif // PAINTER
