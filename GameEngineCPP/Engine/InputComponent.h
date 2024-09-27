#pragma once
#include "Engine/Component.h"

namespace Physics
{
	class RigidBodyComponent;
}

namespace Engine
{
	class InputComponent : public Component
	{
	private:
		float m_speed = 1000;
		Physics::RigidBodyComponent* m_rigidBody;
	public:
		void start() override;
		void update(double deltaTime) override;
	};
}