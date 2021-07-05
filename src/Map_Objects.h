#ifndef MAP_OBJECTS
#define MAP_OBJECTS

class Map_Objects
{
	char m_Symbol;
	float m_xAxis;
	float m_yAxis;
	float m_Size;
	int m_i;
	int m_j;
    
public:
    Map_Objects();
    Map_Objects(char symbol, float xAxis, float yAxis, float size);

	char get_Symbol();
	float get_xAxis();
	float get_yAxis();
	float get_Size();
	int getI();
	int getJ();

	void set_Symbol(char symbol);
	void set_xAxis(float xAxis);
	void set_yAxis(float yAxis);
	void set_Size(float size);
	void setI(int i);
	void setJ(int j);
};

#endif
