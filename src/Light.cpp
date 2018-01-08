#include "../include/Light.h"

Light::Light(const Vec3 & p_position) : m_position(p_position), m_ambientComponent(0.4f), m_diffuseComponent(0.3f), m_specularComponent(0.4f){}

Light::~Light(){}

Light::Light(const float p_x, const float p_y, const float p_z) : m_position(Vec3(p_x, p_y, p_z)), m_ambientComponent(0.4f), m_diffuseComponent(0.3f), m_specularComponent(0.4f) {}

Vec3 Light::GetPosition()
{
	return m_position;
}

void Light::SetPosition(const float p_x, const float p_y, const float p_z)
{
	m_position.x = p_x;
	m_position.y = p_y;
	m_position.z = p_z;
}

float Light::GetAmbient()
{
	return m_ambientComponent;
}

float Light::GetDiffuse()
{
	return m_diffuseComponent;
}

float Light::GetSpecular()
{
	return m_specularComponent;
}

void Light::SetLight(const float p_ambient, const float p_diffuse, const float p_specular)
{
	m_ambientComponent = p_ambient;
	m_diffuseComponent = p_diffuse;
	m_specularComponent = p_specular;
}
