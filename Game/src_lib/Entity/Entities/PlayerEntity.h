/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class AnimationSprite;

class PlayerEntity : public BasicEntity
{
public:
    PlayerEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                 EntityManager& entityManager, MessageBus& messageBus);
    virtual ~PlayerEntity();

    virtual std::string Name() const override { return "PlayerEntity"; }
    virtual EntityType Type() const override { return EntityType::Player; }

protected:
    virtual std::vector<MessageType> Messages() const override;

private:
    virtual void RegisterStates() override;
    virtual void RegisterProperties() override;
    virtual void RegisterShape(const PropertyData& data) override;
    virtual void RegisterAbilities() override;
    virtual void Start(EntityService& entityService) override;
    virtual void OnMessage(std::shared_ptr<Message> msg) override;

    void OnBeginMove(FaceDirection faceDirection);
    void OnUpdateMove(const sf::Vector2f& delta);
    void OnExitShoot();
    void OnBeginAnimation(StateType stateType, AnimationSprite& sprite);
    void OnUpdateAnimation(AnimationSprite& sprite);
};

}  // namespace Entity

}  // namespace FA
