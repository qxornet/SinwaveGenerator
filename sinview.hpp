#pragma once

#include <QChartView>

namespace Ui {
class SinView;
}

class SinView : public QChartView
{
    Q_OBJECT

public:
    explicit SinView(QWidget *parent = nullptr);
    ~SinView();

private:
    Ui::SinView *ui;
};

