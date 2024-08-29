#include "TransformComponent.h"

GameMath::Matrix3 GameEngine::TransformComponent::getLocalMatrix()
{
    return m_localMatrix;
}

GameMath::Matrix3 GameEngine::TransformComponent::getGlobalMatrix()
{
    updateMatrices();
    return m_globalMatrix;
}

void GameEngine::TransformComponent::setLocalPosition(GameMath::Vector2 position)
{
    m_translation = position;
}

GameMath::Vector2 GameEngine::TransformComponent::getLocalPosition()
{
    return m_translation;
}

GameMath::Vector2 GameEngine::TransformComponent::getGlobalPosition()
{
    updateMatrices();
    return GameMath::Vector2(m_globalMatrix.m02, m_globalMatrix.m12);
}

void GameEngine::TransformComponent::setLocalRotation(float rotation)
{
    m_rotation = rotation;
}

float GameEngine::TransformComponent::getLocalRotation()
{
    updateMatrices();
    return m_rotation;
}

void GameEngine::TransformComponent::setLocalScale(GameMath::Vector2 scale)
{
    m_scale = scale;
}

GameMath::Vector2 GameEngine::TransformComponent::getLocalScale()
{
    updateMatrices();
    return m_scale;
}

GameMath::Vector2 GameEngine::TransformComponent::getGlobalScale()
{
    updateMatrices();

    GameMath::Vector2 xAxis = { m_globalMatrix.m00, m_globalMatrix.m01 };
    GameMath::Vector2 yAxis = { m_globalMatrix.m10, m_globalMatrix.m11 };

    return { xAxis.getMagnitude(), yAxis.getMagnitude() };
}

void GameEngine::TransformComponent::setParent(TransformComponent* parent)
{
    m_parent = parent;
}

GameEngine::TransformComponent* GameEngine::TransformComponent::getParent()
{
    return m_parent;
}

void GameEngine::TransformComponent::updateMatrices()
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
