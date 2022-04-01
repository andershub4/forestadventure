/*
 *	Copyright (C) 2021 Anders Wennmo
 *	This file is part of forestadventure which is released under MIT license.
 *	See file LICENSE for full license details.
 */

#pragma once

#include "BasicEntity.h"

namespace FA {

namespace Entity {

class MoleEntity : public BasicEntity
{
public:
    MoleEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
               EntityManager& entityManager, MessageBus& messageBus);
    virtual ~MoleEntity();

    virtual std::string Name() const override { return "MoleEntity"; }
    virtual EntityType Type() const override { return EntityType::Mole; }

private:
    virtual void RegisterModes(ModeController& modeController) override;
    virtual void RegisterAttributes(EntityService& entityService) override;
    virtual void InitModes(const ModeController& modeController, const EntityService& entityService,
                           const AttributeData& data) override;

    void InitMode(std::shared_ptr<BasicMode> mode, const std::vector<FaceDirection>& directions,
                  const EntityService& entityService);
};

}  // namespace Entity

}  // namespace FA
