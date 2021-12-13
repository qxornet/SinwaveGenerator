#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <string>
#include <string_view>

#include <QObject>
#include <QFileDialog>

struct FileHead_t
{
    uint8_t sectionStart = '%';
    uint32_t minCurrPos = 0;
    uint32_t maxCurrPos = 0;

    float amplitude = 0;
    int frequency = 0;
};


class FileManager : public QObject
{
    Q_OBJECT

public:

    explicit FileManager(QObject *parent = nullptr);

signals:

    void sendData(float, float);
    void clearVisibleData();

public slots:

    FileHead_t getHead() const;

    void readFile(std::string_view path);
    void writeFile(std::string_view path);

    void addData(float value);
    void popFront();

    void makeHead(uint32_t minCurr, uint32_t maxCurr, float amplitude, int frequency);

private:

    std::vector<float> buffer;
    FileHead_t fileHead;

};

#endif // FILEMANAGER_H
