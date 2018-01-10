#pragma once
#include "IManager.h"
#include "Entity.h"

class EntityManager : public IManager
{
public:
	EntityManager();
	~EntityManager();

private:
	std::vector<Entity*> m_entities;
};
