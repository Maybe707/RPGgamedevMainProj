#include "Player_Implementation.h"

Player_Implementation::Player_Implementation(float xAxis, float yAxis, float speed) : m_xAxis(xAxis), m_yAxis(yAxis), m_Speed(speed) {}

void Player_Implementation::set_xAxis(float xAxis) { m_xAxis = xAxis; }
void Player_Implementation::set_yAxis(float yAxis) { m_yAxis = yAxis; }

float Player_Implementation::get_xAxis() { return m_xAxis; }
float Player_Implementation::get_yAxis() { return m_yAxis; }
float Player_Implementation::get_xRange() { return m_xRange; }
float Player_Implementation::get_yRange() { return m_yRange; }

void Player_Implementation::Draw (const int SCR_WIDTH, const int SCR_HEIGHT, Shader ourShader, unsigned int VAO, unsigned int texture2)
{
	Matrix<float, 4> trans(64.0f);

	trans = Translate(trans, Vector<float, 4> (m_xAxis, m_yAxis, 0.0f, 1.0f));

	unsigned int transformtLoc = glGetUniformLocation(ourShader.ID, "model");
	glUniformMatrix4fv(transformtLoc, 1, GL_TRUE, &trans[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2);

	ourShader.use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Player_Implementation::Receiver(int key, int action)
{
	m_key_axis = key;
	m_action = action;
}

int& Player_Implementation::getKeyAxis()
{
	return m_key_axis;
}

void Player_Implementation::setKeyAxis(int key)
{
	m_key_axis = key;
}

int& Player_Implementation::getAction()
{
	return m_action;
}

void Player_Implementation::set_Speed(const float &speed)
{
	m_Speed = speed;
}

float& Player_Implementation::get_Speed()
{
	return m_Speed;
}
