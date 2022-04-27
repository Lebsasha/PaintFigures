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

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

    const Figure* currFigureUnderMousePointer(const QPoint& pos);

public:
    std::vector<Figure*> figures;
    State state = State::Idle;



signals:

public slots:

};

#endif // PAINTER
