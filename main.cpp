#include "sinwavegenerator.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication applicaton(argc, argv);
    SinWaveGenerator window;
    window.show();
    return applicaton.exec();
}
