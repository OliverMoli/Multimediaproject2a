#include "pch.h"
#include "RenderComponent.h"
#include "RenderManager.h"


RenderComponent::RenderComponent(GameObject & owner) : Component(owner)
{
}

void RenderComponent::setLayer(RenderLayer layer)
{
	this->layer = layer;
	RenderManager::getInstance().sortByLayer();
}

RenderLayer RenderComponent::getLayer() const
{
	return layer;
}
