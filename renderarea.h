#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    enum ShapeType { Astroid, Cycloid, HuygensCycloid, HypoCycloid, Line };

    explicit RenderArea(QWidget *parent = nullptr);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void setBackgroundColor(QColor color) { m_backgroundColor = color; }
    QColor backgroundColor() const { return  m_backgroundColor; }
    void setShape (ShapeType shape) { m_shape = shape; onShapeChange(); }
    ShapeType shape() const { return  m_shape; }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QPointF computeAstroid(float t);
    QPointF computeCycloid(float t);
    QPointF computeHygens(float t);
    QPointF computeHypo(float t);
    QPointF computeLine(float t);
    QPointF compute(float t);
    void onShapeChange();

    QColor m_backgroundColor;
    QColor m_shapeColor;
    ShapeType m_shape;

    float m_intervalLenght;
    float m_scale;
    int m_stepCount;
};

#endif // RENDERAREA_H
