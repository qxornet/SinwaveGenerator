#pragma once

#include <iostream>
#include <fstream>
#include <memory>

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRubberBand>
#include <QChart>
#include <QtCharts/QChartView>
#include <QTimer>
#include <QFileDialog>

#include "filemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SinWaveGenerator; }
QT_END_NAMESPACE


class SinWaveGenerator : public QMainWindow
{
    Q_OBJECT

public:

    SinWaveGenerator(QWidget *parent = nullptr);
    ~SinWaveGenerator();

private slots:

    void compute();
    void switchProccess(bool enable);
    float genSinValue(int value);
    void setDefaults();
    void acceptValues();
    void currSliderValue(int value);

    void saveData();
    void loadData();

private:

    Ui::SinWaveGenerator *ui;

    const int pointsCount = 600;

    uint32_t minCurrValue = 0;
    uint32_t currentValue = 0;
    float amplitude = 100;
    int  frequency = 100;

    std::unique_ptr<QTimer> computeTimer = std::make_unique<QTimer>();
    std::unique_ptr<FileManager> fileManager = std::make_unique<FileManager>(this);
};
