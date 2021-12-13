#pragma once

#include <QWidget>
#include <QtCharts/QtCharts>
#include <QScatterSeries>

namespace Ui {
class SinView;
}

class SinView : public QChartView
{
    Q_OBJECT

public:

    explicit SinView(QWidget *parent = nullptr);
    ~SinView();

protected:

    void changeEvent(QEvent *e);
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

public slots:

    void setXRange(float min, float max);
    void setYRange(float min, float max);

    void setXInterval(float value);
    void setYInterval(float value);

    void addData(float x, float y);
    void popFront();
    void clearData();

    virtual void setDefaultScaling();

private:

    Ui::SinView *ui;

    QChart* chart = new QChart();
    QLineSeries* series = new QLineSeries();

    QValueAxis* axisX = new QValueAxis;
    QValueAxis* axisY = new QValueAxis;

    QPointF m_lastMousePos;

    float maxY;
    bool isFirst = true;
};

