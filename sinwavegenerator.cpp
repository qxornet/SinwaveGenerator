#include "sinwavegenerator.hpp"
#include "ui_sinwavegenerator.h"

SinWaveGenerator::SinWaveGenerator(QWidget *parent) : QMainWindow(parent), ui(new Ui::SinWaveGenerator)
{
    ui->setupUi(this);

    computeTimer->setInterval(frequency);

    connect(ui->switchButton, SIGNAL(toggled(bool)), this, SLOT(switchProccess(bool)));
    connect(ui->defaultButton, SIGNAL(pressed()), this, SLOT(setDefaults()));
    connect(ui->acceptButton,  SIGNAL(pressed()), this, SLOT(acceptValues()));
    connect(computeTimer.get(), SIGNAL(timeout()), this, SLOT(compute()));
    connect(ui->frameScrollBar, SIGNAL(valueChanged(int)), this, SLOT(currSliderValue(int)));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveData()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadData()));
    connect(ui->saveButton, SIGNAL(pressed()), this, SLOT(saveData()));
    connect(ui->openButton, SIGNAL(pressed()), this, SLOT(loadData()));
    connect(fileManager.get(), SIGNAL(clearVisibleData()), ui->sinView, SLOT(clearData()));
    connect(fileManager.get(), SIGNAL(sendData(float, float)), ui->sinView, SLOT(addData(float,float)));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutMessage()));

    connect(ui->actionStart, &QAction::triggered, this, [this]() {
        ui->switchButton->setChecked(true);
    });

    connect(ui->actionStop, &QAction::triggered, this, [this]() {
        ui->switchButton->setChecked(false);
    });

    ui->sinView->setYRange(-(amplitude+50), amplitude+50);
    ui->sinView->setXRange(0, pointsCount);
    for(currentValue = 0; currentValue < pointsCount; currentValue++)
    {
        auto sinValue = genSinValue(currentValue);
        ui->sinView->addData(currentValue, sinValue);
        fileManager->addData(sinValue);
    }
}

SinWaveGenerator::~SinWaveGenerator()
{
    delete ui;
}

void SinWaveGenerator::compute()
{
    currentValue++;
    minCurrValue++;
    auto sinValue = genSinValue(currentValue);
    ui->sinView->addData(currentValue, sinValue);
    fileManager->addData(sinValue);
    ui->sinView->setXRange(minCurrValue, currentValue);
    ui->frameScrollBar->setMaximum(minCurrValue);
    ui->frameScrollBar->setValue(minCurrValue);
}

void SinWaveGenerator::switchProccess(bool enable)
{
    if(enable)
    {
        ui->switchButton->setIcon(QIcon(":/icons/stop.png"));
        computeTimer->start();
    }
    else
    {
        ui->switchButton->setIcon(QIcon(":/icons/start.png"));
        computeTimer->stop();
    }
}

float SinWaveGenerator::genSinValue(int value)
{
    return amplitude * sin(2 * value * (M_PI/180) * (frequency * 0.01));
}

void SinWaveGenerator::setDefaults()
{
    amplitude = 100;
    frequency = 100;
    ui->freqValue->setValue(100);
    ui->ampValue->setValue(amplitude);
    ui->sinView->setYRange(-(amplitude+50), amplitude+50);
}

void SinWaveGenerator::acceptValues()
{
    frequency = ui->freqValue->value();
    amplitude = ui->ampValue->value();
    ui->sinView->setYRange(-(amplitude+50), amplitude+50);
}

void SinWaveGenerator::currSliderValue(int value)
{
    if((value + pointsCount) >= currentValue)
    {
        ui->sinView->setXRange(minCurrValue, currentValue);
        return;
    }

    ui->sinView->setXRange(value, value + pointsCount);
}

void SinWaveGenerator::showAboutMessage()
{
    QMessageBox::about(this, "Sinwave Generator v1.0", "<p>Created by <b>Qxornet</b><br><b>Github</b>: <a href=https://github.com/qxornet>https://github.com/qxornet</a><br>Made with <b>Qt 6</b>.<p>");
}

// -------------------------------------------------------------

void SinWaveGenerator::saveData()
{
    QString qpath = QFileDialog::getSaveFileName(this,tr("Save sinus table"), "", tr("Point sinus table ( *.pst ) "));
    if(qpath.isEmpty()) return;
    qpath += ".pst";

    fileManager->makeHead(minCurrValue, currentValue, amplitude, frequency);
    fileManager->writeFile(qpath.toStdString());
}

void SinWaveGenerator::loadData()
{
    QString qpath = QFileDialog::getOpenFileName(this, tr("Open sinus table"), "", tr("Point sinus table ( *.pst ) "));
    if(qpath.isEmpty()) return;

    fileManager->readFile(qpath.toStdString());

    auto head = fileManager->getHead();

    currentValue = head.maxCurrPos;
    minCurrValue = head.minCurrPos;
    frequency = head.frequency;
    amplitude = head.amplitude;
    ui->sinView->setYRange(-(amplitude+50), amplitude+50);
    ui->frameScrollBar->setMaximum(minCurrValue);
    ui->frameScrollBar->setValue(minCurrValue);
    ui->sinView->setXRange(minCurrValue, currentValue);

    ui->freqValue->setValue(frequency);
    ui->ampValue->setValue(amplitude);
}

