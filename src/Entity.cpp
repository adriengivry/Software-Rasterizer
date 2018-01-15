#include "../include/Entity.h"

using namespace Toolbox;

Entity::Entity() : m_mesh(nullptr), m_alpha(1.f) {}
Entity::~Entity() 
{
	delete m_mesh;
}

Mesh* Entity::GetMesh() const
{
	return m_mesh;
}

Mat4& Entity::GetMatrix()
{
	return m_transformation;
}

void Entity::SetAlpha(const float p_alpha)
{
	m_alpha = p_alpha;
}

float Entity::GetAlpha()
{
	return m_alpha;
}

void Entity::SetMesh(const Mesh& p_mesh)
{
	m_mesh = new Mesh();
	*m_mesh = p_mesh;
}

void Entity::SetMatrix(const Mat4& p_matrix)
{
	m_transformation = p_matrix;
}

void Entity::SetColor(const float p_r, const float p_g, const float p_b, const float p_a) const
{
	m_mesh->SetColor(p_r, p_g, p_b, p_a);
}
