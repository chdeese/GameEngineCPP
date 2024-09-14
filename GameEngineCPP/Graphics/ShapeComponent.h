#pragma once

#include "Engine/Component.h"

namespace GameGraphics
{
	enum ShapeType
	{
		CIRCLE, BOX
	};

	class ShapeComponent : public Engine::Component
	{
	public:
		void setColor(unsigned int color) { m_color = color; }
		unsigned int getColor() { return m_color; }

		void setShapeType(ShapeType type) { m_shapeType = type; }
		ShapeType getShapeType() { return m_shapeType; }

		void draw() override;

	private:
		ShapeType m_shapeType;
		unsigned int m_color = 0x66AAFFFF;

	};
}