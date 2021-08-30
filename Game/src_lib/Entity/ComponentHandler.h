/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "ComponentData.h"
#include "ComponentStore.h"

namespace FA {

namespace Entity {

class AnimationComponent;
class MovementComponent;
class SpriteComponent;

class ComponentHandler
{
public:
    FaceDirection faceDir_ = FaceDirection::Down;

public:
    ComponentHandler(const ComponentData &data);
    ~ComponentHandler();

    template <class T>
    std::shared_ptr<T> GetComponent() const
    {
        return compStore_.GetComponent<T>();
    }

    template <class T>
    std::shared_ptr<T> GetComponent()
    {
        return compStore_.GetComponent<T>();
    }

    template <class T, typename... Args>
    std::shared_ptr<T> AddComponent(Args &&...args)
    {
        return compStore_.AddComponent<T, Args...>(std::forward<Args>(args)...);
    }

    template <>
    std::shared_ptr<MovementComponent> AddComponent<MovementComponent>();

    template <>
    std::shared_ptr<SpriteComponent> AddComponent<SpriteComponent, const AnimationComponent &>(
        const AnimationComponent &animation);

private:
    ComponentStore compStore_;
    ComponentData data_;
};

}  // namespace Entity

}  // namespace FA
