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
    return QSize(400, 400);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 400);
}

void RenderArea::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(m_backgroundColor);
    painter.setPen(m_shapeColor);

    // drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX(static_cast<int>(prevPoint.x() * static_cast<qreal>(m_scale) + center.x()));
    prevPixel.setY(static_cast<int>(prevPoint.y() * static_cast<qreal>(m_scale) + center.y()));

    float step = m_intervalLenght / m_stepCount;
    for(float t = 0.0f; t < m_intervalLenght; t += step) {
        QPointF point = compute(t);

        QPoint pixel;
        pixel.setX(static_cast<int>(point.x() * static_cast<qreal>(m_scale) + center.x()));
        pixel.setY(static_cast<int>(point.y() * static_cast<qreal>(m_scale) + center.y()));

        painter.drawLine(pixel, prevPixel);

        prevPixel = pixel;
    }
}

QPointF RenderArea::computeAstroid(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 2.0f * static_cast<float>(pow(cos_t, 3));
    float y = 2.0f * static_cast<float>(pow(sin_t, 3));

    return QPointF(static_cast<qreal>(x),static_cast<qreal>(y));
}

QPointF RenderArea::computeCycloid(float t)
{
    return QPointF(static_cast<qreal>(1.5f * (1 - cos(t))), //x
            static_cast<qreal>(1.5f * (t - sin(t))) //y
    );
}

QPointF RenderArea::computeHygens(float t)
{
    return  QPointF(static_cast<qreal>(4 * (3 * cos(t) -cos(3 * t))), //x
                    static_cast<qreal>(4 * (3 * sin(t) - sin(3* t))) //y
    );
}

QPointF RenderArea::computeHypo(float t)
{
    return QPointF(
                static_cast<qreal>(1.5f * (2 * cos(t) + cos(2 * t))), //x
                static_cast<qreal>(1.5f * (2 * sin(t) - sin(2 * t))) //y
    );
}

QPointF RenderArea::computeLine(float t)
{
    return QPointF(static_cast<qreal>(1 - t), //x
                   static_cast<qreal>( 1 -t) //y
    );
}

QPointF RenderArea::computeCircle(float t)
{
    return QPointF(static_cast<qreal>(cos(t)), //x
                   static_cast<qreal>(sin(t)) //y
    );
}

QPointF RenderArea::computeEllipse(float t)
{
    return  QPointF (
                static_cast<qreal>(2.0f * cos(t)), //x
                static_cast<qreal>(1.1f * sin(t)) //y
    );
}

QPointF RenderArea::computeFancy(float t)
{
    float x = 11.0f * cos(t) - 6.0f * cos((11.0f * t) / 6.0f);
    float y = 11.0f * sin(t) - 6.0f * sin((11.0f *t) / 6.0f);
    return QPointF(static_cast<qreal>(x), static_cast<qreal>(y));
}

QPointF RenderArea::computerStarFish(float t)
{
    float R = 5.0f, r = 3.0f, d = 5.0f;

    float x = (R - r) * cos(t) + d * cos((t*(R-r))/r);
    float y = (R - r) * sin(t) - d * sin((t*(R-r))/r);

    return QPointF(static_cast<qreal>(x), static_cast<qreal>(y));
}

QPointF RenderArea::compute(float t)
{
    switch (m_shape) {
    case Astroid:
        return computeAstroid(t);

    case Cycloid:
        return  computeCycloid(t);

    case HuygensCycloid:
        return  computeHygens(t);

    case HypoCycloid:
        return  computeHypo(t);

    case Line:
        return computeLine(t);

    case Circle:
        return computeCircle(t);

    case Ellipse:
        return computeEllipse(t);

    case Fancy:
        return computeFancy(t);

    case Starfish:
        return  computerStarFish(t);
    }

    return QPointF(0, 0);
}

void RenderArea::onShapeChange()
{
    switch (m_shape) {
    case Astroid:
        m_scale = 90.0f;
        m_intervalLenght = static_cast<float>(2 * M_PI);
        m_stepCount = 256;
        break;

    case Cycloid:
        m_scale = 10.0f;
        m_intervalLenght = static_cast<float>(4 * M_PI);
        m_stepCount = 128;
        break;

    case HuygensCycloid:
        m_scale = 12.0f;
        m_intervalLenght = static_cast<float>(4 * M_PI);
        m_stepCount = 256;
        break;

    case HypoCycloid:
        m_scale = 40.0f;
        m_intervalLenght = static_cast<float>(2 * M_PI);
        m_stepCount = 256;
        break;

    case Line:
        m_intervalLenght = 2.0f;
        m_scale = 100.0f;
        m_stepCount = 128;
        break;

    case Circle:
        m_scale = 150.0f;
        m_intervalLenght = static_cast<float>(2 * M_PI);
        m_stepCount = 128;
        break;

    case Ellipse:
        m_scale = 75.0f;
        m_intervalLenght = static_cast<float>(2 * M_PI);
        m_stepCount = 256;
        break;

    case Fancy:
        m_scale = 10.0f;
        m_intervalLenght = static_cast<float>(12 * M_PI);
        m_stepCount = 512;
        break;

    case Starfish:
        m_scale = 25.0f;
        m_intervalLenght = static_cast<float>(6 * M_PI);
        m_stepCount = 256;
        break;
    }   
}
