#pragma once
#include "Mesh.h"
#include "Mat4.h"

class Entity
{
public:
	Entity();
	~Entity();

	Mesh* GetMesh() const;
	Toolbox::Mat4& GetMatrix();

	void SetAlpha(const float p_alpha);
	float GetAlpha() const;
	void SetMesh(const Mesh& p_mesh);
	void SetMatrix(const Toolbox::Mat4& p_matrix);
	void SetColor(const float p_r, const float p_g, const float p_b, const float p_a = 255) const;
private:
	Mesh* m_mesh;
	Toolbox::Mat4 m_transformation;
	float m_alpha;
};

