#include "Map_Objects.h"

Map_Objects::Map_Objects(){}

Map_Objects::Map_Objects(char symbol, float xAxis, float yAxis, float size) : m_Symbol(symbol),
		m_xAxis(xAxis), m_yAxis(yAxis), m_Size(size) {}

char Map_Objects::get_Symbol() { return m_Symbol; }
float Map_Objects::get_xAxis() { return m_xAxis; }
float Map_Objects::get_yAxis() { return m_yAxis; }
float Map_Objects::get_Size() { return m_Size; }
int Map_Objects::getI() { return m_i; }
int Map_Objects::getJ() { return m_j; }

void Map_Objects::set_Symbol(char symbol) { m_Symbol = symbol; }
void Map_Objects::set_xAxis(float xAxis) { m_xAxis = xAxis; }
void Map_Objects::set_yAxis(float yAxis) { m_yAxis = yAxis; }
void Map_Objects::set_Size(float size) { m_Size = size; }
void Map_Objects::setI(int i) { m_i = i; }
void Map_Objects::setJ(int j) { m_j = j; }
