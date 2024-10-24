#pragma once
#include "Engine/Entity.h"

namespace Physics
{
	class FluidParticle : public Engine::Entity
	{
	private:
		float m_mass;
		float m_size;

	public:
		FluidParticle(float mass, float size) : Engine::Entity() { m_mass = mass; m_size = size; }

		void onStart() override;
		void onUpdate(double deltaTime) override;
	};
}