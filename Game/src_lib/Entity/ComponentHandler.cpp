/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#include "ComponentHandler.h"

#include "Components/FaceDirectionComponent.h"
#include "Components/MovementComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"

namespace FA {

namespace Entity {

ComponentHandler::ComponentHandler(const ComponentData& data)
    : data_(data)
{
    auto position = data.position_;
    auto scale = data.scale_;
    compStore_.AddComponent<TransformComponent>(position, scale);
}

ComponentHandler::~ComponentHandler() = default;

template <>
std::shared_ptr<MovementComponent> ComponentHandler::AddComponent<MovementComponent>()
{
    auto t = compStore_.GetComponent<TransformComponent>();
    auto velocity = data_.velocity_;
    return compStore_.AddComponent<MovementComponent>(*t, velocity);
}

template <>
std::shared_ptr<SpriteComponent> ComponentHandler::AddComponent<SpriteComponent, const AnimationComponent&>(
    const AnimationComponent& animation)
{
    auto t = compStore_.GetComponent<TransformComponent>();
    auto d = compStore_.GetComponent<FaceDirectionComponent>();
    return compStore_.AddComponent<SpriteComponent>(*t, *d, animation);
}

}  // namespace Entity

}  // namespace FA
