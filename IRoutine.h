#pragma once
struct IRoutine
{
protected:
	virtual void Init() = 0;
	virtual void Release() = 0;

public:
	virtual void Update(float delta) = 0;
	virtual void Render(float delta) = 0;
};

