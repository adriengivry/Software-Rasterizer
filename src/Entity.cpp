#include "../include/Entity.h"

Entity::Entity() : m_mesh(new Mesh()) {}
Entity::~Entity() {delete m_mesh;}

Mesh * Entity::GetMesh()
{
	return m_mesh;
}

Mat4 Entity::GetMatrix()
{
	return m_transformation;
}

void Entity::SetMesh(const Mesh& p_mesh)
{
	*m_mesh = p_mesh;
}

void Entity::SetMatrix(const Mat4 p_matrix)
{
	m_transformation = p_matrix;
}
