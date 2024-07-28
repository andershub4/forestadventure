/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include <unordered_map>

#include "BasicEntity.h"

#include "Animation/ColliderAnimation.h"
#include "Animation/ImageAnimation.h"
#include "Enum/FaceDirection.h"
#include "Enum/MoveDirection.h"
#include "Resource/ColliderData.h"
#include "Resource/ImageData.h"
#include "ShapeParts/AnimationPart.h"

namespace FA {

namespace Entity {

class PlayerEntity : public BasicEntity
{
public:
    static const std::string str;

    PlayerEntity(EntityId id, const PropertyData& data, const Shared::MapData& mapData, const EntityService& service);
    virtual ~PlayerEntity();

    virtual EntityType Type() const override { return EntityType::Player; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }

protected:
    virtual std::vector<Shared::MessageType> Messages() const override;

private:
    virtual void RegisterProperties() override;
    virtual void ReadProperties(const std::unordered_map<std::string, std::string>& properties) override;
    virtual void RegisterStates(std::shared_ptr<State> idleState, std::shared_ptr<State> deadState,
                                const PropertyData& data) override;
    virtual void OnInit() override;
    virtual void OnMessage(std::shared_ptr<Shared::Message> msg) override;
    virtual void OnBeginDie() override;

    void OnBeginMove(MoveDirection moveDirection);
    void OnUpdateMove(const sf::Vector2f& delta);
    void OnShoot();

    std::shared_ptr<AnimationPart<Shared::ImageAnimation, FaceDirection>> MakeShapePart(
        const std::unordered_map<FaceDirection, std::vector<Shared::ImageData>>& faceDirImages);
    std::shared_ptr<AnimationPart<Shared::ColliderAnimation, FaceDirection>> MakeColliderPart(
        const std::unordered_map<FaceDirection, std::vector<Shared::ColliderData>>& faceDirColliders);

    void DefineIdleState(std::shared_ptr<State> state);
    void DefineMoveState(std::shared_ptr<State> state);
    void DefineAttackState(std::shared_ptr<State> state);
    void DefineAttackWeaponState(std::shared_ptr<State> state);
};

}  // namespace Entity

}  // namespace FA
