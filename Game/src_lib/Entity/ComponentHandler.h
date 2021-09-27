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
#include "Logging.h"

namespace FA {

class CameraManager;
class AnimationDb;

namespace Entity {

class MovementComponent;
class AttackComponent;
class AttackWeaponComponent;
class CameraComponent;

class ComponentHandler
{
public:
    ComponentHandler(const ComponentData &data, CameraManager &cameraManager);
    ~ComponentHandler();

    template <class T>
    std::shared_ptr<T> AddComponent()
    {
        return compStore_.AddComponent<T>(this);
    }

    template <class T>
    std::shared_ptr<T> GetComponent()
    {
        if (compStore_.HasComponent<T>()) {
            return compStore_.GetComponent<T>();
        }
        else {
            LOG_ERROR(typeid(T).name(), " is not in compStore");
            return AddComponent<T>();
        }
    }

    template <>
    std::shared_ptr<MovementComponent> AddComponent<MovementComponent>();

    template <>
    std::shared_ptr<AttackComponent> AddComponent<AttackComponent>();

    template <>
    std::shared_ptr<AttackWeaponComponent> AddComponent<AttackWeaponComponent>();

    template <>
    std::shared_ptr<CameraComponent> AddComponent<CameraComponent>();

    void Awake();
    void InitComponents(const AnimationDb &animationDb);

private:
    ComponentStore compStore_;
    ComponentData data_;
    std::vector<FrameType> frameTypes_;
    CameraManager &cameraManager_;
};

}  // namespace Entity

}  // namespace FA
