#include "TransformComponent.h"

GameMath::Matrix3 Engine::TransformComponent::getLocalMatrix()
{
    return m_localMatrix;
}

GameMath::Matrix3 Engine::TransformComponent::getGlobalMatrix()
{
    updateMatrices();
    return m_globalMatrix;
}

void Engine::TransformComponent::setLocalPosition(GameMath::Vector2 position)
{
    m_translation = position;
}

GameMath::Vector2 Engine::TransformComponent::getLocalPosition()
{
    return m_translation;
}

GameMath::Vector2 Engine::TransformComponent::getGlobalPosition()
{
    updateMatrices();
    return GameMath::Vector2(m_globalMatrix.m02, m_globalMatrix.m12);
}

void Engine::TransformComponent::setLocalRotation(float rotation)
{
    m_rotation = rotation;
}

float Engine::TransformComponent::getLocalRotation()
{
    updateMatrices();
    return m_rotation;
}

void Engine::TransformComponent::setLocalScale(GameMath::Vector2 scale)
{
    m_scale = scale;
}

GameMath::Vector2 Engine::TransformComponent::getLocalScale()
{
    updateMatrices();
    return m_scale;
}

GameMath::Vector2 Engine::TransformComponent::getGlobalScale()
{
    updateMatrices();

    GameMath::Vector2 xAxis = { m_globalMatrix.m00, m_globalMatrix.m01 };
    GameMath::Vector2 yAxis = { m_globalMatrix.m10, m_globalMatrix.m11 };

    return { xAxis.getMagnitude(), yAxis.getMagnitude() };
}

void Engine::TransformComponent::setParent(TransformComponent* parent)
{
    m_parent = parent;
}

Engine::TransformComponent* Engine::TransformComponent::getParent()
{
    return m_parent;
}

void Engine::TransformComponent::updateMatrices()
{
    GameMath::Matrix3 translation = GameMath::Matrix3::createTranslation(m_translation);
    GameMath::Matrix3 rotation = GameMath::Matrix3::createRotation(m_rotation);
    GameMath::Matrix3 scale = GameMath::Matrix3::createScale(m_scale);

    m_localMatrix = translation * rotation * scale;

    if (m_parent)
        m_globalMatrix = m_parent->getGlobalMatrix() * m_localMatrix;
    else
        m_globalMatrix = m_localMatrix;
}
