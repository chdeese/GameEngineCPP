#include "ShapeComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include "Engine/TransformComponent.h"
#include "raylib.h"

void GameGraphics::ShapeComponent::draw()
{
	GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

	Color color = RAYLIB_H::GetColor(m_color);

	GameMath::Vector2 scale = getOwner()->getTransform()->getGlobalScale();

	float offset = 1;
	float positionCircleScale = 0.1f;

	if (m_shapeType == ShapeType::CIRCLE)
		RAYLIB_H::DrawEllipse(position.x, position.y, scale.x, scale.y, color);
	else if (m_shapeType == ShapeType::BOX)
		RAYLIB_H::DrawRectangle(position.x - scale.x / 2, position.y - scale.y / 2, scale.x, scale.y, color);
	RAYLIB_H::DrawCircle(position.x, position.y, ((scale.x + scale.y) / 2) * positionCircleScale, RAYLIB_H::RED);
}
