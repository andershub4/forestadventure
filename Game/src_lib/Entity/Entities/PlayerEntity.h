/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

#include "Resource/Animation.h"

namespace FA {

namespace Entity {

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
    std::unordered_map<StateType, std::unordered_map<FaceDirection, Animation>> animations_;

private:
    virtual void RegisterStates(StateMachine& stateMachine) override;
    virtual void RegisterProperties(EntityService& entityService) override;
    virtual void Start(EntityService& entityService) override;
    virtual void InitStates(const StateMachine& stateMachine, const EntityService& entityService,
                            const PropertyData& data) override;
    virtual void OnMessage(std::shared_ptr<Message> msg) override;

    void InitState(std::shared_ptr<BasicState> state, const std::vector<FaceDirection>& directions,
                   const EntityService& entityService);

    void BuildAnimations(const EntityService& entityService, StateType stateType);
    Animation GetAnimation(const EntityService& entityService, StateType stateType) const;
};

}  // namespace Entity

}  // namespace FA
