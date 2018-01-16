#pragma once

class IManager
{
public:
	virtual ~IManager() = default;

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Close() = 0;
};
