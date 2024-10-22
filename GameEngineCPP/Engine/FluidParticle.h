#pragma once
#include "Entity.h"

namespace Engine
{
	class FluidParticle : public Engine::Entity
	{
	private:
		float m_mass;
		float m_size;

	public:
		FluidParticle() : Engine::Entity() {}

		void setMass(float mass) { m_mass = mass; }
		void setSize(float size) { m_size = size; }

		void onStart() override;
		void onUpdate(double deltaTime) override;
	};
}