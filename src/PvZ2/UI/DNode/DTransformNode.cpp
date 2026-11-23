//
//  DTransformNode.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-23.
//

#include "SexyAppFramework/Common.h"

#include "DNode/DNode.h"

/////////////// Accessors ///////////////

DTransformNode& DTransformNode::setVisible(bool visible)
{
	m_bIsVisible = visible;
	return *this;
}

bool DTransformNode::isVisible() const
{
	return m_bIsVisible;
}

const DVec2& DTransformNode::getPosition() const
{
	return m_pos;
}

float DTransformNode::getPositionX() const
{
	return m_pos.x;
}

float DTransformNode::getPositionY() const
{
	return m_pos.y;
}

float DTransformNode::getScaleX() const
{
	return m_scale.x;
}

float DTransformNode::getScaleY() const
{
	return m_scale.y;
}

const DVec2& DTransformNode::getScaleXY() const
{
	return m_scale;
}

float DTransformNode::getScale() const
{
	return m_scale.x;
}

float DTransformNode::getRotation() const
{
	return m_rotate;
}

const FRect& DTransformNode::getContextRect() const
{
	return m_contextRect;
}

const DVec2& DTransformNode::getAnchorPoint() const
{
	return m_anchorPoint;
}

const DVec2& DTransformNode::getAnchorPointSize() const
{
	return m_anchorPointSize;
}

/////////////// Components ///////////////

DComponent* DTransformNode::getComponent(const std::string& name)
{
	return m_componentContainer.get(name);
}

bool DTransformNode::addComponent(DComponent* component)
{
	return m_componentContainer.add(component);
}

bool DTransformNode::removeComponent(const std::string& name)
{
	return m_componentContainer.remove(name);
}

bool DTransformNode::removeComponent(DComponent* component)
{
	return m_componentContainer.remove(component);
}

void DTransformNode::removeAllComponents()
{
	m_componentContainer.removeAll();
}

void DTransformNode::setRenderEffect(RenderEffectDefinition* effect)
{
	m_renderEffect = effect;
}

/////////////// Transform ///////////////

DTransformNode& DTransformNode::setPosition(const DVec2& pos)
{
	m_pos = pos;
	m_bTransformDirty = true;
	return *this;
}

DTransformNode& DTransformNode::setPositionX(float x)
{
	m_bTransformDirty = true;
	m_pos.x = x;
	return *this;
}

DTransformNode& DTransformNode::setPositionY(float y)
{
	m_bTransformDirty = true;
	m_pos.y = y;
	return *this;
}

DTransformNode& DTransformNode::setScale(float s)
{
	m_bTransformDirty = true;
	m_scale.y = s;
	m_scale.x = s;
	return *this;
}

DTransformNode& DTransformNode::setScaleX(float sx)
{
	m_bTransformDirty = true;
	m_scale.x = sx;
	return *this;
}

DTransformNode& DTransformNode::setScaleY(float sy)
{
	m_bTransformDirty = true;
	m_scale.y = sy;
	return *this;
}

DTransformNode& DTransformNode::setRotation(float angle)
{
	m_bTransformDirty = true;
	m_rotate = angle;
	return *this;
}

DTransformNode& DTransformNode::setPosition(float x, float y)
{
	m_bTransformDirty = true;
	m_pos.set(x, y);
	return *this;
}

DTransformNode& DTransformNode::setScale(float sx, float sy)
{
	m_bTransformDirty = true;
	m_scale.set(sx, sy);
	return *this;
}

void DTransformNode::setTouchDispatcher(DTouchEventDispatcher* touchDispatcher)
{
	m_touchDispatcher = touchDispatcher;
}

DTouchEventDispatcher* DTransformNode::getTouchDispatcher()
{
	return m_touchDispatcher;
}

const std::string& DTransformNode::getName() const
{
	return m_name;
}
