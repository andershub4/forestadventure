/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <memory>
#include <vector>

#include "Enum/FrameType.h"
#include "Logging.h"
#include "PropertyData.h"
#include "PropertyStore.h"

namespace FA {

class CameraManager;
class AnimationDb;

namespace Entity {

class MovementBehavior;
class AttackBehavior;
class AttackWeaponBehavior;
class CameraAttribute;

class PropertyHandler
{
public:
    PropertyHandler(const PropertyData &data, CameraManager &cameraManager);
    ~PropertyHandler();

    template <class T>
    std::shared_ptr<T> AddAttribute()
    {
        return attributeStore_.AddProperty<T>(this);
    }

    template <class T>
    std::shared_ptr<T> AddBehavior()
    {
        return behaviorStore_.AddProperty<T>(this);
    }

    template <class T>
    std::shared_ptr<T> GetAttribute()
    {
        if (attributeStore_.HasProperty<T>()) {
            return attributeStore_.GetProperty<T>();
        }
        else {
            LOG_ERROR(typeid(T).name(), " is not in attributeStore");
            return AddAttribute<T>();
        }
    }

    template <class T>
    std::shared_ptr<T> GetBehavior()
    {
        if (behaviorStore_.HasProperty<T>()) {
            return behaviorStore_.GetProperty<T>();
        }
        else {
            LOG_ERROR(typeid(T).name(), " is not in behaviorStore");
            return AddBehavior<T>();
        }
    }

    template <>
    std::shared_ptr<MovementBehavior> AddBehavior<MovementBehavior>();

    template <>
    std::shared_ptr<AttackBehavior> AddBehavior<AttackBehavior>();

    template <>
    std::shared_ptr<AttackWeaponBehavior> AddBehavior<AttackWeaponBehavior>();

    template <>
    std::shared_ptr<CameraAttribute> AddAttribute<CameraAttribute>();

    void Awake();
    void InitProperties(const AnimationDb &animationDb);

private:
    PropertyStore attributeStore_;
    PropertyStore behaviorStore_;
    PropertyData data_;
    std::vector<FrameType> frameTypes_;
    CameraManager &cameraManager_;
};

}  // namespace Entity

}  // namespace FA
