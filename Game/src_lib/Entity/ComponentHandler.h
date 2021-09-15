/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#include "ComponentData.h"
#include "ComponentStore.h"
#include "Enum/FrameType.h"

namespace FA {

class CameraManager;
class AnimationDb;

namespace Entity {

class AnimationComponent;
class MovementComponent;
class SpriteComponent;
class FaceDirectionComponent;
class AttackComponent;
class AttackWeaponComponent;
class CameraComponent;

class ComponentHandler
{
public:
    ComponentHandler(const ComponentData &data, CameraManager &cameraManager);
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
    std::shared_ptr<AttackComponent> AddComponent<AttackComponent>();

    template <>
    std::shared_ptr<AttackWeaponComponent> AddComponent<AttackWeaponComponent>();

    template <>
    std::shared_ptr<SpriteComponent> AddComponent<SpriteComponent>();

    template <>
    std::shared_ptr<CameraComponent> AddComponent<CameraComponent>();

    void InitComponents(const AnimationDb &animationDb);

private:
    ComponentStore compStore_;
    ComponentData data_;
    std::vector<FrameType> frameTypes_;
    CameraManager &cameraManager_;
};

}  // namespace Entity

}  // namespace FA
