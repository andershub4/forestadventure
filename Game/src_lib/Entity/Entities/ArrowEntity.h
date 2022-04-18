/*
 *	Copyright (C) 2022 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

#include "Resource/Image.h"

namespace FA {

namespace Entity {

class ArrowEntity : public BasicEntity
{
public:
    ArrowEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
                EntityManager& entityManager, MessageBus& messageBus);
    virtual ~ArrowEntity();

    virtual std::string Name() const override { return "ArrowEntity"; }
    virtual EntityType Type() const override { return EntityType::Arrow; }

protected:
    virtual void PostUpdate(EntityService& entityService) override;

private:
    Image image_;

private:
    virtual void RegisterStates(StateMachine& stateMachine) override;
    virtual void RegisterProperties(EntityService& entityService) override;
    virtual void InitStates(const StateMachine& stateMachine, const EntityService& entityService,
                            const PropertyData& data) override;

    void BuildImages(const EntityService& entityService, StateType stateType);
    Image GetImage(const EntityService& entityService, StateType stateType) const;
};

}  // namespace Entity

}  // namespace FA
