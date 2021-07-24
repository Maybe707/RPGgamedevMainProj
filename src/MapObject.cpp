#include "MapObject.h"

MapObject::MapObject() {}

MapObject::MapObject(char symbol, float xAxis, float yAxis, float size) :
        m_Symbol(symbol),
        m_xAxis(xAxis),
        m_yAxis(yAxis),
        m_Size(size) {}

char MapObject::getSymbol()
{
    return m_Symbol;
}

float MapObject::getXAxis()
{
    return m_xAxis;
}

float MapObject::getYAxis()
{
    return m_yAxis;
}

float MapObject::getSize()
{
    return m_Size;
}

void MapObject::setSymbol(char symbol)
{
    m_Symbol = symbol;
}

void MapObject::setXAxis(float xAxis)
{
    m_xAxis = xAxis;
}

void MapObject::setYAxis(float yAxis)
{
    m_yAxis = yAxis;
}

void MapObject::setSize(float size)
{
    m_Size = size;
}

void MapObject::setI(int i)
{
    m_i = i;
}

void MapObject::setJ(int j)
{
    m_j = j;
}
