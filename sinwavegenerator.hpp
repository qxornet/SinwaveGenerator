#pragma once

#include <iostream>

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRubberBand>
#include <QChart>
#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE
namespace Ui { class SinWaveGenerator; }
QT_END_NAMESPACE


class SinWaveGenerator : public QMainWindow
{
    Q_OBJECT

public:

    SinWaveGenerator(QWidget *parent = nullptr);
    ~SinWaveGenerator();

public slots:

    void switchProccess(bool enable);

private:

    double genSinValue(int value);

private:

    Ui::SinWaveGenerator *ui;

    float amplitude = 1;
    float frequency = 1;

    double lastSinValue = 0.0;

    QGraphicsScene *graphScene;
};
