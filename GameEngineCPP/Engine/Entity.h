#pragma once
#include "List.h"
#include "Component.h"

namespace GameEngine
{
	class TransformComponent;

	class Entity
	{
	public:
		Entity();

		void start();

		void update(double deltaTime);

		void fixedUpdate(double fixedDeltaTime);
		
		void draw();

		void end();

		void addComponent(Component* component);

		template<typename T>
		T* addComponent();

		template<typename T>
		T* addComponent(T* component);

		template<typename T>
		T* getComponent();

		virtual void onStart() {}
		virtual void onUpdate(double deltaTime) {}
		virtual void onFixedUpdate(float fixedDeltaTime) {}
		virtual void onEnd() {}
		virtual void onDisable() {}
		virtual void onEnable() {}

		bool getStarted() { return m_started; }
		TransformComponent* getTransform() { return m_transform; }

		bool getEnabled() { return m_enabled; }
		void setEnabled(bool enabled);

	private:
		bool m_started;
		bool m_enabled;
		TransformComponent* m_transform;
		List<Component*> m_components;

	};

	template<typename T>
	inline T* Entity::addComponent()
	{
		Component* component = new T();

		component->setOwner(this);
		m_components.add(component);

		return (T*)component;
	}

	template<typename T>
	inline T* Entity::addComponent(T* component)
	{
		component->setOwner(this);
		m_components.add(component);
		return component;
	}

	template<typename T>
	inline T* Entity::getComponent()
	{
		T* result = nullptr;

		for (Component* component : m_components)
		{
			if (result = dynamic_cast<T*>(component))
				break;
		}

		return result;
	}
}