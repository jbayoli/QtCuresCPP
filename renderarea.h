#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    enum ShapeType { Astroid, Cycloid, HuygensCycloid, HypoCycloid };

    explicit RenderArea(QWidget *parent = nullptr);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void setBackgroundColor(QColor color) { m_backgroundColor = color; }
    QColor backgroundColor() const { return  m_backgroundColor; }
    void setShape (ShapeType shape) { m_shape = shape; }
    ShapeType shape() const { return  m_shape; }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QPointF computeAstroid(float t);

    QColor m_backgroundColor;
    QColor m_shapeColor;
    ShapeType m_shape;
};

#endif // RENDERAREA_H
