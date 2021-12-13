#include "filemanager.h"

FileManager::FileManager(QObject *parent)
    : QObject{parent}
{

}

void FileManager::readFile(std::string_view path)
{
    std::ifstream file(path.data(), std::ios_base::in | std::ios_base::binary);

    if(!file.is_open()) return;
    FileHead_t header;


    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if(header.sectionStart != '%') return;

    float currXPoint = 0;
    fileHead = header;
    buffer.clear();

    emit clearVisibleData();

    while(!file.eof())
    {
        float value;
        file.read(reinterpret_cast<char*>(&value), sizeof(value));
        buffer.push_back(value);
        emit sendData(currXPoint, buffer.back());
        currXPoint++;
    }

    file.close();
}

void FileManager::writeFile(std::string_view path)
{
    std::ofstream file(path.data(), std::ios_base::out | std::ios_base::binary);

    if(!file.is_open()) return;

    file.write(reinterpret_cast<char*>(&fileHead), sizeof(fileHead));

    for(auto value : buffer)
    {
        file.write(reinterpret_cast<char*>(&value), sizeof(value));
    }

    file.close();
}

void FileManager::addData(float value)
{
    buffer.push_back(value);
}

void FileManager::popFront()
{
    buffer.erase(buffer.begin());
}

void FileManager::makeHead(uint32_t minCurr, uint32_t maxCurr, float amplitude, int frequency)
{
    auto& [secStart, minCurrVal, maxCurVal, ampl, freq] = fileHead;

    secStart = '%';
    minCurrVal = minCurr;
    maxCurVal = maxCurr;
    ampl = amplitude;
    freq = frequency;
}

FileHead_t FileManager::getHead() const
{
    return fileHead;
}


