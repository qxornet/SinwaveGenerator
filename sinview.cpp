#include "sinview.hpp"
#include "ui_sinview.h"

SinView::SinView(QWidget *parent) :
    QChartView(parent),
    ui(new Ui::SinView)
{
    ui->setupUi(this);
}

SinView::~SinView()
{
    delete ui;
}
