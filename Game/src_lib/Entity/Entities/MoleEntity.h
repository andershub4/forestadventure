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

class MoleEntity : public BasicEntity
{
public:
    MoleEntity(EntityId id, CameraManager& cameraManager, const SheetManager& sheetManager,
               EntityManager& entityManager, MessageBus& messageBus);
    virtual ~MoleEntity();

    virtual std::string Name() const override { return "MoleEntity"; }
    virtual EntityType Type() const override { return EntityType::Mole; }

private:
    std::unordered_map<ModeType, std::unordered_map<FaceDirection, Animation>> animations_;

private:
    virtual void RegisterModes(ModeController& modeController) override;
    virtual void RegisterProperties(EntityService& entityService) override;
    virtual void InitModes(const ModeController& modeController, const EntityService& entityService,
                           const PropertyData& data) override;

    void InitMode(std::shared_ptr<BasicMode> mode, const std::vector<FaceDirection>& directions,
                  const EntityService& entityService);

    void BuildAnimations(const EntityService& entityService, ModeType modeType);
    Animation GetAnimation(const EntityService& entityService, ModeType modeType) const;
};

}  // namespace Entity

}  // namespace FA
