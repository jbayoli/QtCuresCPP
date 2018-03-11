#include "renderarea.h"
#include <QPainter>
#include <math.h>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent),
    m_backgroundColor(0, 0, 255),
    m_shapeColor(255, 255, 255),
    m_shape(Astroid)
{

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

    switch (m_shape) {
    case Astroid:
        m_backgroundColor = Qt::red;
        break;

    case Cycloid:
        m_backgroundColor = Qt::green;
        break;

    case HuygensCycloid:
        m_backgroundColor = Qt::blue;
        break;

    case HypoCycloid:
        m_backgroundColor = Qt::yellow;
        break;
    }

    painter.setBrush(m_backgroundColor);
    painter.setPen(m_shapeColor);

    // drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    int stepCount = 64.0f;
    float scale = 40.0f;
    float intervalLenght = static_cast<float>(2 * M_PI);
    float step = intervalLenght / stepCount;
    for(float t = 0.0f; t < intervalLenght; t += step) {
        QPointF point = computeAstroid(t);

        QPointF pixel;
        pixel.setX(point.x() * static_cast<qreal>(scale) + center.x());
        pixel.setY(point.y() * static_cast<qreal>(scale) + center.y());

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
