#include "sinwavegenerator.hpp"
#include "ui_sinwavegenerator.h"

SinWaveGenerator::SinWaveGenerator(QWidget *parent) : QMainWindow(parent), ui(new Ui::SinWaveGenerator)
{
    ui->setupUi(this);

    graphScene = new QGraphicsScene(ui->sinView);
    connect(ui->switchButton, SIGNAL(toggled(bool)), this, SLOT(switchProccess(bool)));

    amplitude = 100;
    frequency = 1000 * 0.01;
    for(int i = 0; i < 200; i++)
    {
        double value = genSinValue(i);
        std::cout.precision(4);
        std::cout << std::fixed << value << std::endl;
    }

    ui->sinView->setScene(graphScene);
}

SinWaveGenerator::~SinWaveGenerator()
{
    delete ui;
}

void SinWaveGenerator::switchProccess(bool enable)
{
    if(enable)
        ui->switchButton->setIcon(QIcon(":/icons/stop.png"));
    else
        ui->switchButton->setIcon(QIcon(":/icons/start.png"));
}

double SinWaveGenerator::genSinValue(int value)
{
    return amplitude * sin(2 * value * (M_PI/180) * frequency);
}


//":/icons/stop.png"
