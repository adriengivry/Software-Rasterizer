#include "../include/Entity.h"

Entity::Entity() : m_mesh(nullptr) {}
Entity::~Entity() 
{
	if(m_mesh)
		delete m_mesh;
}

Mesh * Entity::GetMesh()
{
	return m_mesh;
}

Mat4& Entity::GetMatrix()
{
	return m_transformation;
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

void Entity::MultiplyMesh()
{
	if (m_mesh != nullptr)
	{
		for (int i = 0; i < m_mesh->GetVertices().size(); i++)
			m_mesh->GetVertices()[i].VertexTransform(m_transformation);
	}
}
