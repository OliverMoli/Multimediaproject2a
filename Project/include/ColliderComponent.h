#pragma once
#include "Component.h"

class ColliderComponent:public Component
{
public:
	ColliderComponent(GameObject& owner,bool isTrigger);
	virtual bool intersect(std::shared_ptr<ColliderComponent> otherCol) = 0;
	void initialize() override;
	void update(float deltaTime) override;
	bool isTrigger() const;
	void setTrigger(bool trig);
private:
	bool trigger;
};
