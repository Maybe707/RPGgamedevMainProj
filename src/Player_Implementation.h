#ifndef PLAYER_IMPLEMENTATION
#define PLAYER_IMPLEMENTATION

#include "Unit_Interface.h"

class Player_Implementation : public Unit_Interface
{
	float m_xAxis;
	float m_yAxis;
	float m_Speed;
	float m_xRange = 32.0f;
	float m_yRange = 32.0f;
	int m_key_axis;
	int m_action;
public:
	Player_Implementation(float xAxis, float yAxis, float speed);

	void set_xAxis(float xAxis);
	void set_yAxis(float yAxis);
	void setKeyAxis(int key);
	void set_Speed(const float& speed);

	float get_xAxis();
	float get_yAxis();
	float get_xRange();
	float get_yRange();
	int& getKeyAxis();
	int& getAction();
	float& get_Speed();

	virtual void Draw (const int SCR_WIDTH, const int SCR_HEIGHT, Shader ourShader, unsigned int VAO, unsigned int texture2) override;
	virtual void Receiver(int key, int action) override;
};

#endif
