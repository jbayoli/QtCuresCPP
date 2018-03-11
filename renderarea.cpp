#include "renderarea.h"
#include <QPainter>
#include <math.h>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent),
    m_backgroundColor(0, 0, 255),
    m_shapeColor(255, 255, 255),
    m_shape(Astroid)
{
    onShapeChange();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(m_backgroundColor);
    painter.setPen(m_shapeColor);

    // drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    float step = m_intervalLenght / m_stepCount;
    for(float t = 0.0f; t < m_intervalLenght; t += step) {
        QPointF point = compute(t);

        QPointF pixel;
        pixel.setX(point.x() * static_cast<qreal>(m_scale) + center.x());
        pixel.setY(point.y() * static_cast<qreal>(m_scale) + center.y());

        painter.drawPoint(pixel);
    }
}

QPointF RenderArea::computeAstroid(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 2 * static_cast<float>(pow(cos_t, 3));
    float y = 2 * static_cast<float>(pow(sin_t, 3));

    return QPointF(static_cast<qreal>(x),static_cast<qreal>(y));
}

QPointF RenderArea::computeCycloid(float t)
{

}

QPointF RenderArea::computeHygens(float t)
{

}

QPointF RenderArea::computeHypo(float t)
{

}

QPointF RenderArea::compute(float t)
{
    switch (m_shape) {
    case Astroid:
        return computeAstroid(t);
        break;

    case Cycloid:
        return  computeCycloid(t);
        break;

    case HuygensCycloid:
        return  computeHygens(t);
        break;

    case HypoCycloid:
        return  computeHypo(t);
        break;
    }
    return QPointF(0, 0);
}

void RenderArea::onShapeChange()
{
    switch (m_shape) {
    case Astroid:
        m_scale = 40.0f;
        m_intervalLenght = static_cast<float>(2 * M_PI);
        m_stepCount = 256;
        break;

    case Cycloid:

        break;

    case HuygensCycloid:

        break;

    case HypoCycloid:

        break;
    }
}
