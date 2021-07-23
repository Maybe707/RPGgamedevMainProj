#include "Map_Objects.h"

MapObjects::MapObjects()
{ }

MapObjects::MapObjects(char symbol, float xAxis, float yAxis, float size) :
    m_Symbol(symbol),
    m_xAxis(xAxis),
    m_yAxis(yAxis),
    m_Size(size)
{ }

char MapObjects::getSymbol()
{ 
    return m_Symbol;
}

float MapObjects::getXAxis()
{
    return m_xAxis;
}

float MapObjects::getYAxis()
{
    return m_yAxis;
}

float MapObjects::getSize()
{
    return m_Size;
}

int MapObjects::getI()
{
    return m_i;
}

int MapObjects::getJ()
{
    return m_j;
}

void MapObjects::setSymbol(char symbol)
{
    m_Symbol = symbol;
}

void MapObjects::setXAxis(float xAxis)
{
    m_xAxis = xAxis;
}

void MapObjects::setYAxis(float yAxis)
{
    m_yAxis = yAxis;
}

void MapObjects::setSize(float size)
{
    m_Size = size;
}

void MapObjects::setI(int i)
{
    m_i = i;
}

void MapObjects::setJ(int j)
{
    m_j = j;
}
