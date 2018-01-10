#pragma once
#include "IObject.h"

class IManager : public IObject
{
public:
	virtual ~IManager() {}

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Close() = 0;
};
