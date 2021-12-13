#include "sinview.hpp"
#include "ui_sinview.h"

SinView::SinView(QWidget *parent) :
    QChartView(parent),
    ui(new Ui::SinView)
{
    ui->setupUi(this);

    chart->addSeries(series);
    chart->setTitle("Sinusiod");

    axisX->setLabelFormat("%i");
    axisX->setTitleText("x");
    axisX->setRange(0, 200);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY->setLabelFormat("%i");
    axisY->setTitleText("y");
    axisY->setRange(0, 16);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    series->setColor(Qt::blue);
    series->setOpacity(0.5);
    chart->legend()->hide();
    this->setRenderHint(QPainter::Antialiasing);
    this->setRubberBand(QChartView::RectangleRubberBand);
    this->setBackgroundBrush(Qt::white);
    this->setChart(chart);

    setDragMode(QGraphicsView::NoDrag);
    this->setMouseTracking(true);
}


void SinView::setXInterval(float value)
{
    float min = axisX->min() > 0 ? axisX->min() : -(axisX->min());
    int tick = ((axisX->max()+min) / value)+1;
    axisX->setTickCount(tick);
}

void SinView::setYInterval(float value)
{
    float min = axisY->min() > 0 ? axisY->min() : -(axisY->min());
    int tick = ((axisY->max()+min) / value)+1;
    axisY->setTickCount(tick);
}

void SinView::setDefaultScaling()
{
    axisX->setRange(0, 200);
    axisY->setRange(0, 16);
}

void SinView::addData(float x, float y)
{
    series->append(x, y);
}

void SinView::popFront()
{
    series->remove(0);

}

void SinView::clearData()
{
    series->clear();
}


void SinView::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SinView::wheelEvent(QWheelEvent *event)
{
    qreal factor = event->angleDelta().y() > 0? 0.5: 2.0;
    chart->zoom(factor);
    event->accept();
    QChartView::wheelEvent(event);
}

void SinView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton)
    {
        QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
        m_lastMousePos = event->pos();
        event->accept();
    }

    QChartView::mousePressEvent(event);
}

void SinView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::MiddleButton)
    {
        auto dPos = event->pos() - m_lastMousePos;
        chart->scroll(-dPos.x(), dPos.y());

        m_lastMousePos = event->pos();
        event->accept();

        QApplication::restoreOverrideCursor();
    }

    QChartView::mouseMoveEvent(event);
}

void SinView::setXRange(float min, float max)
{
    axisX->setRange(min, max);
}

void SinView::setYRange(float min, float max)
{
    axisY->setRange(min, max);
}

SinView::~SinView()
{
    delete ui;
    delete chart;
}
