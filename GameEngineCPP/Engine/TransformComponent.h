#pragma once

#include "Component.h"
#include <Math/Matrix3.h>
#include <Math/Vector2.h>

namespace GameEngine
{
	class TransformComponent : public Component
	{
	public:
		GameMath::Matrix3 getLocalMatrix();
		GameMath::Matrix3 getGlobalMatrix();

		void setLocalPosition(GameMath::Vector2 position);
		GameMath::Vector2 getLocalPosition();
		GameMath::Vector2 getGlobalPosition();

		void setLocalRotation(float rotation);
		float getLocalRotation();

		void setLocalScale(GameMath::Vector2 scale);
		GameMath::Vector2 getLocalScale();

		GameMath::Vector2 getGlobalScale();

		void setParent(TransformComponent* parent);
		TransformComponent* getParent();

	private:
		GameMath::Matrix3 m_localMatrix;
		GameMath::Matrix3 m_globalMatrix;

		float m_rotation;
		GameMath::Vector2 m_scale = GameMath::Vector2(1.0f, 1.0f);
		GameMath::Vector2 m_translation = GameMath::Vector2{0.0f, 0.0f};

		TransformComponent* m_parent;

		TransformComponent** m_children;

		void updateMatrices();


	};
}