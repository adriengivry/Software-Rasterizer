#pragma once
#include "Mat4.h"

class Light
{
private:
	Toolbox::Vec3 m_position;
	float m_ambientComponent;
	float m_diffuseComponent;
	float m_specularComponent;

public:
	Light(const Toolbox::Vec3& p_position);
	~Light();
	Light(const float p_x, const float p_y, const float p_z);

	Toolbox::Vec3 GetPosition();
	void SetPosition(const float p_x, const float p_y, const float p_z);
	float GetAmbient();
	float GetDiffuse();
	float GetSpecular();
	void SetLight(const float p_ambient, const float p_diffuse, const float p_specular);
};