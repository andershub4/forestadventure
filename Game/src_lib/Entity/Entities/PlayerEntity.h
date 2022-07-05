/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class PlayerEntity : public BasicEntity
{
public:
    PlayerEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                 EntityManager& entityManager, MessageBus& messageBus, const sf::Vector2u& mapSize);
    virtual ~PlayerEntity();

    virtual std::string Name() const override { return "PlayerEntity"; }
    virtual EntityType Type() const override { return EntityType::Player; }
    virtual LayerType GetLayer() const override { return LayerType::Ground; }

protected:
    virtual std::vector<MessageType> Messages() const override;

private:
    virtual void RegisterProperties() override;
    virtual void RegisterShape() override;
    virtual void RegisterStates(std::shared_ptr<State> idleState, const PropertyData& data) override;
    virtual void Start() override;
    virtual void OnMessage(std::shared_ptr<Message> msg) override;
    virtual void OnDying() override;

    void OnBeginMove(FaceDirection faceDirection);
    void OnUpdateMove(const sf::Vector2f& delta);
    void OnExitShoot();
    void OnUpdateAnimation(const Animation& animation);
};

}  // namespace Entity

}  // namespace FA
